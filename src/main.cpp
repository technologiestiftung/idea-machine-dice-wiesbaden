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
  client.loop();
  readSensor();
  diceing();

  if (firstReading && side >= 1 && side <= 6) {
    sending_data();
    last_side = side;
    firstReading = false;
    Serial.println("First reading sent!");
    return;  // Springe zum nächsten Loop-Durchlauf
  }

  if (total_movement > 5.0) {
    isMoving = true;
    lastMovementTime = millis();
  } 
  else if (isMoving && (millis() - lastMovementTime) > SETTLE_TIME) {
    if (side != last_side && side != 0) {
      sending_data();
      last_side = side;
    }
    isMoving = false;
  }
  
  delay(50);

}




