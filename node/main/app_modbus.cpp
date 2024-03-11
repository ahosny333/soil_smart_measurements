#include <ModbusRTU.h>
#include "main.h"
#include <ArduinoJson.h>
#include "app_modbus.h"

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
  Serial.print("Request result: 0x");
  Serial.println(event, HEX);
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

  Serial.println("------------------------------------------------");
  Serial.println("NPK_SENSOR");
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

    Serial.println(NPK_N);
    Serial.println(NPK_P);
    Serial.println(NPK_K);

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

  Serial.println("------------------------------------------------");
  Serial.println("MT_SENSOR");
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
      MT_M = regs[0]/10;
      MT_T = regs[1]/10;
      data.MT_M = MT_M;
      data.MT_T = MT_T;
    }
    else
    {
      MT_M = 0;
      MT_T = 0;
    }

    Serial.println(MT_M);
    Serial.println(MT_T);

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
  Serial.println("------------------------------------------------");
  Serial.println("T_M_EC_S_SENSOR");
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
      T_M_EC_S_T = regs[0];
      T_M_EC_S_M = regs[1];
      T_M_EC_S_EC = regs[2];
      T_M_EC_S_S = regs[3];
      data.T_M_EC_S_T = T_M_EC_S_T;
      data.T_M_EC_S_M = T_M_EC_S_M;
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
    Serial.println(T_M_EC_S_T);
    Serial.println(T_M_EC_S_M);
    Serial.println(T_M_EC_S_EC);
    Serial.println(T_M_EC_S_S);
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
  Serial.println("------------------------------------------------");
  Serial.println("EC_SENSOR");
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

    Serial.println(EC_T);
    Serial.println(EC_M);

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
  Serial.println("------------------------------------------------");
  Serial.println("PH_SENSOR");
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

    Serial.println(PH_T);
    Serial.println(PH_M);

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
  Serial.println(jsonStr);
}
