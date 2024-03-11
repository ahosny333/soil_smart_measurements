#ifndef APP_MODBUS_H_
#define APP_MODBUS_H_

struct Data_Package {
  uint16_t NPK_N = 0;
  uint16_t NPK_P = 0;
  uint16_t NPK_K = 0;
  uint16_t MT_M = 0;
  uint16_t MT_T = 0;
  uint16_t T_M_EC_S_T = 0;
  uint16_t T_M_EC_S_M = 0;
  uint16_t T_M_EC_S_EC = 0;
  uint16_t T_M_EC_S_S =0;
};

void modbus_init();
void read_sensors_values();
void data_serializer();

#endif