#include <config.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
const uint16_t port = 80;
const char * host = "192.168.1.183"; // ip or dns


void setup() {
    Serial.begin(115200);

    ESP8266WiFiMulti WiFiMulti;

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("WIFI_SSID", "WIFI_PASS");

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi...");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}



      void hue(String body, uint8_t light, String hueIp, String HUEAPIKEY){

        Serial.print("connecting to ");
        Serial.println(host);
        WiFiClient client;

        if (client.connect(hueIp, 80)) {

          String path =
              "PUT /api/" + HUEAPIKEY + "/lights/" + String(light) + "/state";
          client.println(" HTTP/1.1");
          client.println("Cache-Control: no-cache");
          client.println("Content-Type: application/json");
          client.print("Content-Length: ");
          client.println(body.length());
          client.println();
          client.print(body);
          Serial.println("sent");  // command executed
      }



    while (client.connected()) {
      if (client.available()) {
        char str = client.read();
        Serial.print(str);
      }
    }

    unsigned long currentMillis = millis(), previousMillis = millis();
    long interval = 2000;

    while (!client.available()) {

      if ((currentMillis - previousMillis) > interval) {

        Serial.println("Timeout");
        client.stop();
        return;
      }
      currentMillis = millis();
    }



    Serial.println("wait 5 sec...");
    delay(5000);
  }

  void loop(){
    String body = ("{\"on\":false}");
    hue(body, 1, HUEIP, HUEAPIKEY);
    }
