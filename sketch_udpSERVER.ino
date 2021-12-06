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



char sender;
char buffer_all[500];
int count = 0;
int count_replay = 0;
char sender_replay;

void loop () {
int packetSize = Udp . parsePacket ();
if ( packetSize ) {
int len = Udp . read ( packetBuffer,255);
if ( len > 0) packetBuffer [ len -1] = 0;
Serial . print ( " The ␣ receiving ␣ message ␣ is : ␣ " );
Serial . println ( packetBuffer );


sender = *packetBuffer;
buffer_all[count] = sender;
count +=count;


Serial . println(sender);

long int mytime = millis();
Serial.print(mytime);
while(mytime%800 ==0 ){
sender_replay = buffer_all[count_replay];
count_replay += count_replay;
  
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
          delay(500);

             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
             delay(300);
             mytime = 0;
}



      


}
}
