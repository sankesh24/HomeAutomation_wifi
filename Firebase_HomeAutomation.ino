
#include <FirebaseESP8266.h>
#include  <ESP8266WiFi.h>
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11
// Initialize DHT sensor.
uint8_t DHTPin = D4; 
DHT dht(DHTPin, DHTTYPE); 
int sensorPin = A0;
int val = 0;
#define ssid "BALA"  //WiFi SSID
#define password "4285299689"  //WiFi Password
#define FIREBASE_HOST "mykingdom-a2f4e-default-rtdb.firebaseio.com"       //Firebase Project URL Remove "https:" , "\" and "/"
#define FIREBASE_AUTH "6XyF26hUVbnw3PxOacBS10aBZNBQU1b2U2N70bpB"      //Firebase Auth Token

FirebaseData firebaseData;

//If using Relay Module
int Device_1 = D0; //initialize D0 Pin
int Device_2 = D1; //initialize D1 Pin
int Device_3 = D2; //initialize D2 Pin
int Device_4 = D3; //initialize D3 Pin



void setup() {
  
 Serial.begin(9600);
   WiFi.begin (ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);

    pinMode(Device_1,OUTPUT);//initialize the Device OUTPUT  
    pinMode(Device_2,OUTPUT);//initialize the Device OUTPUT  
    pinMode(Device_3,OUTPUT);//initialize the Device OUTPUT  
    pinMode(Device_4,OUTPUT);//initialize the Device OUTPUT  
    pinMode (DHTPin,INPUT);
    dht.begin();
   
}


void loop() {
  if (Firebase.get(firebaseData,"/ABS/D1")) {
    if (firebaseData.dataType() == "string") {
      String De1 = firebaseData.stringData();
          if (De1=="1"){
              digitalWrite(Device_1,LOW); //Device1 is ON
              Serial.println ("Device 1 ON");
          }
          else if (De1=="0"){
              digitalWrite(Device_1,HIGH);//Device1 if OFF
              Serial.println ("Device 1 OFF");
            }}}
  if (Firebase.get(firebaseData,"/ABS/D2")) {
    if (firebaseData.dataType() == "string") {
      String De2 = firebaseData.stringData();
          if (De2=="1"){
              digitalWrite(Device_2,LOW);//Device2 is ON
              Serial.println ("Device 2 ON");
          }
              else if (De2=="0"){
              digitalWrite(Device_2,HIGH);// Device2 os OFF
              Serial.println ("Device 2 OFF");
            }}}
  if (Firebase.get(firebaseData,"/ABS/D3")) {
    if (firebaseData.dataType() == "string") {
      String De3 = firebaseData.stringData();
          if (De3=="1"){
              digitalWrite(Device_3,LOW);//Device3 is ON
              Serial.println ("Device 3 ON");
          }
              else if (De3=="0"){
              digitalWrite(Device_3,HIGH);//Device3 is OFF
              Serial.println ("Device 3 OFF");
            }}}
                      
  if (Firebase.get(firebaseData,"/ABS/D4")) {
    if (firebaseData.dataType() == "string") {
      String De4 = firebaseData.stringData();
          if (De4=="1"){
              digitalWrite(Device_4,LOW);//Device4 is ON
              Serial.println ("Device 4 ON");
          }
              else if (De4=="0"){
              digitalWrite(Device_4,HIGH);//Device4 is OFF
              Serial.println ("Device 4 OFF");
            }}}
  float Temperature = dht.readTemperature();
  Serial.print("Temperature = ");
  Serial.print(Temperature);
  Serial.println(" 'C ");
  Firebase.setFloat(firebaseData, "/ABS/Temp", Temperature);
  float Hum = dht.readHumidity();
  Serial.print("Humidity = ");
  Serial.print(Hum);
  Serial.println(" % ");
  Firebase.setFloat(firebaseData, "/ABS/Hum", Hum);
  int level = readSensor();
  Serial.print("water level:");
  Serial.println(level);
  Firebase.setFloat(firebaseData, "/ABS/waterlevel", level);
  
  }
 int readSensor(){
  val = analogRead(sensorPin);
  return val;
}
