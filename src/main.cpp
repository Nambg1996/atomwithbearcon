#include <WiFi.h>
#include <iostream>
#include <iostream>
#include <ArduinoHttpClient.h>
#include <Ethernet.h>
#include <HTTPClient.h>

//const char* ssid = "ASUKA5";
//const char* password = "2019kyohei2019";
const char* ssid = "Galaxy A71A1D5";
const char* password = "ycup4087";

const char* serverAddress = "www.example.com";
const int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

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
    // make 


 


  }

  
    if (!client.connect("192.168.45.120", 80)) {
    Serial.println("Connection failed");
    return;
  }else{

 if (!client.connect("192.168.45.120", 80)) {
    Serial.println("Connection failed");
    return;
  }
  String payload = "rssi=10&adress=abc";
  client.print(String("POST /php/index.php HTTP/1.1\r\n") +
               "Host: 192.168.45.120\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: " + payload.length() + "\r\n" +
               "Connection: close\r\n\r\n" +
               payload);
  while(client.available() == 0) {
    delay(1);
  }
  String response = client.readString();
  Serial.println(response);
  delay(10000);
    





  }

  


}