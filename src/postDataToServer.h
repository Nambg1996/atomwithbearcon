WiFiClient wifi;
HttpClient client = HttpClient(wifi, localhost, port);

void postDataTowebServer(String rssi, String address) {

String payload = "rssi="+rssi+"&adress="+address;

    if (!client.connect(localhost, port)) {
    Serial.println("Connection failed");
    return;
  }else{

 if (!client.connect(localhost, port)) {
    Serial.println("Connection failed");
    return;
  }


   
           client.print(String(filedirectory) +
               "Host: " + localhost + "\r\n" +
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

  // function code goes here
}