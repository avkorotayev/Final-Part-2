#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "Ant";
const char* password = "2851kkkk";
const char* mqtt_server = "34.19.86.162";

WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_setup() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    client.setServer(mqtt_server, 1883);
    while (!client.connected()) {
        client.connect("ESP32Server");
    }
}

void mqtt_send(const char* message) {
    client.publish("mud/roomdesc", message);
    client.loop();
}
