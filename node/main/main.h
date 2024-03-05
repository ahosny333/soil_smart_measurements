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

// modbus settings
#define max_retries 5

#define NPK_SENSOR_ADDR 0x01
#define EC_SENSOR_ADDR 0x02
#define MT_SENSOR_ADDR 0x03
#define PH_SENSOR_ADDR 0x04

#define T_M_EC_S_SENSOR_ADDR 0x05 //TRUE



// #define NPK_SENSOR 
// #define EC_SENSOR 
// #define MT_SENSOR 
// #define PH_SENSOR 
#define T_M_EC_S_SENSOR 1   // to set slave id use address 254 and start address 201 in qmodmaster fc = 0x06 then write the required id to 5


#ifdef NPK_SENSOR
#define NPK_SENSOR_START_ADD 0x001E////////
#endif

#ifdef EC_SENSOR
#define EC_SENSOR_START_ADD 0x002E
#endif

#ifdef T_M_EC_S_SENSOR
#define T_M_EC_S_SENSOR_START_ADD 0x0000
#endif



#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define INITIAL_AP_TIME 60000
#define AP_MODE_PIN 21
#define sd_card_ss_pin 5
// #define TIME_TO_SLEEP  60        /* time to sleep in seconds*/
// #define WAKE_UP_TIME    60000

#endif