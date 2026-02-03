#ifndef FUNCTION_H
#define FUNCTION_H

#include<Arduino.h>


void callback(char* topic, byte* message, unsigned int length);
void reconnect();
void readSensor();
void sending_data();
void diceing ();

#endif