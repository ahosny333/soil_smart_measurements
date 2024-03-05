#include <ModbusRTU.h>
#include "main.h"
#include <ArduinoJson.h>

String jsonStr;
ModbusRTU mb;
uint16_t regs[5];
bool mb_success = false;
#ifdef NPK_SENSOR
uint16_t NPK_N, NPK_P, NPK_K;
#endif

#ifdef EC_SENSOR
uint16_t EC_ec, EC_tds;
#endif

#ifdef MT_SENSOR
uint16_t MT_M, MT_T;
#endif

#ifdef T_M_EC_S_SENSOR
uint16_t T_M_EC_S_T, T_M_EC_S_M, T_M_EC_S_EC, T_M_EC_S_S;
bool T_M_EC_S_ok = false;
#endif

bool HRead(Modbus::ResultCode event, uint16_t transactionId, void *data)
{
  Serial.print("Request result: 0x");
  Serial.println(event, HEX);
  if(event == 0x00 )
  {
    mb_success = true;
  }
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
  addr = NPK_SENSOR_START_ADD;
  if (!mb.slave())
  {                                                     // Check if no transaction in progress
    mb.readHreg(NPK_SENSOR_ADDR, addr, regs, 3, HRead); // Send Read Hreg from Modbus Server
    while (mb.slave())
    { // Check if transaction is active
      mb.task();
      delay(10);
    }
    NPK_N = float(regs[0]);
    NPK_P = float(regs[1]);
    NPK_K = float(regs[2]);
    Serial.println(regs[0]);
    Serial.println(regs[1]);
    Serial.println(regs[2]);
  }
  delay(1000);
#endif

#ifdef EC_SENSOR
  addr = EC_SENSOR_START_ADD;
  if (!mb.slave())
  {                                                    // Check if no transaction in progress
    mb.readHreg(EC_SENSOR_ADDR, addr, regs, 2, HRead); // Send Read Hreg from Modbus Server
    while (mb.slave())
    { // Check if transaction is active
      mb.task();
      delay(10);
    }
    EC_ec = float(regs[0]);
    EC_tds = float(regs[1]);
    Serial.println(regs[0]);
    Serial.println(regs[1]);
  }
  delay(1000);
#endif



#ifdef T_M_EC_S_SENSOR
  uint8_t retry_counter = 0;
  addr = T_M_EC_S_SENSOR_START_ADD;
  mb_success = false;
  while (mb_success == false && retry_counter < max_retries)
  {  
                                                   // Check if no transaction in progress
    mb.readHreg(T_M_EC_S_SENSOR_ADDR, addr, regs, 4, HRead); // Send Read Hreg from Modbus Server
    while (mb.slave())
    { // Check if transaction is active
      mb.task();
      delay(10);
    }
    delay(1000);
    T_M_EC_S_T = float(regs[0]);
    T_M_EC_S_M = float(regs[1]);
    T_M_EC_S_EC = float(regs[2]);
    T_M_EC_S_S = float(regs[3]);
    Serial.println(regs[0]);
    Serial.println(regs[1]);
    Serial.println(regs[2]);
    Serial.println(regs[3]);
    delay(1000);
    retry_counter++;
  }
  
  if(mb_success == false)
  {
    T_M_EC_S_ok = false;
  }
  else
  {
    T_M_EC_S_ok = true;
  }
#endif

}


void data_serializer()
{

  // Allocate the memory for the JSON document
  StaticJsonBuffer<300> jsonBuffer;

  // Create the root JSON object
  JsonObject &root = jsonBuffer.createObject();

  // Add the 'node' and 'bat' keys
  root["n"] = NODE_ID;
  root["b"] = 456;

  // Create the 'reading' array
  JsonArray &reading = root.createNestedArray("r");

// Add sensor readings to the 'reading' array
#ifdef NPK_SENSOR
  JsonObject &npkObj = reading.createNestedObject();
  JsonArray &npkArray = npkObj.createNestedArray("npk");
  npkArray.add(NPK_N);
  npkArray.add(NPK_P);
  npkArray.add(NPK_K);
#endif

#ifdef EC_SENSOR
  JsonObject &ecObj = reading.createNestedObject();
  JsonArray &ecArray = ecObj.createNestedArray("ec");
  ecArray.add(EC_ec);
  ecArray.add(EC_tds);
  Serial.println("ec sensor");
#endif

#ifdef T_M_EC_S_SENSOR
if(T_M_EC_S_ok)
{
  JsonObject &T_M_EC_S_Obj = reading.createNestedObject();
  JsonArray &T_M_EC_S_Array = T_M_EC_S_Obj.createNestedArray("T_M_EC_S");
  T_M_EC_S_Array.add(T_M_EC_S_T);
  T_M_EC_S_Array.add(T_M_EC_S_M);
  T_M_EC_S_Array.add(T_M_EC_S_EC);
  T_M_EC_S_Array.add(T_M_EC_S_S);
}
else
{
  JsonObject &T_M_EC_S_Obj = reading.createNestedObject();
  JsonArray &T_M_EC_S_Array = T_M_EC_S_Obj.createNestedArray("T_M_EC_S");
  T_M_EC_S_Array.add("0");
  T_M_EC_S_Array.add("0");
  T_M_EC_S_Array.add("0");
  T_M_EC_S_Array.add("0");

}
#endif

  // Serialize the JSON document to a string
  jsonStr.clear();
  root.printTo(jsonStr);

  // Print the JSON string
  Serial.println(jsonStr);
}
