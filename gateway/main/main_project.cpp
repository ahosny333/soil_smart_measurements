
#include "Arduino.h"
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ModbusRTU.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "main.h"
#include "app_rf.h"
#include "app_firebase.h"
#include "app_wm.h"

extern bool wifi_connected;

void setup(){
  Serial.begin(115200);
  while(!Serial){
    delay(1000);
  }
  rf_init();
  wm_init();
  firebase_init();
}

void loop(){
    DEBUG_PRINTLN("loop");
    //Serial.println("serial loop");
    delay(500);
    if(rf_get_data() && wifi_connected)
    {
      
        firebase_update_readings();
  
    
    }
}