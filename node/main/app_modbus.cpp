#include <ModbusRTU.h>
#include "main.h"


ModbusRTU mb;
uint16_t regs[5];
bool HRead(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  Serial.print("Request result: 0x");
  Serial.print(event, HEX);
  return true;
}

void modbus_init()
{
  Serial2.begin(9600, SERIAL_8N1);
  mb.begin(&Serial2);
  mb.master();
}

void read_sensors_values()
{

  #ifdef NPK_SENSOR
    if (!mb.slave()) {    // Check if no transaction in progress
    mb.readHreg(NPK_SENSOR_ADDR, 0x00, regs, 3, HRead); // Send Read Hreg from Modbus Server
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(10);
    }
    Serial.println(regs[0]);
    Serial.println(regs[1]);
    Serial.println(regs[3]);
    }
    delay(1000);
  #endif

}

