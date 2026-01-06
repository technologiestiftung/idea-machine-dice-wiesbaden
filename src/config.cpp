#include "config.h"

// Hier werden die Variablen *definiert* (nur einmal!)
Adafruit_MPU6050 mpu;


const char* ssid = "ts.berlin Guest";
const char* password = "berlin@digital";

IPAddress ip(192,168,133,250);
IPAddress gateway(192,168,133,1);
IPAddress subnet(255,255,255,0);

const char* mqtt_server = "192.168.133.68";

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


const char name[] = "esp32 mini";

const unsigned long updateInterval = 200;

sensors_event_t a, g, temp;

int side = 0;
char sideString [4];