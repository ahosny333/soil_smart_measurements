
#include "Arduino.h"
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ModbusRTU.h>
#include <SPI.h>
#include <ESPmDNS.h>
#include <ESP32Time.h>
#include "printf.h"
#include "RF24.h"
#include "main.h"
#include "app_modbus.h"
#include "credentials.h"
#include "app_wifi.h"
#include "app_webserver_idf.h"
#include "RTClib.h"
#include "app_sd.h"
#include "app_rf.h"
#include "app_rtc.h"

// ESP32Time rtc;
// ESP32Time rtc(0);
// bool rtc_done = false;
uint32_t wake_timer = 0;
uint16_t TIME_TO_SLEEP; /* time to sleep in seconds*/
uint16_t WAKE_UP_TIME;  /* time to wake in sec */
extern char ap_name[30];
extern bool flashUpdateRequest;
int x = 3;
void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for serial port to connect
  }
  readSystemVariables();
  RTC_init();
  wake_timer = millis();
  Serial.println("starting");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  sd_card_init();
  modbus_init();
  rf_init();
  wm_init();
  if (WiFi.getMode() == WIFI_AP)
  {
    DEBUG_PRINTLN("access point mode");
    if (MDNS.begin(ap_name))
    {
      MDNS.addService("http", "tcp", 80);
    }
    else
    {
      Serial.println("Error starting mDNS");
    }
    webserver_task();
  }
}

void loop()
{
  while (x>0)
  {
    x-=1;
    Serial.println("inside waking period");
    read_sensors_values();
    data_serializer();
    rf_send_data();
    delay(6000);
  }
  
    


  // if start ap for calibration
  if (WiFi.getMode() == WIFI_AP)
  {
    while( millis() - wake_timer < WAKE_UP_TIME *1000)
    {
      read_sensors_values();
      data_serializer();
      //rf_send_data();
      delay(3000);
      if (flashUpdateRequest)
      {
        flashUpdateRequest = false;
        saveSystemVariables();
      }

    }

  }

  Serial.println("start sleep");
  esp_deep_sleep_start();
  Serial.println("loop"); // can not come here
}