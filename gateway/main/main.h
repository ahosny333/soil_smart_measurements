#ifndef MAIN_H_
#define MAIN_H_

#define CLIENT "ELCADY"
#define FIRMWARE_VERSION "1.1"

#define ssid     "Agrimachinery_B"       // replace with your SSID
#define password  "Agri@131"          //replace with your Password
// #define ssid     "eng.hosni"       // replace with your SSID
// #define password  "ahmedhosnyohaj"          //replace with your Password

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
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTDEC(x)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTLNDEC(x)
#endif



#endif