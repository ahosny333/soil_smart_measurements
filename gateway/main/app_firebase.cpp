#include <ArduinoJson.h>
#include <WiFi.h>   
#include "Arduino.h"
#include <IOXhop_FirebaseESP32.h>
#include <stdio.h>
#include "app_firebase.h"
#include "app_rf.h"
#include "main.h"

extern Data_Package data; 

///Devices/1008/[ControllerID]-[DeviceID]/
// : 2041 - 2042 - 2043 - 2045 - 2046 
const char MT_M[] = "/Devices/1008/1112-2041/value";
const char MT_T[] = "/Devices/1008/1112-2042/value";
const char MT_M_update[] = "/Devices/1008/1112-2041/cmd";
const char MT_T_update[] = "/Devices/1008/1112-2042/cmd";

const char T_M_EC_S_EC[] = "/Devices/1008/1112-2043/value";
const char T_M_EC_S_S[] = "/Devices/1008/1112-2045/value";
const char T_M_EC_S_EC_update[] = "/Devices/1008/1112-2043/cmd";
const char T_M_EC_S_S_update[] = "/Devices/1008/1112-2045/cmd";

const char T_M_EC_S_M[] = "/Devices/1008/1112-2044/value";
const char T_M_EC_S_M_update[] = "/Devices/1008/1112-2044/cmd";

uint32_t last_rec =0;

void firebase_init()
{
  Firebase.begin(FIREBASE_Host, FIREBASE_authorization_key);
}

void firebase_update_readings()
{
  if(millis() - last_rec > 30000 )
    {
      last_rec = millis();
      DEBUG_PRINTLN("send to firebase");
      Serial.println("send to firebase");
      Firebase.setString(MT_M, String(data.MT_M));
      Firebase.setString(MT_M_update, "r");

      Firebase.setString(MT_T, String(data.MT_T));
      Firebase.setString(MT_T_update, "r");
      DEBUG_PRINTLN(data.MT_T);
      DEBUG_PRINTLN(data.MT_M);

      Firebase.setString(T_M_EC_S_EC, String(data.T_M_EC_S_EC));
      Firebase.setString(T_M_EC_S_EC_update, "r");

      Firebase.setString(T_M_EC_S_S, String(data.T_M_EC_S_S));
      Firebase.setString(T_M_EC_S_S_update, "r");

      Firebase.setString(T_M_EC_S_M, String(data.T_M_EC_S_M));
      Firebase.setString(T_M_EC_S_M_update, "r");
    }
}