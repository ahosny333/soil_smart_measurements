#include "Arduino.h"
#include <WiFi.h>
#include "main.h"

#define wm_reconnect_interval 20000
uint32_t wm_reconnect_timer =0;
bool wifi_connected = false;

void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  DEBUG_PRINTLN("Connected To The WiFi Network");
}
 
void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  DEBUG_PRINT("Local ESP32 IP: ");
  DEBUG_PRINTLN(WiFi.localIP());
  wifi_connected = true;
}
 
void WiFi_Disconnected_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  DEBUG_PRINTLN("Disconnected From WiFi Network");
  wifi_connected = false;
  // Attempt Re-Connection
  if(millis() - wm_reconnect_timer > wm_reconnect_interval)
  {
    DEBUG_PRINTLN("try to reconnect");
    WiFi.begin(ssid, password);
    wm_reconnect_timer = millis();
  }
}


void wm_init()
{
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(ConnectedToAP_Handler, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(GotIP_Handler, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFi_Disconnected_Handler, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.begin(ssid, password);                                       
  DEBUG_PRINT("Connecting to WIFI");
  while (WiFi.status() != WL_CONNECTED) {
    DEBUG_PRINT(".");
    delay(500);
  }

}
