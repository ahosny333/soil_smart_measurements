#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include "main.h"

char ap_name[30];
static uint32_t initial_ap_timer = 0;
char default_auth_password[] ="12345678";

void wm_activity_callback() {

  
  initial_ap_timer = millis();
}

void onStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  DEBUG_PRINTLN("Station connected ");
  wm_activity_callback();
}

void onStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  DEBUG_PRINTLN("Station disconnected ");
}


void setup_ap()
{
    WiFi.mode(WIFI_AP);
    delay(1000);
    WiFi.softAP(ap_name, default_auth_password);
    WiFi.onEvent(onStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STACONNECTED);
    // Call "onStationDisconnected" each time a station disconnects
    WiFi.onEvent(onStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);
}

void ap_loop() {

    if (millis() - initial_ap_timer > INITIAL_AP_TIME) {
      //write_eeprom_wm_state(STATION);
      //esp_reset();
    }
}

void wm_init()
{
    pinMode(AP_MODE_PIN, INPUT_PULLUP);
    delay(1000);
    if (digitalRead(AP_MODE_PIN) == LOW)
    {
        sprintf(ap_name, "%s_NODE_%d",CLIENT,NODE_ID);
        WiFi.setHostname(ap_name);
        setup_ap();
    }
}