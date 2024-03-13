#include <ModbusRTU.h>
#include "main.h"
#include <ArduinoJson.h>
#include "app_modbus.h"
#include "app_sd.h"

extern bool sd_exist;
extern bool rtc_exist;

String jsonStr;
ModbusRTU mb;
uint16_t regs[5];
uint8_t retry_counter;
bool mb_success = false;

#ifdef NPK_SENSOR
uint16_t NPK_N, NPK_P, NPK_K;
bool NPK_ok = false;
#endif

#ifdef MT_SENSOR
uint16_t MT_M, MT_T;
bool MT_ok = false;
#endif

#ifdef T_M_EC_S_SENSOR
uint16_t T_M_EC_S_T, T_M_EC_S_M, T_M_EC_S_EC, T_M_EC_S_S;
bool T_M_EC_S_ok = false;
#endif

#ifdef EC_SENSOR
uint16_t EC_T, EC_M;
bool EC_ok = false;
#endif

#ifdef PH_SENSOR
uint16_t PH_T, PH_M;
bool PH_ok = false;
#endif

Data_Package data;

bool HRead(Modbus::ResultCode event, uint16_t transactionId, void *data)
{
  DEBUG_PRINT("Request result: 0x");
  DEBUG_PRINTLNHEX(event);
  if (event == 0x00)
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

  //////////////////////////////////////////////////////

  DEBUG_PRINTLN("------------------------------------------------");
  DEBUG_PRINTLN("NPK_SENSOR");
#ifdef NPK_SENSOR
  retry_counter = 0;
  addr = NPK_SENSOR_START_ADD;
  mb_success = false;
  while (mb_success == false && retry_counter < max_retries)
  {
    // Check if no transaction in progress
    mb.readHreg(NPK_SENSOR_ADDR, addr, regs, 3, HRead); // Send Read Hreg from Modbus Server
    while (mb.slave())
    { // Check if transaction is active
      mb.task();
      delay(10);
    }

    delay(1000);

    if (mb_success == true)
    {
      NPK_N = regs[0];
      NPK_P = regs[1];
      NPK_K = regs[2];
      data.NPK_N = NPK_N;
      data.NPK_P = NPK_P;
      data.NPK_K = NPK_K;
    }
    else
    {
      NPK_N = 0;
      NPK_P = 0;
      NPK_K = 0;
    }

    DEBUG_PRINTLN(NPK_N);
    DEBUG_PRINTLN(NPK_P);
    DEBUG_PRINTLN(NPK_K);

    delay(1000);
    retry_counter++;
  }

  if (mb_success == false)
  {
    NPK_ok = false;
  }
  else
  {
    NPK_ok = true;
  }
#endif
  ////////////////////////////////////////////////////////

  DEBUG_PRINTLN("------------------------------------------------");
  DEBUG_PRINTLN("MT_SENSOR");
#ifdef MT_SENSOR
  retry_counter = 0;
  addr = MT_SENSOR_START_ADD;
  mb_success = false;
  while (mb_success == false && retry_counter < max_retries)
  {
    // Check if no transaction in progress
    mb.readHreg(MT_SENSOR_ADDR, addr, regs, 2, HRead); // Send Read Hreg from Modbus Server
    while (mb.slave())
    { // Check if transaction is active
      mb.task();
      delay(10);
    }


    delay(1000);

    if (mb_success == true)
    {
      MT_M = regs[0];
      MT_T = regs[1];
      // Serial.print(" raw m : ");
      // Serial.println(MT_M);
      data.MT_M = MT_M * 10 /37 ;
      if(data.MT_M > 100)
      {
        data.MT_M = 100;
      }
      data.MT_T = MT_T / 10;
    }
    else
    {
      MT_M = 0;
      MT_T = 0;
    }

    DEBUG_PRINTLN(data.MT_M);
    DEBUG_PRINTLN(data.MT_T);

    delay(1000);
    retry_counter++;
  }

  if (mb_success == false)
  {
    MT_ok = false;
  }
  else
  {
    MT_ok = true;
  }
#endif

  ////////////////////////////////////////////////////////
  DEBUG_PRINTLN("------------------------------------------------");
  DEBUG_PRINTLN("T_M_EC_S_SENSOR");
#ifdef T_M_EC_S_SENSOR
  retry_counter = 0;
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
    if (mb_success == true)
    {
      T_M_EC_S_T = regs[1];
      T_M_EC_S_M = regs[0];
      T_M_EC_S_EC = regs[2];
      T_M_EC_S_S = regs[3];
      // Serial.print("raw ec m :");
      // Serial.println(T_M_EC_S_M);
      data.T_M_EC_S_T = T_M_EC_S_T/100;
      data.T_M_EC_S_M = T_M_EC_S_M *1/37;
      if(data.T_M_EC_S_M > 100)
      {
        data.T_M_EC_S_M = 100;
      }
      data.T_M_EC_S_EC = T_M_EC_S_EC;
      data.T_M_EC_S_S = T_M_EC_S_S;
    }
    else
    {
      T_M_EC_S_T = 0;
      T_M_EC_S_M = 0;
      T_M_EC_S_EC = 0;
      T_M_EC_S_S = 0;
    }
    DEBUG_PRINTLN(data.T_M_EC_S_T);
    DEBUG_PRINTLN(data.T_M_EC_S_M);
    DEBUG_PRINTLN(data.T_M_EC_S_EC);
    DEBUG_PRINTLN(data.T_M_EC_S_S);
    delay(1000);
    retry_counter++;
  }
  if (mb_success == false)
  {
    T_M_EC_S_ok = false;
  }
  else
  {
    T_M_EC_S_ok = true;
  }
