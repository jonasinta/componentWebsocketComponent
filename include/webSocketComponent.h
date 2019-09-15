/*
 * thermC.h
 *
 *  Created on: 19/01/2019
 *      Author: jonas
 */

#ifndef WEBSOCKETCOMPONent_H_
#define WEBSOCKETCOMPONent_H_
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "sdkconfig.h"







//PROTOTYPES----------------------------------------------------------------------------

static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
static void websocket_send(void)
static void websocket_init(void);
static void websocket_destroy(void);
void app_main();



#endif /* WEBSOCKETCOMPONent_H_ */
