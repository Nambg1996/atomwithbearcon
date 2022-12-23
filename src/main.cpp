#include <ArduinoBLE.h>
#include <BLEDevice.h>

// Declare an BLEDevice object


void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Serial.println("Initializing BLE device...");
  BLE.begin();

  Serial.println("Scanning for devices...");
  BLE.scan();

  BLE.setLocalName("M5-stack");
  // ...  
  // start advertising
  BLE.advertise();

  
}

void loop() {
  BLE.poll();

  if (BLE.available()) {
    BLEDevice device = BLE.available();
    Serial.print("Device found: ");
    Serial.println(device.address());
    Serial.print("RSSI: ");
    Serial.println(device.rssi());
    Serial.print("has local Name: ");
    Serial.println(device.hasLocalName());
//
    /* Serial.print("hasCharacteristic: ");
    Serial.println(device.hasCharacteristic()); */

    Serial.print("advertisedServiceUuid: ");
    Serial.println(device.advertisedServiceUuid());

   /*  Serial.print("characteristic: ");
    Serial.println(device.characteristic()); */

    Serial.print("device name: ");
    Serial.println(device.deviceName());
    

   
  }

delay(3000);


}