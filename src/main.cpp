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
            Serial.println("Button pressed");
        }
    }
}

void intWifi(){

int retries = 1;
while(WiFi.status() != WL_CONNECTED && retries > 0) {
    WiFi.begin(ssid, password);
    delay(500);
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

  Serial.println("Free heap: " + String(ESP.getFreeHeap())); 
  if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi connection lost. Reconnecting...");
        flagWifi = false;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi connection is good");
        flagWifi = true;
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
  timerAlarmWrite(timer, 2000000, true); // alarm value in microseconds, autoreload
  timerAlarmEnable(timer); 
  intWifi();
  //connectWiFi();

}


void loop()
{


if(!flagWifi){
intWifi();
}



 
  
delay(10000);

  
}
