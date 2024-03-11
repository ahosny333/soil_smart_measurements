#include <ArduinoJson.h>
#include <IOXhop_FirebaseESP32.h>
#include <stdio.h>
#include "app_firebase.h"

void firebase_init()
{
  Firebase.begin(FIREBASE_Host, FIREBASE_authorization_key);
}

