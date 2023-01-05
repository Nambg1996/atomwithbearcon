
void setupWifi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
  }
}


void wifiReconnectWhenLost(const char* ssid, const char* password) {
  while (WiFi.status() == WL_DISCONNECTED) {
    Serial.println("Wifi connection lost. Attempting to reconnect...");
    WiFi.begin(ssid, password);
    delay(5000);
  }
  Serial.println("wifi still active");
}