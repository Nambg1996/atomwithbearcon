#include <ArduinoBLE.h>
#include <BLEDevice.h>


// Declare an BLEDevice object
BLEDevice device;

void setup() {
  // Initialize the BLE library
  BLE.begin();

  // Scan for BLE devices
  BLE.scan();
}

void loop() {
  // Poll the BLE library for events
  device.poll();

  // Check if the device is connected
  if (!device.connected()) {
    // If the device is not connected, try to connect to it
    device.connect();
  }

int rssi = device.rssi();

// If the RSSI value is greater than or equal to -60, the device is considered "near"
if (rssi >= -60) {
  Serial.println("near");
}
// Otherwise, the device is considered "far"
else {
  Serial.println("far");
}

}