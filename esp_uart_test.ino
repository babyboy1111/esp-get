#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif
#include <Wire.h>
#include "ESP32_MailClient.h"
// REPLACE WITH YOUR NETWORK CREDENTIALS

#define emailSenderAccount    "ghuyniot@gmail.com"    
#define emailSenderPassword   "weekndcold1"
#define emailRecipient        "nguyenkhaikh321@gmail.com"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "NodeWifi32 Test"
#define RXD2 16
#define TXD2 17
#define LED 2
// The Email Sending data object contains config and data to send
SMTPData smtpData;
// Callback function to get the Email sending status

//Access point credentials
const char* ssid = "Sinh Vien Home";
const char* password = "06117370";
const char* host = "http://dighuyniot.tech";
String get_host = "http://dighuyniot.tech";
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 3000000; 
int check=0;
char buff[10];
char str1[10]="b1x";
char str2[10]="b0x";
volatile byte indx;
WiFiServer server(80);  // open port 80 for server connection
void sendCallback(SendStatus info);
  void setup() {
    // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
    Serial.begin(115200);
    //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    pinMode(LED,OUTPUT);
  WiFi.begin(ssid, password);
    //starting the server
    server.begin();
    startMillis = millis();
  }
boolean checkArrays(char arrayA[],char arrayB[], long numItems) {

    boolean same = true;
    long i = 0;
    while(i<numItems && same) { 
      same = arrayA[i] == arrayB[i];
      i++;
    }
    return same;
  }
  
 void loop()
{
  if(Serial2.available()>0){
    char c=Serial2.read();
    if(indx<sizeof buff){
      buff[indx++]=c;
      if(c=='x'){
        if(checkArrays(buff,str1,10)){
       digitalWrite(LED,HIGH);
      }else if(checkArrays(buff,str2,10)){digitalWrite(LED,LOW);}
        indx=0;
      }
    }else{indx=0;}
   }
}
