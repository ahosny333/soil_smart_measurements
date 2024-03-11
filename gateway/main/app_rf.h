#ifndef APP_rf_H_
#define APP_rf_H_
#include "Arduino.h"

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

void rf_init();
bool rf_get_data();

#endif