#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "D3sJR4rSTXkKpgjqh6fCQc4UO_20Pwgf";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HONDAGMC";
char pass[] = "18182321yougi";

void getPirValue();
void getSoilMoisture();

#define montionSensor 5                // Input for HC-S501
#define soilMoistureSensor1 4 
#define soilMoistureSensor2 0
#define soilMoistureSensor3 2 
#define soilMoistureSensorData A0
int pirValue;                   // Place to store read PIR Value
int pinValue;                   //Variable to read virtual pin
int soilMoistureSensorValue;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000; 

BLYNK_WRITE(V0)
{
 pinValue = param.asInt();    
} 

void setup()
{
  Serial.begin(9600);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(montionSensor, INPUT);
  pinMode(soilMoistureSensor1, OUTPUT);
  pinMode(soilMoistureSensor2, OUTPUT);
  pinMode(soilMoistureSensor3, OUTPUT);
  pinMode(soilMoistureSensorData, INPUT);
  startMillis = millis();  //initial start time
}

void loop()
{
  Blynk.run();
  if (pinValue == HIGH)    
  {
    getPirValue();
  }

  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    getSoilMoisture();
    startMillis = currentMillis;
  }
}

void getPirValue(void)        //Get PIR Data
{
  pirValue = digitalRead(montionSensor);
  if (pirValue) 
    { 
      Serial.println("Motion detected");
      Blynk.notify("Motion detected");  
    }
}

void getSoilMoisture(void)
{
  digitalWrite(soilMoistureSensor1,HIGH);
  delay(1000);
  soilMoistureSensorValue = analogRead(soilMoistureSensorData);
  digitalWrite(soilMoistureSensor1,LOW);

  Blynk.virtualWrite(V2, soilMoistureSensorValue);

  digitalWrite(soilMoistureSensor2,HIGH);
  delay(1000);
  soilMoistureSensorValue = analogRead(soilMoistureSensorData);
  digitalWrite(soilMoistureSensor2,LOW);
  Blynk.virtualWrite(V3, soilMoistureSensorValue);

  digitalWrite(soilMoistureSensor3,HIGH);
  delay(1000);
  soilMoistureSensorValue = analogRead(soilMoistureSensorData);
  digitalWrite(soilMoistureSensor3,LOW);
  Blynk.virtualWrite(V4, soilMoistureSensorValue);

}