#endif

  ////////////////////////////////////////////////////////
  DEBUG_PRINTLN("------------------------------------------------");
  DEBUG_PRINTLN("EC_SENSOR");
#ifdef EC_SENSOR
  retry_counter = 0;
  addr = EC_SENSOR_START_ADD;
  mb_success = false;
  while (mb_success == false && retry_counter < max_retries)
  {
    // Check if no transaction in progress
    mb.readHreg(EC_SENSOR_ADDR, addr, regs, 2, HRead); // Send Read Hreg from Modbus Server
    while (mb.slave())
    { // Check if transaction is active
      mb.task();
      delay(10);
    }

    delay(1000);
    if (mb_success == true)
    {
      EC_T = float(regs[0]);
      EC_M = float(regs[1]);
    }
    else
    {
      EC_T = 0;
      EC_M = 0;
    }

    DEBUG_PRINTLN(EC_T);
    DEBUG_PRINTLN(EC_M);

    delay(1000);
    retry_counter++;
  }

  if (mb_success == false)
  {
    EC_ok = false;
  }
  else
  {
    EC_ok = true;
  }
#endif

  ////////////////////////////////////////////////////////
  DEBUG_PRINTLN("------------------------------------------------");
  DEBUG_PRINTLN("PH_SENSOR");
#ifdef PH_SENSOR
  retry_counter = 0;
  addr = PH_SENSOR_START_ADD;
  mb_success = false;
  while (mb_success == false && retry_counter < max_retries)
  {
    // Check if no transaction in progress
    mb.readHreg(PH_SENSOR_ADDR, addr, regs, 2, HRead); // Send Read Hreg from Modbus Server
    while (mb.slave())
    { // Check if transaction is active
      mb.task();
      delay(10);
    }

    delay(1000);
    if (mb_success == true)
    {
      PH_T = float(regs[0]);
      PH_M = float(regs[1]);
    }
    else
    {
      PH_T = 0;
      PH_M = 0;
    }

    DEBUG_PRINTLN(PH_T);
    DEBUG_PRINTLN(PH_M);

    delay(1000);
    retry_counter++;
  }

  if (mb_success == false)
  {
    PH_ok = false;
  }
  else
  {
    PH_ok = true;
  }
#endif
  if(sd_exist && rtc_exist)
  {
    log_data();
  }
  else{
    DEBUG_PRINTLN("not logged data");
    DEBUG_PRINTLN(sd_exist);
    DEBUG_PRINTLN(rtc_exist);

  }
}
void data_serializer()
{

  // Allocate the memory for the JSON document
  StaticJsonBuffer<450> jsonBuffer;

  // Create the root JSON object
  JsonObject &root = jsonBuffer.createObject();

  // Add the 'node' and 'bat' keys
  root["n"] = NODE_ID;
  root["b"] = 456;

  // Create the 'reading' array
  JsonArray &reading = root.createNestedArray("r");

  // Add sensor readings to the 'reading' array

/////////////////////////////////////////////////
// NPK_SENSOR
#ifdef NPK_SENSOR
  if (NPK_ok)
  {
    JsonObject &NPK_Obj = reading.createNestedObject();
    JsonArray &NPK_Array = NPK_Obj.createNestedArray("NPK");
    NPK_Array.add(NPK_N);
    NPK_Array.add(NPK_P);
    NPK_Array.add(NPK_K);
  }
  else
  {
    JsonObject &NPK_Obj = reading.createNestedObject();
    JsonArray &NPK_Array = NPK_Obj.createNestedArray("NPK");
    NPK_Array.add("0");
    NPK_Array.add("0");
    NPK_Array.add("0");
  }
#endif

/////////////////////////////////////////////////
// MT_SENSOR
#ifdef MT_SENSOR
  if (MT_ok)
  {
    JsonObject &MT_Obj = reading.createNestedObject();
    JsonArray &MT_Array = MT_Obj.createNestedArray("MT");
    MT_Array.add(MT_T);
    MT_Array.add(MT_M);
  }
  else
  {
    JsonObject &MT_Obj = reading.createNestedObject();
    JsonArray &MT_Array = MT_Obj.createNestedArray("MT");
    MT_Array.add("0");
    MT_Array.add("0");
  }
#endif

/////////////////////////////////////////////////
// T_M_EC_S_SENSOR
#ifdef T_M_EC_S_SENSOR
  if (T_M_EC_S_ok)
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

/////////////////////////////////////////////////
// EC_SENSOR
#ifdef EC_SENSOR
  if (EC_ok)
  {
    JsonObject &EC_Obj = reading.createNestedObject();
    JsonArray &EC_Array = EC_Obj.createNestedArray("EC");
    EC_Array.add(EC_T);
    EC_Array.add(EC_M);
  }
  else
  {
    JsonObject &EC_Obj = reading.createNestedObject();
    JsonArray &EC_Array = EC_Obj.createNestedArray("EC");
    EC_Array.add("0");
    EC_Array.add("0");
  }
#endif

/////////////////////////////////////////////////
// PH_SENSOR
#ifdef PH_SENSOR
  if (PH_ok)
  {
    JsonObject &PH_Obj = reading.createNestedObject();
    JsonArray &PH_Array = PH_Obj.createNestedArray("PH");
    PH_Array.add(PH_T);
    PH_Array.add(PH_M);
  }
  else
  {
    JsonObject &PH_Obj = reading.createNestedObject();
    JsonArray &PH_Array = PH_Obj.createNestedArray("PH");
    PH_Array.add("0");
    PH_Array.add("0");
  }
#endif

  // Serialize the JSON document to a string
  jsonStr.clear();
  root.printTo(jsonStr);

  // Print the JSON string
  DEBUG_PRINTLN(jsonStr);
}
