
#include "Arduino.h"
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ModbusRTU.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "main.h"
#include "app_modbus.h"
#include "credentials.h"


uint32_t wake_timer = 0;
uint16_t TIME_TO_SLEEP;      /* time to sleep in seconds*/
uint16_t WAKE_UP_TIME;       /* time to wake in sec */

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

// Let these addresses be used for the pair
uint8_t address[][6] = { "1Node", "2Node" };
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1;  // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX role, false = RX role

// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
float payload = 0.0;





void setup(){
  Serial.begin(115200);
  while(!Serial){
    ; // wait for serial port to connect
  }
  readSystemVariables();
  wake_timer = millis();
  Serial.println("starting");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  modbus_init();
  data_serializer();
}

void loop(){

   while( millis() - wake_timer < WAKE_UP_TIME *1000)
   {   
    
    Serial.println("inside waking perod");    
    delay(5000);
   }
    
    Serial.println("start sleep");
    esp_deep_sleep_start();
    Serial.println("loop");    // can not come here
}