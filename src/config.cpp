#include "config.h"

// Hier werden die Variablen *definiert* (nur einmal!)
Adafruit_MPU6050 mpu;

/*
const char* ssid = "Deine SSID";
const char* password = "Dein Passwort";

IPAddress ip("Deine IP-Adresse");
IPAddress gateway("Deine Gateway-Adresse");
IPAddress subnet("Deine Subnetzmaske");

const char* mqtt_server = "Dein MQTT Server IP"; 
*/
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

float x_achse = 0;
float y_achse = 0;
float z_achse = 0;

int last_side = 0;

String message = "";
String messageTemp = "";


const char name[] = "esp32 mini two";

const unsigned long updateInterval = 200;

sensors_event_t a, g, temp;

int side = 0;
char sideString [4];