#ifndef MAIN_H_
#define MAIN_H_


#define CLIENT "TEST"
#define NODE_ID 1
#define FIRMWARE_VERSION "1.1"

//#define DEBUG 1
#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x); Serial.flush()
#define DEBUG_PRINTDEC(x) Serial.print(x, DEC);Serial.flush()
#define DEBUG_PRINTLN(x) Serial.println(x);Serial.flush()
#define DEBUG_PRINTLNDEC(x) Serial.println(x, DEC);Serial.flush()
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTLNDEC(x)
#endif

#define NPK_SENSOR_ADDR 0x01
#define EC_SENSOR_ADDR 0x02
#define MT_SENSOR_ADDR 0x03
#define PH_SENSOR_ADDR 0x04
#define MT2_SENSOR_ADDR 0x05
#define MT3_SENSOR_ADDR 0x06


#define NPK_SENSOR 1
#define EC_SENSOR 1
#define MT_SENSOR 0
#define PH_SENSOR 0
#define MT2_SENSOR 0
#define MT3_SENSOR 0

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define INITIAL_AP_TIME 60000
#define AP_MODE_PIN 21
// #define TIME_TO_SLEEP  60        /* time to sleep in seconds*/
// #define WAKE_UP_TIME    60000

#endif