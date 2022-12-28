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

using namespace std;


void runFunction() {
  // Your function code goes here
  Serial.println("Function ran!");
}

void setup() {
  Serial.begin(115200);
  setupWifi(ssid, password);
   BLE.begin();

   // start scanning for peripherals
   BLE.scan();



}

void loop() {
    // your code goes here
    //runFunctionAfterDelay(5000, runFunction);
    //wifiReconnectWhenLost(ssid, password);

   

    BLEDevice peripheral = BLE.available();

   Serial.println("peripheral ::!");
   Serial.println(peripheral.advertisedServiceUuid());

        if (peripheral.advertisedServiceUuid()=="feaa") {
          // get RSSI value for the peripheral
          int rssi = peripheral.rssi();
          String adressUUId= peripheral.address();

          // print RSSI value
          Serial.print("RSSI: ");
          Serial.println(rssi);
          Serial.print("Adress: ");
          Serial.println(adressUUId);
          delay(1000);
        }

       
   
   

    

    String rssi = "10";
    String address = "abc";
    //postDataTowebServer(rssi,address);



    }



