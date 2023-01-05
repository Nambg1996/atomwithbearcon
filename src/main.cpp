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
using namespace std;


void runFunction() {
  // Your function code goes here
  Serial.println("Function ran!");
}

void getSignalQuality(int rssi) {
  if (rssi >= -60 && rssi <= -34) {
    
    digitalWrite(33, HIGH);
  } else if (rssi >= -80 && rssi < -61) {
    digitalWrite(33, HIGH);
  } else if (rssi <-81 && rssi >= -100) {
    digitalWrite(33, LOW);                                                               
  } else {
     digitalWrite(33, LOW);
  }
}

void setup() {

  pinMode(33, OUTPUT);   // set pin 33 to output mode
  digitalWrite(33, LOW);
  Serial.begin(115200);
  setupWifi(ssid, password);
   BLE.begin();

   // start scanning for peripherals
   BLE.scan();




}

void loop() {
    // your code goes here
    //runFunctionAfterDelay(5000, runFunction);
  
    wifiReconnectWhenLost(ssid, password);

   

    BLEDevice peripheral = BLE.available();

   Serial.println("peripheral ::!");
   Serial.println(peripheral.advertisedServiceUuid());

        if (peripheral.advertisedServiceUuid()=="feaa"||peripheral.address()=="cd:09:fe:8f:7f:1a") {

          
          // get RSSI value for the peripheral
          int rssi = peripheral.rssi();
          String adressMac= peripheral.address();

          // print RSSI value
          Serial.print("RSSI: ");
          Serial.println(rssi);
          Serial.print("Adress: ");
          Serial.println(adressMac);
          Serial.println("type rssi:");

          String rssiValue = std::to_string(rssi).c_str();
          //std::string s = std::to_string(rssi);
          getSignalQuality(rssi);
          Serial.println(rssiValue);
          postDataTowebServer(rssiValue,adressMac+"-"+peripheral.advertisedServiceUuid());
          delay(milidelay);
   
        }else{

          digitalWrite(33, LOW);

        }

  
    



    }






