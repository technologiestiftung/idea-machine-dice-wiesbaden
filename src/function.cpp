#include "Arduino.h"

#include "config.h"
#include "function.h"
#include "config_hidden.h"

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
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Last-Will-Message: Beim Disconnect wird "getrennt" gesendet
    if (client.connect("espClientdice_Pink", "dice/pink/status", 0, true, "getrennt")) {
      Serial.println("connected");
      // Nach erfolgreicher Verbindung "verbunden" senden
      client.publish("dice/pink/status", "verbunden", true);
      client.subscribe("esp32/input");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 milliseconds");
      delay(500);
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
    
  itoa(side, sideString, 10);
  Serial.print("Neue Würfelseite: ");
  Serial.println(sideString);
  client.publish("dice/pink", sideString);
 
}

void diceing ()
{
    total_movement =
      abs(a.acceleration.x - last_x) +
      abs(a.acceleration.y - last_y) +
      abs(a.acceleration.z - last_z);

  last_x = a.acceleration.x;
  last_y = a.acceleration.y;
  last_z = a.acceleration.z;

  Serial.print("total_movement: ");
  Serial.println(total_movement);
}