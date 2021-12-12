#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

int motorPin3 = 15; // digital pin D15 for vibration motor 1
int motorPin4 = 18; // digital pin D18 for vibration motor 2
int motorPin1 = 19; // digital pin D18 for vibration motor 2
int motorPin2 = 21; // digital pin D18 for vibration motor 2


WiFiUDP Udp ; // creation of wifi Udp instance
char packetBuffer[500];
unsigned int localPort = 9999;
const char * ssid = " ESP32_for_IMU " ;
const char * password = " ICSESP32IMU " ;

void setup () {
Serial . begin (512000);
WiFi . softAP ( ssid , password ); // ESP32 as access point
Udp . begin ( localPort );
pinMode ( motorPin1 , OUTPUT );
pinMode ( motorPin2 , OUTPUT );
pinMode ( motorPin3 , OUTPUT );
pinMode ( motorPin4 , OUTPUT );
}



char *sender;
char buffer_all[500];//buffer

int count = -1; // pointer for writing the buffer
// We set this to -1 because we do the following:
// The counter reflects the position last written to/read from.
// This means that if they're equal, we can't read anymore.

int count_replay = -2; //pointer for reading the buffer
int count_loop =0; // loop counter for the whole loop process
long int mytime; // count the time since board onset
long int mytime_pre; // record the time where last reading happens



void loop () {
 
// receive message
int packetSize = Udp . parsePacket (); 
if ( packetSize) {

int len = Udp . read ( packetBuffer,255);
if ( len > 0) packetBuffer [ len -1] = 0;

//print the received number
Serial.print("Packet received: ");
Serial . println ( packetBuffer );

// -1 which used as correction will be transferred to "255" in char
// so we check whether the second char of the string is 5, if so, this is a correction signal
// then we set current position in buffer to a blank
  
if(packetBuffer[1] == '5')
{
  buffer_all[count] = ' ';
}

// writing the buffer
else
{
  sender =  packetBuffer;
  count ++;
  buffer_all[count] = *sender;
}

// print what is written into the buffer
Serial.print("Write counter: ");
Serial.println(count);

}

mytime = millis();// calculate time since board onset

//only for the first loop,set mytime and mytime_pre to be equal
if (count_loop == 0){
mytime_pre = mytime;
}

// if two pointers has at least two position in between(in case of there is a correction blank)
// and last reading has been at least 2000 ms away from current writing(time-delay for replaying)
if (count -1 > count_replay && mytime_pre + 2000 < mytime&& buffer_all[count_replay+1]!=' ') {

Serial.println("now start reading!");
mytime_pre = mytime;
count_replay++;
  
//read buffer
if (count_replay >= 0) {
sender_replay = buffer_all[count_replay]; //read

// print the reading pointer  
Serial.print("Read counter: ");
Serial.println(count_replay);
  
//print the replay number  
Serial.print("Reading: ");
Serial.println(buffer_all[count_replay]);

Serial.print("buffer space :");
Serial.println(buffer_all);

// vibrate  
if (sender_replay == '1') 
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
          } 
      else if (sender_replay =='2') 
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
          } 
      else if (sender_replay =='3')
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
          }
      else if (sender_replay =='4')
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender_replay =='5')
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , LOW );
          }
      else if (sender_replay =='6')
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender_replay =='7')
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , LOW );
          }
      else if (sender_replay =='8')
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender_replay =='9')
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender_replay =='0')
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , LOW );
          }
          delay(400);

             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
             delay(100);
             
}
}
else if (count -1 > count_replay && mytime_pre + 2000 < mytime&& buffer_all[count_replay+1]==' '){
  count_replay++;
}

count_loop ++;
}
