#include "Arduino.h"

#include "config.h"
#include "function.h"

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println(); 
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection......");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/input");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(100);
    }
  }
}

void readSensor()
{
  
  mpu.getEvent(&a, &g, &temp);
  long now = millis();
  if (now - lastMsg > updateInterval ) {
    lastMsg = now;
  
 
    if (a.acceleration.x >= +8) side = 5;
    if (a.acceleration.x <= -8) side = 2;
    if (a.acceleration.y >= +8) side = 4;
    if (a.acceleration.y <= -8) side = 3;
    if (a.acceleration.z >= +8) side = 1;
    if (a.acceleration.z <= -8) side = 6;

    }

  delay(100);
}


void sending_data()
{
    if (side != last_side) {

        last_side = side;
        itoa(side, sideString, 10);

        Serial.print("Neue Würfelseite: ");
        Serial.println(sideString);

        client.publish("dice/one", sideString);
    }
 
}
