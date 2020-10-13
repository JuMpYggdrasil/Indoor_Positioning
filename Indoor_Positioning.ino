#include <ESP8266WiFi.h>

WiFiServer server(80);

String line;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP_01n1");

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client){
    return;
  }

  Serial.println("New client");
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      if (c == '\r') {
        Serial.println(line);
        line = "";
        break;
      } else if (c == '\n') {
        // Pass {new line}
      } else {
        line += c; 
      }
    }
  }

  delay(1);
  client.stop();
  Serial.println("Client disconnect");
}
