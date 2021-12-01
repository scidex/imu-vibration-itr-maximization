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


int a[100] = {0};
int count = 0;
int packet_Buffer;
char sender;

void loop () {
int packetSize = Udp . parsePacket ();
if ( packetSize ) {
int len = Udp . read ( packetBuffer,255);
if ( len > 0) packetBuffer [ len -1] = 0;
Serial . print ( " The ␣ receiving ␣ message ␣ is : ␣ " );
Serial . println ( packetBuffer );

//packet_Buffer = (int)packetBuffer;

//a[count] = packet_Buffer;

//sender = packet_Buffer;
//Serial . println ( sender );
sender = *packetBuffer;

if (sender == '1') 
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
          } 
      else if (sender =='2') 
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
          } 
      else if (sender =='3')
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , LOW );
          }
      else if (sender =='4')
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender =='5')
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , LOW );
          }
      else if (sender =='6')
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender =='7')
          {
             digitalWrite ( motorPin1 , LOW );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , LOW );
          }
      else if (sender =='8')
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , LOW );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender =='9')
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , HIGH );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , HIGH );
          }
      else if (sender =='0')
          {
             digitalWrite ( motorPin1 , HIGH );
             digitalWrite ( motorPin2 , LOW );
             digitalWrite ( motorPin3 , HIGH );
             digitalWrite ( motorPin4 , LOW );
          }

delay (1000);
}
}
