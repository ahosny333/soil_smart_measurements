#ifndef MAIN_H_
#define MAIN_H_

#define CLIENT "ELKADY"
#define NODE_ID 1
#define FIRMWARE_VERSION "1.1"

//#define DEBUG 1
#ifdef DEBUG
#define DEBUG_PRINT(x) \
    Serial.print(x);   \
    Serial.flush()
#define DEBUG_PRINTDEC(x) \
    Serial.print(x, DEC); \
    Serial.flush()
#define DEBUG_PRINTLN(x) \
    Serial.println(x);   \
    Serial.flush()
#define DEBUG_PRINTLNDEC(x) \
    Serial.println(x, DEC); \
    Serial.flush()
#define DEBUG_PRINTLNHEX(x) \
    Serial.println(x, HEX); \
    Serial.flush()
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTLNDEC(x)
#define DEBUG_PRINTLNHEX(x)
#endif

// Number of Retry Reading
#define max_retries 1 //////////////////////////////////////////////
//##################################################################
// Sensor Address 
#define NPK_SENSOR_ADDR 0x01 ////////////////////TRUE
#define MT_SENSOR_ADDR 0x03 /////////////////////TRUE
#define T_M_EC_S_SENSOR_ADDR 0x05 ///////////////TRUE

#define EC_SENSOR_ADDR 0x02 /////////////////////TRUE
#define PH_SENSOR_ADDR 0x04

//####################################################################
// Enable Sensor 
// #define NPK_SENSOR 1 ////////////////////////////done
#define MT_SENSOR 1 /////////////////////////////done
#define T_M_EC_S_SENSOR 1 ///////////////////////done

// #define EC_SENSOR 1
// #define PH_SENSOR 1

// to set slave id use address 254 and start address 201 in qmodmaster fc = 0x06 then write the required id to 5

//####################################################################
// Register 

#ifdef NPK_SENSOR//////////////////////////////////done
#define NPK_SENSOR_START_ADD 0x001E 
#endif

#ifdef  MT_SENSOR//////////////////////////////////done
#define MT_SENSOR_START_ADD 0x0000// CHANEABLE
#endif

#ifdef T_M_EC_S_SENSOR/////////////////////////////done
#define T_M_EC_S_SENSOR_START_ADD 0x0000
#endif

//////////////////////////////////////////////////////////

#ifdef  EC_SENSOR//////////////////////////////////done
#define EC_SENSOR_START_ADD 0x0000
#endif

#ifdef  PH_SENSOR//////////////////////////////////done
#define PH_SENSOR_START_ADD 0x0000
#endif


















#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define INITIAL_AP_TIME 60000
#define AP_MODE_PIN 19
#define sd_card_ss_pin 27
// #define TIME_TO_SLEEP  60        /* time to sleep in seconds*/
// #define WAKE_UP_TIME    60000

#endif