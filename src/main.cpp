#include <WiFi.h>
#include <iostream>
#include <iostream>
#include <ArduinoHttpClient.h>
#include <Ethernet.h>
#include <WiFi101.h>
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

  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(192, 168, 1, 177);

  HttpClient client = HttpClient(wifi, serverAddress, port);

  // Initialize the HTTP client
 

 


  
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
    delay(5000);

  }



}