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
  Wire.begin ();
  Serial.begin (512000);
  myIMU.init ();
  //yIMU. setAccOffsets ( -16330.0 , 16450.0 , -16600.0 , 16180.0 ,-16520.0 , 16690.0);
  //myIMU. setGyrOffsets ( -115.0 , 130.0 , 105.0);
  //Serial . println (" Position ␣your␣ ICM20948 ␣flat␣and␣don ’t␣move␣it␣-␣␣ calibrating ...");
  delay (1000);
  myIMU. autoOffsets ();
  // Serial . println ("Done!");
  myIMU. enableAcc (true );
  myIMU. enableGyr (true );
  myIMU. setAccRange ( ICM20948_ACC_RANGE_2G );
  myIMU. setAccDLPF ( ICM20948_DLPF_6 );
  myIMU. setAccSampleRateDivider (10);
  myIMU. setGyrRange ( ICM20948_GYRO_RANGE_250 );
  myIMU. setGyrDLPF ( ICM20948_DLPF_6 );
  myIMU. setGyrSampleRateDivider (10);
  myIMU. setMagOpMode ( AK09916_CONT_MODE_20HZ );

  // Setup for udp:
  WiFi.begin(ssid , password );
  WiFi.mode(WIFI_STA); // ESP -32 as client
  WiFi.config (ipCliente , ipServidor , Subnet );
  Udp.begin (localPort);

  // Setup for emg
  #define volt_esp32e 5.0
  #define baud_esp_32e 512000
  //Serial.begin (baud_esp_32e );
}

void loop () {
// IMU
myIMU. readSensor ();
xyzFloat gValue = myIMU. getGValues ();
xyzFloat gyr = myIMU. getGyrValues ();
// returns magnetic flux ensity [ microT ]
xyzFloat magValue = myIMU. getMagValues ();
float resultantG = myIMU. getResultantG ( gValue );
// For g- values the corrected raws are used
// Serial . println (" Acceleration ␣in␣g␣(x,y,z):");


//Change x and y directions:
xyzFloat norm_gValue;
norm_gValue.x = - gValue.x / 2;
norm_gValue.y = - gValue.y / 2;
norm_gValue.z = gValue.z / 2;


xyzFloat norm_gyr;
norm_gyr.x = gyr.x / 250;
norm_gyr.y = gyr.y / 250;
norm_gyr.z = gyr.z / 250;

xyzFloat norm_mag;
norm_mag.x = magValue.x;
norm_mag.y = magValue.y;
norm_mag.z = magValue.z;

/*
Serial.print("Acc_x:");
Serial.print(norm_gValue.x);
Serial.print(",");
Serial.print("Acc_y:");
Serial.print(norm_gValue.y);
Serial.print(",");
Serial.print("Acc_z:");
Serial.print(norm_gValue.z);

Serial.print(",");

Serial.print("Gyr_x:");
Serial.print(norm_gyr.x);
Serial.print(",");
Serial.print("Gyr_y:");
Serial.print(norm_gyr.y);
Serial.print(",");
Serial.print("Gyr_z:");
Serial.println(norm_gyr.z);
*/


// Differentiaion of trials:
float absolute_norm_g = sqrt(sq(norm_gValue.x) + sq(norm_gValue.y) + sq(norm_gValue.z));
float theta =  fmod(((atan2(norm_gValue.y, norm_gValue.x)* 360 / (2*M_PI)) + 360), 360); // horizontal plane
float phi = acos(norm_gValue.z / absolute_norm_g);

// TODO: Make it insensitive to rotation.
/*if (previous_upward > 0.6 && previous_upward1 < 0.6 && previous_upward2 < 0.6 && state == "Origin"){
  state = "Upwards";
  Serial.println();
  Serial.println();
  Serial.println(state);
  Serial.println("Result: 9 (moving upward)");
} else if(state == "Upwards" && (previous_upward > 0.48) && (previous_upward1 < 0.48) && (previous_upward2 < 0.48)){
  Serial.println("Downward");
  state = "Origin";
  Serial.println(state);
  Serial.println();*/
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
} else if (round(absolute_norm_g * 100.0) / 100.0 == 0.50 && previous_num == 0.50 && previous_num1 == 0.50 && previous_num2 == 0.50 && (state == "Moving outward" || state == "Moving inward")) {
  if (state == "Moving outward") {
    state = "Outward";
    //Serial.println(state);
    accumulate_angles = false;
    float max_angle = 0;
    float min_angle = 360;
    float max_acc = -100;
    float min_acc = 100;
    float max_gyr_z = -100;
    float min_gyr_z = 100;

   //Serial.print("Number of angles: ");
   //Serial.println(number_angles);
   //Serial.println();

   /*
   for (int i = 0; i < number_angles; i++){
      Serial.println(angle_list[number_angles]);
   }
   */
   

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

   //Serial.print("Max angle: ");
   //Serial.println(max_angle);
   //Serial.print("Min angle");
   //Serial.println(min_angle);

   if ((max_angle - min_angle) > 330){
    //Serial.println("Special: Right direction");
     // cumulative_angle = 0;
   
      for (int i = 0; i < number_angles; i++){
        if (angle_list[i] < 180){
          //cumulative_angle += (angle_list[number_angles] + 360)
          cumulative_angle += 360;
        //}else{
        //  cumulative_angle += angle_list[number_angles]
        //}
        }
      }
      
    
    //Serial.println((cumulative_angle / number_angles) * 360 / (2*M_PI));
   }
   float mean_angle = fmod((cumulative_angle / number_angles), 360);
   /*
   Serial.print("Max acc_z: ");
   Serial.println(max_acc);

   Serial.print("Min acc_z: ");
   Serial.println(min_acc);

   Serial.print("Max gyr_z: ");
   Serial.println(max_gyr_z);

   Serial.print("Min gyr_z: ");
   Serial.println(min_gyr_z);
   
   Serial.print("Mean angle: ");
   Serial.println(mean_angle);
   */

   // Here the mean angle result is known.
   // Coding scheme:
   int result_number = -2;
   if (max_gyr_z > 0.8 || min_gyr_z < -0.8){
    result_number = 0;
    //state = "Origin";
    //Serial.println(state);
    //delay(100);
   } else if (max_acc > 0.8){
    result_number = 9;
    //state = "Origin";
    //Serial.println(state);
    //delay(100);
   }else if (mean_angle <= 22.5 or mean_angle > 337.5){
    result_number = 3;
   }else if(mean_angle > 22.5 and mean_angle <= 67.5){
    result_number = 2;
   }else if(mean_angle > 67.5 and mean_angle <= 112.5){
    result_number = 1;
   }else if(mean_angle > 112.5 and mean_angle <= 157.5){
    result_number = 8;
   }else if(mean_angle > 157.5 and mean_angle <= 202.5){
    result_number = 7;
   }else if(mean_angle > 202.5 and mean_angle <= 247.5){
    result_number = 6;
   }else if(mean_angle > 247.5 and mean_angle <= 292.5){
    result_number = 5;
   }else if(mean_angle > 292.5 and mean_angle <= 337.5){
    result_number = 4;
   }

   state = "Origin";
   //Serial.println(state);
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
   //Serial.print("The␣ sending ␣ message ␣is:␣");
   //Serial.println(buf);

   delay(300);

   //Serial.print("Result angle: ");



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



   

   // Systems engineering: Divide and conquer: test subsystems individually, stack them together later.
   // Give numbers for the whole subsystem. (30 bits per minute.
   // --> one can say which one has to be improved!
   /* EMG: removing numbers
    * 0: 
    * 
    * 
    * Work on skeleton models: First: Go for a very simple model, then improve it.
    * Do recordings! (with a camera!)
    * 
    * 
    */


   
  } else if (state == "Moving inward") {
    state = "Origin";
    Serial.println(state);
    Serial.println();
    
  }
  delay(200);
}

