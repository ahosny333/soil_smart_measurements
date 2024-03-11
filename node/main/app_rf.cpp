#include <ModbusRTU.h>
#include "main.h"
#include <ArduinoJson.h>
#include "app_modbus.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
extern Data_Package data; 



void rf_init() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void rf_send_data() {
  // Send the whole data from the structure to the receiver
  radio.write(&data, sizeof(Data_Package));
  //delay(500);
}

