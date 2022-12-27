

#include <ArduinoBLE.h>
#include <WiFi.h>

/* #include <libpq-fe.h>
#include <stdlib.h>
#include <string.h>
 */


void setup()
{

 
  Serial.begin(115200);
  WiFi.begin("ASUKA5", "2019kyohei2019");
  while (!Serial);

  // begin initialization
  if (!BLE.begin())
  {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1)
      ;
  }
  // start scanning for peripherals
  BLE.scanForUuid("feaa");
}

void loop()
{
  // check if a peripheral has been discovered

  
  BLEDevice peripheral = BLE.available();


  if (peripheral)
  {
    // discovered a peripheral, print out address, local name, and advertised service
    // Serial.print("Found ");
    // Serial.print(peripheral.address());
    // Serial.print(" '");
    // Serial.print(peripheral.localName());
    // Serial.print("' ");
    // Serial.print(peripheral.advertisedServiceUuid());
    // Serial.println();
     
       BLE.stopScan();


       Serial.println("status of conected ...");
      
       

       if (peripheral.connect()) {
          Serial.println("Connected");

     while (1){

    

       Serial.print("this is a device for beacon ");
      // BLE.stopScan();
      Serial.print("RSSI: ");
      Serial.println(peripheral.rssi());
      Serial.println("Adress: ");
      Serial.println(peripheral.address());
      delay(3000);
      BLEService batteryService = peripheral.service("180f");

    if (batteryService) {
      // use the service
      if (batteryService.hasCharacteristic("2a19")) {
        Serial.println("Battery service has battery level characteristic");
      }
    } else {
      Serial.println("Peripheral does NOT have battery service");
    }

     }



     
  if (WiFi.status() == WL_CONNECTED) {
    // WiFi is connected
     Serial.println("WiFi is connected");


  } else {
    // WiFi is not connected
    Serial.println("WiFi is not connected");
  }
     





    } else {
      Serial.println("Failed to connect!");
      return;
    } 
      


      
      // discover peripheral attributes
     
// battery

  }

  
  
}
