#include <WiFi.h>
#include <ArduinoBLE.h>
#include <ArduinoHttpClient.h>
// #include <Ethernet.h>
#include <HTTPClient.h>
#include "setting.h"
// #include "runfunctionAfterDelays.h"
#include "myWifi.h"
#include <iostream>
#include "postDataToServer.h"
#include <string>
// #include <random>
// #include <array>
#include <cstdlib>
#include <ctime>
#include <FastLED.h>
#include <M5Atom.h>
#include <esp_heap_caps.h>
#include <esp_task_wdt.h>
hw_timer_t * timer = NULL;

void IRAM_ATTR showMessageToConsole() {
  // Code to be executed when the timer triggers
  Serial.println("Timer triggered!");
}






using namespace std;
int previousMillis = 0;

void getSignalQuality(int rssi)
{
  if (rssi >= -75 && rssi <= -28)
  {

    digitalWrite(33, HIGH); // light is on

    delay(3000);
  }
  else
  {
    digitalWrite(33, LOW); // light is off
  }
}

void setup()
{

  Serial.begin(115200);
  pinMode(33, OUTPUT);   // set pin 33 to output mode
  digitalWrite(33, LOW); // light is off
  setupWifi(ssid, password);
  BLE.begin();
  BLE.scan(); // start scanning for peripherals
  esp_task_wdt_init(60, true);
  esp_task_wdt_add(NULL);  
  // st up timer
  timer = timerBegin(0, 80, true); // timer index, divider, count up
  timerAttachInterrupt(timer, &showMessageToConsole, true); // interrupt function, edge trigger
  timerAlarmWrite(timer, 2000, true); // alarm value in microseconds, autoreload
  //timerAlarmEnable(timer); 



}




void loop()
{

  unsigned long currentMillis = millis();
  // Serial.print("Free memory: "+heap_caps_get_free_size(MALLOC_CAP_8BIT));
  Serial.println("Free heap: " + String(ESP.getFreeHeap()));
  if (ESP.getFreeHeap() < 25000)
  {                // Check if the free heap is less than 2500 bytes
    ESP.restart(); // Reset the device
  }

  // Check if 1 second has passed
  if (currentMillis - previousMillis >= 8000)
  {
    // Reset the elapsed time tracker
    BLE.stopScan();
    //Serial.println("stop scan : ");
    delay(500);
    BLE.begin();
    //Serial.println("scan again scan : ");
    BLE.scan();
    previousMillis = currentMillis;
  }
  else
  {

    wifiReconnectWhenLost(ssid, password);
    BLEDevice peripheral = BLE.available();
    bool deviceTargetScan = peripheral.advertisedServiceUuid() == uuidBeacon || peripheral.address() == macBeacon;

    if (deviceTargetScan)
    {

     
      int rssi = peripheral.rssi();
      String adressMac = peripheral.address();
      String rssiValue = std::to_string(rssi).c_str();
      //Serial.println(rssiValue);
      getSignalQuality(rssi);
      postDataTowebServer(rssiValue, adressMac + "-" + peripheral.advertisedServiceUuid());
    }
    else
    {

      // device peripheral is not available
    }
  }
}
