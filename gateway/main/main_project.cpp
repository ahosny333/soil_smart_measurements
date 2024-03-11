
#include "Arduino.h"
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ModbusRTU.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "app_rf.h"
#include "app_firebase.h"

const char *ssid = "ICITY";
const char *password = "iEgyptCity";


void setup(){
  Serial.begin(115200);
  while(!Serial){
    delay(1000);
  }
  rf_init();
  WiFi.begin(ssid, password);                                       
  Serial.print("Connecting to WIFI");
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  }

  firebase_init();
}

void loop(){
    Serial.println("loop");
    delay(1000);
    if(rf_get_data())
    {
      firebase_update_readings();
    }
}