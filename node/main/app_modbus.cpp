#include <ModbusRTU.h>
#include "main.h"


ModbusRTU mb;
uint16_t regs[5];

#ifdef NPK_SENSOR
  uint16_t sn_N,sn_P,sn_K;
#endif


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
  uint8_t addr;

  #ifdef NPK_SENSOR
    addr = 0x001E;
    if (!mb.slave()) {    // Check if no transaction in progress
    mb.readHreg(NPK_SENSOR_ADDR, addr, regs, 3, HRead); // Send Read Hreg from Modbus Server
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(10);
    }
    sn_N = float(regs[0]);
    sn_P = float(regs[1]);
    sn_K = float(regs[2]);
    Serial.println(regs[0]);
    Serial.println(regs[1]);
    Serial.println(regs[2]);
    }
    delay(1000);
  #endif

}

