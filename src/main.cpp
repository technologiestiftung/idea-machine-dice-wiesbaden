#include <Arduino.h>

#include <Adafruit_MPU6050.h>
#include <PubSubClient.h>

#include<WiFi.h>

#include "config.h"
#include "function.h"
#include "config_hidden.h"



void setup() {

  Serial.begin(9600); // Serielle Kommunikation initialisieren - 9600 bits pro Sekunde

  if (!mpu.begin()) { // Wenn MPU6050 nicht erkannt wird
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // Beschleunigungsbereich auf +-8G einstellen
  mpu.setGyroRange(MPU6050_RANGE_500_DEG); // Gyrobereich auf +- 500 deg/s einstellen
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); // Filterbandbreite auf 21 Hz einstellen

  delay(100); // Verzögerung zur Stabilität
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500); 
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP-Address of ESP32 Mini module: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  unsigned long now = millis();
  client.loop();

  if (now - lastSend > INTERVAL) {
    lastSend = now;
    readSensor();
    sending_data();
  }

}




