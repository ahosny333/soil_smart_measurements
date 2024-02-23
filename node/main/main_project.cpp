
#include "Arduino.h"
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ModbusRTU.h>

ModbusRTU mb;


void setup(){
  Serial.begin(115200);
  while(!Serial){
    ; // wait for serial port to connect
  }
}

void loop(){
    Serial.println("loop");
    delay(1000);
}