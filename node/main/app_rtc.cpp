#include "main.h"
#include <ArduinoJson.h>
#include <RTClib.h>

RTC_DS3231 rtc;
bool rtc_exist = false;
DateTime now;
bool rtc_done = false;
extern bool flashUpdateRequest;


void RTC_init() {
  if (! rtc.begin()) {
    DEBUG_PRINTLN("RTC module is NOT found");
    rtc_exist = false;
  }
  else
  {
    
    DEBUG_PRINTLN("RTC module is found");
    if(rtc_done == false)
    {
      DEBUG_PRINTLN("RTC NOT DONE SO INIT WITH COMPILE");
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      rtc_done = true;
      flashUpdateRequest = true;
    }
    else{
      DEBUG_PRINTLN("RTC used saved value");
    }

    
    rtc_exist = true;
    
  }
}

void rtc_get_now_date() {
  now = rtc.now();
  //Serial.println(now.hour());
}

