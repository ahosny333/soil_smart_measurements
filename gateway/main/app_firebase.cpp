#include <ArduinoJson.h>
#include <WiFi.h>    
#include <IOXhop_FirebaseESP32.h>
#include <stdio.h>
#include "app_firebase.h"
#include "app_rf.h"

extern Data_Package data; 

const char MT_M[] = "/Devices/1002-2001/value";
const char MT_T_[] = "/Devices/1002-2351/value";
const char MT_M_update[] = "/Devices/1002-2001/cmd";
const char MT_T_update[] = "/Devices/1002-2351/cmd";

const char T_M_EC_S_EC[] = "/Devices/1112-2041/value";
const char T_M_EC_S_S[] = "/Devices/1112-2042/value";
const char T_M_EC_S_EC_update[] = "/Devices/1112-2041/cmd";
const char T_M_EC_S_S_update[] = "/Devices/1112-2042/cmd";


void firebase_init()
{
  Firebase.begin(FIREBASE_Host, FIREBASE_authorization_key);
}

void firebase_update_readings()
{
  Firebase.setString(MT_M, String(data.MT_M));
  Firebase.setString(MT_M_update, "r");

  Firebase.setString(MT_T_, String(data.MT_T));
  Firebase.setString(MT_T_update, "r");

  Firebase.setString(T_M_EC_S_EC, String(data.T_M_EC_S_EC));
  Firebase.setString(T_M_EC_S_EC_update, "r");

  Firebase.setString(T_M_EC_S_S, String(data.T_M_EC_S_S));
  Firebase.setString(T_M_EC_S_S_update, "r");
}