/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "thermC.h"
#include "thermCConstants.h"

static void check_efuse();
static void print_char_val_type(esp_adc_cal_value_t val_type);

static void check_efuse()
{
    //Check TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

void vrefToPin(void)
{
	 esp_err_t status = adc2_vref_to_gpio(GPIO_NUM_25);
	    if (status == ESP_OK) {
	        printf("v_ref routed to GPIO\n");
	    } else {
	        printf("failed to route v_ref\n");
	    }

}



void thermistorInit()
{
    //Check if Two Point or Vref are burned into eFuse
    check_efuse();

   //put vref to GPIO25
   vrefToPin();



   // get register
   adc1_config_width(ADC_WIDTH_12Bit);//config adc1 width
  // adc1_pad_init(ADC1_CHANNEL_6);
   adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_0db);
   int val=adc1_get_voltage(ADC1_CHANNEL_6);
   adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_11db);
   int val2=adc1_get_voltage(ADC1_CHANNEL_6);
   printf("ADC1 CH6 value: %d @ 0db, %d @ 11db\n", val, val2);
   //Configure ADC
    if (unit == ADC_UNIT_1) {
        adc1_config_width(WUDTH);
        adc1_config_channel_atten((adc1_channel_t)channel, atten);
    } else {
        adc2_config_channel_atten((adc2_channel_t)channel, atten);
    }

    //Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, WUDTH, DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);


}


double  GetthermC(void )
		{

	        uint32_t adc_reading = 0;
	        //Multisampling
	        for (int i = 0; i < NO_OF_SAMPLES; i++) {
	            if (unit == ADC_UNIT_1) {
	                adc_reading += adc1_get_raw(channel);
	                //printf("\tcount %d, value %d\n", i, adc_reading);
	            } else {
	                int raw;
	                adc2_get_raw((adc2_channel_t)channel, WUDTH, &raw);
	                adc_reading += raw;
	            }//close else
	        }//close for
	        adc_reading /= NO_OF_SAMPLES;
	        //Convert adc_reading to voltage in mV
	        voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
	        voltage = voltage/1000;//convert mV to volts

	        r_therm =(r1*(vref-voltage))/voltage; //calculate the calculated voltage to the resistance of thermistor

	        temp_oneT = oneT25 +(oneBeta*(log(r_therm/30000)));  //partial calculation of the steinhart

	        tempC = (1/temp_oneT) - 273.15; //get inverse(finish steinhart) and convert from K to deg. C
	        //printf("++++++++++++++++++++++++++++++++++++++++++\n\n\ttempC%.1f    Rthermistor%.3fKohm\n",tempC, r_therm/1000);

        return tempC;
	}//closefunction





