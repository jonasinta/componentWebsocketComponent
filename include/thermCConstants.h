/*
 * thermCConstants.h
 *
 *  Created on: 20/01/2019
 *      Author: jonas
 */

#ifndef COMPONENTS_COMPONENTTHERMISTORCOMPONENT_INCLUDE_THERMCCONSTANTS_H_
#define COMPONENTS_COMPONENTTHERMISTORCOMPONENT_INCLUDE_THERMCCONSTANTS_H_

#define DEFAULT_VREF    1105        //Use adc2_vref_to_gpio() to obtain a better estimate- actual voltage measured

#define NO_OF_SAMPLES   64          //Multisampling
#define WUDTH 			ADC_WIDTH_12Bit  //width of bits adc

static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_6;     //GPIO34 if ADC1, GPIO14 if ADC2

//static const adc_atten_t atten = ADC_ATTEN_DB_0;
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;
static const float r1 =30150.0; //the riesistor between thermistor and earth.
static const float vref =3.282;
static const double  oneT25 = 1.0/298.15; // inverse of 25c in kelvinators
static const double  oneBeta = 1.0/3960.0; // inverse of the B constant for this thermistor B=3960


double voltage =0.0;
double tempC=0.0;
double r_therm=0.0;
double temp_oneT =0.0; // put the inverse of T in here



#endif /* COMPONENTS_COMPONENTTHERMISTORCOMPONENT_INCLUDE_THERMCCONSTANTS_H_ */
