/*
 * ADC.h
 *
 * Created: 2016-05-30 11:15:25
 *  Author: Andrzej
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "Includes.h"

//#define TABLE_LENGTH 8 // DAC sine table length
#define MEAS_SHARP_LEFT 1 //od tylu lewy
#define MEAS_SHARP_RIGHT 2 // prawy
#define MEAS_SHARP_FRONT 3 // srodkowy
#define MEAS_BAT_V 4

void init_ADC(void);
uint16_t ReadADC(uint8_t Channel);
float BAT_read_voltage(void);

#endif /* ADC_H_ */