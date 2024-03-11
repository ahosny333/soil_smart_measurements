
#include "Arduino.h"
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ModbusRTU.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "app_rf.h"
#include "app_firebase.h"



void setup(){
  Serial.begin(115200);
  while(!Serial){
    ; // wait for serial port to connect
  }
  rf_init();
  firebase_init();
}

void loop(){
    Serial.println("loop");
    delay(1000);
    // if(rf_get_data())
    // {

    // }
}