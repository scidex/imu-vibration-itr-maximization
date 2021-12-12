/*
 * 
 * This script can be used for the encoder side. An IMU can be used for encoding the numbers 0-9.
 * In addition an EMG can be used for increasing accuracy. No changes in the code have to be made if it is decided that no EMG correction is needed.
 * Make sure that the IP-adreee specified in the IP block is not occupied by another device in the same network yet!
 * 
 */


# include <Wire.h>
# include <math.h>
# include <ICM20948_WE.h>
# include <WiFi.h>
# include <WiFiUdp.h>
# define ICM20948_ADDR 0x69
ICM20948_WE myIMU = ICM20948_WE ( ICM20948_ADDR );

// Setting up the udp connection:
WiFiUDP Udp; // creation of wifi Udp instance
int packetBuffer[255];
# define BUFFER_SIZE 500
unsigned int localPort = 9999;
const char *ssid = " ESP32_for_IMU ";
const char * password = " ICSESP32IMU ";
// declaration of default IP for server
IPAddress ipServidor (192 , 168, 4, 1);

/*
* The ip address of the client has to be different to the server
* otherwise it will conflict because the client tries to connect
* to itself .
*/

IPAddress ipCliente (192 , 168, 4, 170); // different IP than server
IPAddress Subnet (255 , 255, 255, 0);

// Initializing scalar and list variables for storing measurements and states
float previous_num = 0.5;
float previous_num1 = 0.5;
float previous_num2 = 0.5;

float previous_upward = 0.5;
float previous_upward1 = 0.5;
float previous_upward2 = 0.5;

float emg_list[300] = {0};
int emg_list_counter = 0;
bool muscle_flexed = true;
float state_change_time = millis();

String state = "Origin";
bool accumulate_angles = false;
int number_angles = 0;
float cumulative_angle = 0;
float mean_angle = 0;
float angle_list[1000] = {0};
float acc_z_list[1000] = {0};
float gyr_z_list[1000] = {0};

void setup () {

  // Setup for IMU
  Wire.begin ();
  Serial.begin (512000);
  myIMU.init ();
  delay (1000);
  myIMU. autoOffsets ();
  myIMU. enableAcc (true );
  myIMU. enableGyr (true );
  myIMU. setAccRange ( ICM20948_ACC_RANGE_2G );
  myIMU. setAccDLPF ( ICM20948_DLPF_6 );
  myIMU. setAccSampleRateDivider (10);
  myIMU. setGyrRange ( ICM20948_GYRO_RANGE_250 );
  myIMU. setGyrDLPF ( ICM20948_DLPF_6 );
  myIMU. setGyrSampleRateDivider (10);
  myIMU. setMagOpMode ( AK09916_CONT_MODE_20HZ );

  // Setup udp:
  WiFi.begin(ssid , password );
  WiFi.mode(WIFI_STA); // ESP -32 as client
  WiFi.config (ipCliente , ipServidor , Subnet );
  Udp.begin (localPort);

  // Setup EMG
  #define volt_esp32e 5.0
  #define baud_esp_32e 512000
}

