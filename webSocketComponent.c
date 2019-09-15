/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "webSocketComponent.h"


/* ESP HTTP Client Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/


#include <stdio.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"


#include "esp_log.h"
#include "esp_websocket_client.h"
#include "esp_event.h"
#include "esp_event_loop.h"

static const char *TAG = "WEBSOCKET";
static const char *WEBSOCKET_ECHO_ENDPOINT = CONFIG_WEBSOCKET_URI;

//Global Variables
QueueHandle_t websocketSendQueue = NULL;
QueueHandle_t websocketRecieveQueue = NULL;

static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    // esp_websocket_client_handle_t client = (esp_websocket_client_handle_t)handler_args;
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
    switch (event_id) {
        case WEBSOCKET_EVENT_CONNECTED:
            ESP_LOGI(TAG, "WEBSOCKET_EVENT_CONNECTED");


            break;
        case WEBSOCKET_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "WEBSOCKET_EVENT_DISCONNECTED");
            break;

        case WEBSOCKET_EVENT_DATA:
            ESP_LOGI(TAG, "WEBSOCKET_EVENT_DATA");
            ESP_LOGW(TAG, "Received=%.*s\r\n", data->data_len, (char*)data->data_ptr);

            xQueueSend( websocketRecieveQueue, (char*)data->data_ptr, 0 );
            break;
        case WEBSOCKET_EVENT_ERROR:
            ESP_LOGI(TAG, "WEBSOCKET_EVENT_ERROR");
            break;
    }
}

//method for sending data down the websocket
static void websocket_send(void) {

	esp_websocket_client_start(client);

				if (esp_websocket_client_is_connected(client)) {
					char[20] tempArray;
					char singleChar;
					char i =0;
					while (0){
					xQueueReceive( websocketSendQueue, &singleChar, 0 );
					tempArray[i] = singleChar;
					i++;
					}
					int len = sprintf(data, "hello %04d", i++);
					ESP_LOGI(TAG, "Sending %s", data);
					esp_websocket_client_send(client, data, len, portMAX_DELAY);
				}
				vTaskDelay(1000 / portTICK_RATE_MS);

			esp_websocket_client_stop(client);
			    ESP_LOGI(TAG, "Websocket Stopped");


}//close method bebsocket send

// methos for initiate websocket- endpoint, client etc
static void websocket_init(void)
{
    ESP_LOGI(TAG, "Connectiong to %s...", WEBSOCKET_ECHO_ENDPOINT);

    const esp_websocket_client_config_t websocket_cfg = {
        .uri = WEBSOCKET_ECHO_ENDPOINT, // or wss://echo.websocket.org for websocket secure
    };

    esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);

   // esp_websocket_client_start(client);


    static void websocket_destroy(void)
    {

	esp_websocket_client_destroy(client);

} // close websocket destroye method

void app_main()
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());
    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("WEBSOCKET_CLIENT", ESP_LOG_DEBUG);
    esp_log_level_set("TRANS_TCP", ESP_LOG_DEBUG);

    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    websocketSendQueue = xQueueCreate( 20, sizeof( byte[20] ) );
    websocketSendQueue = xQueueCreate( 20, sizeof( byte[20] ) );

    websocket_init();
}
