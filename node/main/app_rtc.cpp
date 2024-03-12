#include "main.h"
#include <ArduinoJson.h>
#include <RTClib.h>

RTC_DS3231 rtc;
bool rtc_exist = false;
DateTime now;


void RTC_init() {
  if (! rtc.begin()) {
    Serial.println("RTC module is NOT found");
    rtc_exist = false;
  }
  else
  {
    Serial.println("RTC module is found");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    rtc_exist = true;
  }
}

void rtc_get_now_date() {
  now = rtc.now();
}

