#ifndef APP_SD_H_
#define APP_SD_H_
#include "FS.h"
#include "SD.h"
#include "SPI.h"

void writeFile(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);
void sd_card_init();
void log_data();
#endif