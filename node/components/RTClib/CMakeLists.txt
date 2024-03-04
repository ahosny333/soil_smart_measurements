cmake_minimum_required(VERSION 3.5)

set(includedirs
  src/
  )

set(srcs
  src/RTC_DS1307.cpp
  src/RTC_DS3231.cpp
  src/RTC_Micros.cpp
  src/RTC_Millis.cpp
  src/RTC_PCF8523.cpp
  src/RTC_PCF8563.cpp
  src/RTClib.cpp
  )

idf_component_register(SRCS ${srcs} 
                    INCLUDE_DIRS ${includedirs}
                    REQUIRES "arduino" "Adafruit_BusIO")
project(RTClib)
