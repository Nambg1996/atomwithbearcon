#include <WiFi.h>

//const char* ssid = "ASUKA5";
//const char* password = "2019kyohei2019";
const char* ssid = "Galaxy A71A1D5";
const char* password = "ycup4087";

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    
   
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());
}

void loop() {
  // your code goes here

    Serial.println("Wifi localIp: ");
    Serial.println(WiFi.localIP());
  
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
    delay(5000);

    while (WiFi.status() == WL_DISCONNECTED ) {
    Serial.println("Wifi is lost");
    WiFi.begin(ssid, password);
    delay(500);

  }



}