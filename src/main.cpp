#include <WiFi.h>
#include <ArduinoBLE.h>
#include <ArduinoHttpClient.h>
#include <HTTPClient.h>
#include "setting.h"
#include "myWifi.h"
#include <iostream>
#include "postDataToServer.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <FastLED.h>
#include <M5Atom.h>
#include <esp_heap_caps.h>
#include <esp_task_wdt.h>

int buttonState = 0;
unsigned long lastDebounceTime = 0; 
const int debounceDelay = 50;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
using namespace std;
int previousMillis = 0;

volatile bool flagWifi = false;
volatile bool flagRegister = false;


void IRAM_ATTR buttonPressed() {
    int reading = digitalRead(39);
    if (reading != buttonState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
        buttonState = reading;
        if (buttonState == LOW) {
           // Serial.println("Button pressed");
            flagRegister=true;

        }
    }
}

void intWifi(){

int retries = 2;
while(WiFi.status() != WL_CONNECTED && retries > 0) {
    Serial.println("attempting to connect");
    WiFi.begin(ssid, password);
    delay(1000);
    retries--;
}

if(WiFi.status() != WL_CONNECTED){
  //connection failed
 Serial.println("connect wifi is not connected");
  flagWifi = false;
}
else{
  //connection success
   Serial.println("connect wifi is good");
  flagWifi = true;
}

}


void IRAM_ATTR showMessageToConsole() {
 portENTER_CRITICAL_ISR(&timerMux);
          Serial.println("wifi status"); 
        Serial.println(WiFi.status()); 

  //Serial.println("Free heap: " + String(ESP.getFreeHeap())); 
  if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi connection lost. Reconnecting...");
        flagWifi = false;
        Serial.println("flagWifi"); 
        Serial.println(flagWifi); 
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi connection is good");
        flagWifi = true;
        Serial.println("flagWifi"); 
        Serial.println(flagWifi); 
    } 


  portEXIT_CRITICAL_ISR(&timerMux); 

   
}

void setup()
{
  Serial.begin(115200);

  pinMode(39, INPUT);
  attachInterrupt(digitalPinToInterrupt(39), buttonPressed, FALLING);
  timer = timerBegin(1, 80, true); // timer index, divider, count up
  timerAttachInterrupt(timer, &showMessageToConsole, true); // interrupt function, edge trigger
  timerAlarmWrite(timer, 4000000, true); // alarm value in microseconds, autoreload
  timerAlarmEnable(timer); 
  intWifi();

  // intilaze bluetooth
   BLE.begin();
   BLE.scan();

}


void loop()
{


if(!flagWifi){
    // connectWiFi again
intWifi();
}
Serial.println("flag wifi on main loop");
Serial.println(flagWifi);

Serial.println("flagRegister");
Serial.println(flagRegister);
if(flagRegister){
    // button pressed will triger to function
  Serial.println("button pressed");
  int countScan = 10;

for (int i = 0; i < countScan; i++) {
  BLEDevice peripheral = BLE.available();
  if (peripheral) {
    String address = peripheral.address();
    int rssi = peripheral.rssi();
    // Do something with the address
    Serial.print("address: ");
    Serial.println(address);
     Serial.print("RSSI: ");
          Serial.println(rssi);
  }
}
  flagRegister=false;
}



   


 
  
delay(1000);

  
}