if (accumulate_angles == true){
  angle_list[number_angles] = theta;
  acc_z_list[number_angles] =  round(norm_gValue.z * 100.0) / 100.0;
  gyr_z_list[number_angles] = round(norm_gyr.z * 100.0) / 100.0;
  //Serial.println("Theta: ");
  //Serial.println(theta);

  number_angles++;
  cumulative_angle += theta;
  float mean_angle = cumulative_angle / number_angles;
  //Serial.println(mean_angle);
}

previous_num2 = previous_num1;
previous_num1 = previous_num;
previous_num = round(absolute_norm_g * 100.0) / 100.0;


previous_upward2 = previous_upward1;
previous_upward1 = previous_upward;
previous_upward = round(norm_gValue.z * 100.0) / 100.0;


// EMG
int sensorValue = analogRead (34);
float voltage = sensorValue * (volt_esp32e / 4095.0);
emg_list[emg_list_counter] = sensorValue;
emg_list_counter += 1;
emg_list_counter = emg_list_counter % 300;
float emg_sum = 0;
for(int i = 0; i < 300; i++){
  emg_sum += emg_list[i];
}

float emg_threshold = 4050;
float mean_emg = emg_sum / 300;
if (mean_emg <= emg_threshold && muscle_flexed == true){
  muscle_flexed = false;
} else if (mean_emg > emg_threshold && muscle_flexed == false && (millis()-state_change_time) > 1000) {
  muscle_flexed = true;
  state_change_time = millis();
  int result_number = -1;
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
}

/*
if (previous_upward > 0.7){
  Serial.println(previous_upward);
}
*/




//Serial.print("G_norm:");
//Serial.println(absolute_norm_g);
//Serial.println(state);
//Serial.print(",");
//Serial.print("Theta:");
//Serial.print(theta);
//Serial.print(",");
//Serial.print("Phi:");
//Serial.println(phi);



/*
Serial.print(",");


Serial.print("Mag_x:");
Serial.print(magValue.x);
Serial.print(",");
Serial.print("Mag_y:");
Serial.print(magValue.y);
Serial.print(",");
Serial.print("Mag_z:");
Serial.println(magValue.z);
*/


/*
Serial . print("␣␣␣");
Serial . print( gValue .y);
Serial . print("␣␣␣");
Serial . println ( gValue .z);
// The resulting acceleration from a g-value triple :
// The absolute value of the sum of the three vectors
Serial . print(" Resultant ␣g:␣");
Serial . println ( resultantG );
Serial . println (" Gyroscope ␣data␣in␣ degrees /s:␣");
Serial . print(gyr.x);
Serial . print("␣␣␣");
Serial . print(gyr.y);
Serial . print("␣␣␣");
Serial . println (gyr.z);
Serial . println (" Magnetometer ␣Data␣in␣ microTesla :␣");
Serial . print( magValue .x);
Serial . print("␣␣␣");
Serial . print( magValue .y);
Serial . print("␣␣␣");
Serial . println ( magValue .z);
Serial . println (" ******************************************** ");
delay (500);
*/
}
