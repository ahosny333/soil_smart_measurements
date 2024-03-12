#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <nvs_flash.h>
#include "nvs.h"
#include "credentials.h"
#include "main.h"
#include <Arduino.h>

extern uint16_t TIME_TO_SLEEP;
extern uint16_t WAKE_UP_TIME; 
//extern bool rtc_done;

void readSystemVariables() {
    // defaults
    TIME_TO_SLEEP = 60;      /* time to sleep in seconds*/
    WAKE_UP_TIME = 60;    /* time to wake in seconds */

    nvs_handle my_handle;
    //printf("\nOpening Non-Volatile Storage (NVS) handle... for read \n");
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle! for read \n", esp_err_to_name(err));
    }
    else
    {
        err= nvs_get_u16(my_handle, "TIME_TO_SLEEP", &TIME_TO_SLEEP);
        if(err != ESP_OK)
        {
            TIME_TO_SLEEP = 60;
            Serial.println("failed read TIME_TO_SLEEP");
        }
        err= nvs_get_u16(my_handle, "WAKE_UP_TIME", &WAKE_UP_TIME);
        if(err != ESP_OK)
            WAKE_UP_TIME = 60;

        // uint8_t temp_rtc_done;
        // err= nvs_get_u8(my_handle, "rtc_done", &temp_rtc_done);
        // if(err != ESP_OK)
        //     {rtc_done = false;}
        // else
        //     {rtc_done = (temp_rtc_done == 0) ? false:true;}

        // Close
        nvs_close(my_handle);

    }
   
}

void saveSystemVariables() {
    nvs_handle my_handle;
    //printf("\nOpening Non-Volatile Storage (NVS) handle... for write\n");
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle! for write\n", esp_err_to_name(err));
    }
    else
    {
        DEBUG_PRINTLN("start save parameters");
        err = nvs_set_u16(my_handle, "TIME_TO_SLEEP", TIME_TO_SLEEP);
        err = nvs_set_u16(my_handle, "WAKE_UP_TIME", WAKE_UP_TIME);
        // uint8_t temp_rtc_done;
        // temp_rtc_done = (rtc_done == false) ? 0:1;
        // err = nvs_set_u8(my_handle, "rtc_done", temp_rtc_done);
        err = nvs_commit(my_handle);
        // printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        // Close
        nvs_close(my_handle);
    }

}
