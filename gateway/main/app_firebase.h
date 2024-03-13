#ifndef APP_firebase_H_
#define APP_firebase_H_
#include "Arduino.h"

#include <IOXhop_FirebaseESP32.h>
#include <stdio.h>

#define FIREBASE_Host  "makanty-53d43-default-rtdb.firebaseio.com/" //"agrimachinery-64483-default-rtdb.europe-west1.firebasedatabase.app/"                 // replace with your Firebase Host
#define FIREBASE_authorization_key "qsDNRdFyU2mBdHsugehnSxAOsAq3OjgQLRDXLd7A"//"siClksVtqW11OYX8AiR57z0rIHIe9Q3myAAOpXf7"

void firebase_init();
void firebase_update_readings();

#endif