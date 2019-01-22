/*
 * thermC.h
 *
 *  Created on: 19/01/2019
 *      Author: jonas
 */

#ifndef THERMC_H_
#define THERMC_H_
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "driver/adc.h"
#include "esp_adc_cal.h"
#include <driver/dac.h>
#include "math.h"




//PROTOTYPES----------------------------------------------------------------------------
double  GetthermC(void );// this one is where im going to get the temperature from


void vrefToPin(void);
void thermistorInit(void); //put this in main init lists



#endif /* THERMC_H_ */
