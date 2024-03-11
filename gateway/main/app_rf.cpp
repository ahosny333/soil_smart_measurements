#include <ModbusRTU.h>
//#include "main.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "app_rf.h"

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
Data_Package data; 


void rf_init() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void rf_get_data() {
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
  }
}

