#include <WiFi.h>
#include <ArduinoBLE.h>
#include <ArduinoHttpClient.h>
#include <Ethernet.h>
#include <HTTPClient.h>
#include "setting.h"
#include "runfunctionAfterDelays.h"
#include "myWifi.h"
#include <iostream>
#include "postDataToServer.h"
#include <string>
#include <random>
#include <array>
#include <cstdlib>
#include <ctime>
#include <FastLED.h>
#include <M5Atom.h>
using namespace std;

unsigned long previousMillis = 0;

void runFunction() {
  // Your function code goes here
  Serial.println("Function ran!");

  BLE.stopScan();
  Serial.println("stop scan : ");
  delay(500);
  BLE.begin();
  Serial.println("scan again scan : ");
  BLE.scan();
  delay(1000);
}

hw_timer_t * hwtimer = NULL;

void IRAM_ATTR scanBLEAgain() {
  // Toggle the LED every time the timer triggers
  //M5.Atom.toggle();
   Serial.println("Function ran!");

  /* BLE.stopScan();
  Serial.println("stop scan : ");
  delay(500);
  BLE.begin();
  Serial.println("scan again scan : ");
  BLE.scan(); */
  


}




void getSignalQuality(int rssi) {
  if (rssi >= -75 && rssi <= -28) {
    
    digitalWrite(33, HIGH);// light is on

    delay(3000);
                                                                
  } else {
     digitalWrite(33, LOW);// light is off
  }
}

void setup() {
  //M5.begin(true, true, true);

  pinMode(33, OUTPUT);   // set pin 33 to output mode
  digitalWrite(33, LOW);// light is off
  Serial.begin(115200);
  setupWifi(ssid, password);
  BLE.begin();

   // start scanning for peripherals
   BLE.scan();

   
  hwtimer = timerBegin(1, 80, true);
  timerAttachInterrupt(hwtimer, &scanBLEAgain, true);
  timerAlarmWrite(hwtimer, 1000, true);
   //timerAlarmEnable(hwtimer);



}

void loop() {


   unsigned long currentMillis = millis();

  // Check if 1 second has passed
  if (currentMillis - previousMillis >= 8000) {
    // Reset the elapsed time tracker
    BLE.stopScan();
    Serial.println("stop scan : ");
    delay(500);
    BLE.begin();
    Serial.println("scan again scan : ");
    BLE.scan();
    previousMillis = currentMillis;

   
  }else{


    wifiReconnectWhenLost(ssid, password);
    BLEDevice peripheral = BLE.available();
    bool deviceTargetScan = peripheral.advertisedServiceUuid()==uuidBeacon||peripheral.address()==macBeacon;
   

        if (deviceTargetScan) {

          Serial.println("scan ok: ");
          // get RSSI value for the peripheral
          int rssi = peripheral.rssi();
          String adressMac= peripheral.address();
          String rssiValue = std::to_string(rssi).c_str();
          Serial.println(rssiValue);
          getSignalQuality(rssi);
          

          //postDataTowebServer(rssiValue,adressMac+"-"+peripheral.advertisedServiceUuid());
 
   
        }else{

                  //runFunctionAfterDelay(5000, runFunction);   

          }



  }


 
    

                             

 
                          
                          
     }

       
          



    






