#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_MPU6050.h>

// Variablen deklarieren (nicht definieren)
extern Adafruit_MPU6050 mpu;

extern const char* ssid;
extern const char* password;

extern IPAddress ip;
extern IPAddress gateway;
extern IPAddress subnet;

extern const char* mqtt_server;


extern WiFiClient espClient;
extern PubSubClient client;

extern long lastMsg;
extern char msg[50];


extern float x_achse;
extern float y_achse;
extern float z_achse;

extern int last_side;


extern String message;
extern String messageTemp;

extern const char name[];
extern const unsigned long updateInterval;


extern char sideString [4];

extern int side;
extern sensors_event_t a, g, temp;

extern float last_x, last_y, last_z;
extern float total_movement;

extern unsigned long startTime;
const unsigned long INTERVAL;
unsigned long now;

#endif


