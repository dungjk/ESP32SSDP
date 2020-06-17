#include <WiFi.h>
#include <WebServer.h>
#include <ESP32SSDP.h>

const char* ssid = "********";
const char* password = "********";

WebServer HTTP(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting WiFi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(WiFi.waitForConnectResult() == WL_CONNECTED){

    Serial.printf("Starting HTTP...\n");
    HTTP.on("/index.html", HTTP_GET, [](){
      HTTP.send(200, "text/plain", "Hello World!");
    });
    HTTP.on("/description.xml", HTTP_GET, [](){
      SSDP.schema(HTTP.client());
    });
    HTTP.begin();

    Serial.printf("Starting SSDP...\n");
    SSDP
      .setSchemaURL("description.xml")
      .setHTTPPort(80)
      .setName("Philips hue clone")
      .setSerialNumber("001788102201")
      .setURL("index.html")
      .setModelName("Philips hue bridge 2012")
      .setModelNumber("929000226503")
      .setModelURL("http://www.meethue.com")
      .setManufacturer("Royal Philips Electronics")
      .setManufacturerURL("http://www.philips.com")
      .setDeviceType("upnp:rootdevice") //to appear as root device
      .begin();

    Serial.printf("Ready!\n");
  } else {
    Serial.printf("WiFi Failed\n");
    while(1) delay(100);
  }
}

void loop() {
  HTTP.handleClient();
  delay(1);
}