void loop () {
// Defining storage variables and initializing them with current IMU measurement values
myIMU. readSensor ();
xyzFloat gValue = myIMU.getGValues();
xyzFloat gyr = myIMU.getGyrValues();
xyzFloat magValue = myIMU.getMagValues();
float resultantG = myIMU.getResultantG(gValue);


// Transformation into xyz coordinate system proposed in the report:
//
//     z-axis (up)
//     ^   y-axis (forward)
//     |  7
//     | /
//     |/
//     +-----------> x-axis (to RHS)

xyzFloat norm_gValue;
norm_gValue.x = - gValue.x / 2;
norm_gValue.y = - gValue.y / 2;
norm_gValue.z = gValue.z / 2;

// Normalizing gyroscope values
xyzFloat norm_gyr;
norm_gyr.x = gyr.x / 250;
norm_gyr.y = gyr.y / 250;
norm_gyr.z = gyr.z / 250;

xyzFloat norm_mag;
norm_mag.x = magValue.x;
norm_mag.y = magValue.y;
norm_mag.z = magValue.z;


// Transformation from Cartesian coordinates into Spherical coordinates
// r = absolute_norm_g
float absolute_norm_g = sqrt(sq(norm_gValue.x) + sq(norm_gValue.y) + sq(norm_gValue.z));
float theta =  fmod(((atan2(norm_gValue.y, norm_gValue.x)* 360 / (2*M_PI)) + 360), 360); // horizontal plane
float phi = acos(norm_gValue.z / absolute_norm_g);

// Introducing several conditions for number encoding:
// 1. absolute acceleration as well as the the previous two acceleration measurements must be greater than threshold
// 2. The state must be Oritin or Outward
// Accumulating angles is started
if (round(absolute_norm_g * 100.0) / 100.0 > 0.52 && previous_num > 0.52 && previous_num1 > 0.52 && previous_num2 > 0.52  && (state == "Origin" || state == "Outward")) {
  if (state == "Origin") {
    state = "Moving outward";
    number_angles = 0;
    cumulative_angle = 0;
    accumulate_angles = true;
    //Serial.println(state);
  } else if (state == "Outward") {
    state = "Moving inward";
    Serial.println(state);
  }
// Conditions for detecting the Outward state:
// 1. absolute acceleration is at baseline (0.5)
// 2. State is moving Outward or moving inward
} else if (round(absolute_norm_g * 100.0) / 100.0 == 0.50 && previous_num == 0.50 && previous_num1 == 0.50 && previous_num2 == 0.50 && (state == "Moving outward" || state == "Moving inward")) {
  if (state == "Moving outward") {
    state = "Outward";
    accumulate_angles = false;

    // Detecting the minimum and maximum acceleration, and gyroscope value around the z axis
    float max_angle = 0;
    float min_angle = 360;
    float max_acc = -100;
    float min_acc = 100;
    float max_gyr_z = -100;
    float min_gyr_z = 100;

   for (int i = 0; i < number_angles; i++){
      //Serial.println(angle_list[i]);
      if (angle_list[i] > max_angle){
        max_angle = angle_list[i];
      }
      if (angle_list[i] < min_angle){
        min_angle = angle_list[i];
      }

      // Do the same thing for the acceleration
      if (acc_z_list[i] > max_acc){
        max_acc = acc_z_list[i];
      }
      if (acc_z_list[i] < min_acc){
        min_acc = acc_z_list[i];
      }

      if (gyr_z_list[i] > max_gyr_z){
        max_gyr_z = gyr_z_list[i];
      }
      if (gyr_z_list[i] < min_gyr_z){
        min_gyr_z = gyr_z_list[i];
      }
   }

   // Moving to the right hand side must be evaluated as an extra case.
   // Example in a coordinate system with x-axis to right (0°), y-axis upwards (90°), negative y-axis (270°)
   // Hence, if moving right values between 0°-22.5° and 337.5°-360° are encountered. Taking the average here would give a result of ~180° and would hence point in negative x-direction, which is wrong.
   // Hence, a correction must be performed:
   if ((max_angle - min_angle) > 330){
   
      for (int i = 0; i < number_angles; i++){
        if (angle_list[i] < 180){
          cumulative_angle += 360;
        }
      }
   }
   float mean_angle = fmod((cumulative_angle / number_angles), 360);

   // Now, the mean angle is known and this mean angle is translated into the number encoding
   int result_number = -2; // Default number -2 if encounting went wrong. -1 is used for resetting
   if (max_gyr_z > 0.8 || min_gyr_z < -0.8){

   // Horizontal encoding scheme:
   /*
   3: 0 degrees, range: -22.5 (or 337.5) to 22.5
   2: 45 degrees, range: 22.5 to 67.5
   1: 90 degrees, range: 67.5 to 112.5
   8: 135 degrees, range: 112.5 to 157.5
   7: 180 degrees, range: 157.5 to 202.5
   6: 225 degrees, range: 202.5 to 247.5
   5: 270 degrees, range: 247.5 to 292.5
   4: 315 degrees, range: 292.5 to 337.5
   */

   // result_number holds the encoded number, the angle is specified in a polar coordinate system
   result_number = 0;
   // Upwards direction detection using the z-acceleration value for a threshold condition
   } else if (max_acc > 0.8){
    result_number = 9; // upwards
   }else if (mean_angle <= 22.5 or mean_angle > 337.5){
    result_number = 3; // 0°
   }else if(mean_angle > 22.5 and mean_angle <= 67.5){
    result_number = 2; // 45°
   }else if(mean_angle > 67.5 and mean_angle <= 112.5){
    result_number = 1; //90°
   }else if(mean_angle > 112.5 and mean_angle <= 157.5){
    result_number = 8; //135°
   }else if(mean_angle > 157.5 and mean_angle <= 202.5){
    result_number = 7; // 180°
   }else if(mean_angle > 202.5 and mean_angle <= 247.5){
    result_number = 6; // 225°
   }else if(mean_angle > 247.5 and mean_angle <= 292.5){
    result_number = 5; // 270°
   }else if(mean_angle > 292.5 and mean_angle <= 337.5){
    result_number = 4; // 215°
   }

   state = "Origin";
   // Giving feedback to the decoding participant
   Serial.print(result_number);
   Serial.print(", ");

   // Send the number per udp:
   char result_number_char = char(result_number);
   Udp.beginPacket(ipServidor, 9999); // initiate transmission of data
   char buf[BUFFER_SIZE]; // buffer to hold the string to append
   // appending to create a char
   sprintf(buf, "%d", result_number_char);
   Udp.printf(buf); // print the char
   Udp.printf("\r\n"); // end segment
   Udp.endPacket(); // close communication
   delay(300);

  // Resetting state to Origin after the movement was performed
  } else if (state == "Moving inward") {
    state = "Origin";
    Serial.println(state);
    Serial.println();
    
  }
  // Introducing a short delay of 200ms to be sure that the movement is over
  delay(200);
}

// Appending the current theta angle to a list which is evaluated to obtain the mean angle
// The same is done with the acceleration and gyroscope values in z-direction
if (accumulate_angles == true){
  angle_list[number_angles] = theta;
  acc_z_list[number_angles] =  round(norm_gValue.z * 100.0) / 100.0;
  gyr_z_list[number_angles] = round(norm_gyr.z * 100.0) / 100.0;

  number_angles++;
  cumulative_angle += theta;
  float mean_angle = cumulative_angle / number_angles; // Current mean angle
}


// Storing the previous values for the threshold conditions
previous_num2 = previous_num1;
previous_num1 = previous_num;
previous_num = round(absolute_norm_g * 100.0) / 100.0;


previous_upward2 = previous_upward1;
previous_upward1 = previous_upward;
previous_upward = round(norm_gValue.z * 100.0) / 100.0;


// Using an EMG for resetting the last encoded number
int sensorValue = analogRead (34);
float voltage = sensorValue * (volt_esp32e / 4095.0);
// Measuring the sensor value and storing it for mean evaluation 
// The last 300 sample measurements are stored.
emg_list[emg_list_counter] = sensorValue;
emg_list_counter += 1;
emg_list_counter = emg_list_counter % 300;
float emg_sum = 0;
for(int i = 0; i < 300; i++){
  emg_sum += emg_list[i];
}

float emg_threshold = 4050;
// Obtaining the mean emg value

float mean_emg = emg_sum / 300;
// EMG condition for defaultly setting the mu
// 1. Mean EMG value is smaller than threshold
// 2. Muscle is flexed already
if (mean_emg <= emg_threshold && muscle_flexed == true){
  muscle_flexed = false;
// Condition for detection muscle flexion:
// 1. Threshold is exceeded
// 2. Muscle is not flexed yet
// 3. The previous resetting lies at least 1 second in the past.
} else if (mean_emg > emg_threshold && muscle_flexed == false && (millis()-state_change_time) > 1000) {
  muscle_flexed = true;
  state_change_time = millis();
  int result_number = -1; // -1 is sent via UDP for resetting on the receiver side
  // Printing to give the encoder participant feedback
  Serial.print(result_number);
  Serial.print(", ");
  // Send the number per UDP:
  char result_number_char = char(result_number);
  Udp.beginPacket(ipServidor, 9999); // initiate transmission of data
  char buf[BUFFER_SIZE]; // buffer to hold the string to append
  sprintf(buf, "%d", result_number_char);
  Udp.printf(buf); // print the char
  Udp.printf("\r\n"); // end segment
  Udp.endPacket(); // close communication
}
}
