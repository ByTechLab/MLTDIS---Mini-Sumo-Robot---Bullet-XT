#include "Includes.h"

void init_ADC(void)
{
	ADCA.CTRLA= ADC_ENABLE_bm;
	//ADCB.CTRLB= ADC_CONMODE_bm;//|//ADC_IMPMODE_bm;//|ADC_CURRLIMIT_MED_gc;
	ADCA.REFCTRL = ADC_REFSEL_AREFA_gc|ADC_RESOLUTION_12BIT_gc;
	//|ADC_RESOLUTION_LEFT12BIT_gc
	ADCA.PRESCALER = ADC_PRESCALER_DIV512_gc;
	
	ADCA.CH0.CTRL = ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN1_gc;//|ADC_CH_MUXNEG_PIN3_gc; //ADC 1 pin
	ADCA.CH0.INTCTRL = 0 ; // No interrupt
	
	ADCA.CH1.CTRL = ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH1.MUXCTRL = ADC_CH_MUXPOS_PIN2_gc;//ADC 2 pin
	ADCA.CH1.INTCTRL = 0 ; // No interrupt
	
	ADCA.CH2.CTRL = ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH2.MUXCTRL = ADC_CH_MUXPOS_PIN3_gc;//ADC 3 pin
	ADCA.CH2.INTCTRL = 0 ; // No interrupt
	
	ADCA.CH3.CTRL = ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH3.MUXCTRL = ADC_CH_MUXPOS_PIN4_gc;//ADC 3 pin
	ADCA.CH3.INTCTRL = 0 ; // No interrupt

}
uint16_t ReadADC(uint8_t Device)
{
	switch(Device)
	{
		case MEAS_SHARP_RIGHT:
		ADCA.CH2.CTRL |= ADC_CH_START_bm; // Start conversion
		while (ADCA.INTFLAGS==0) ; // Wait for complete
		return ADCA.CH2RES ;
		break;
		
		case MEAS_SHARP_FRONT:
		ADCA.CH1.CTRL |= ADC_CH_START_bm; // Start conversion
		while (ADCA.INTFLAGS==0) ; // Wait for complete
		return ADCA.CH1RES ;
		break;
		
		case MEAS_SHARP_LEFT:
		ADCA.CH0.CTRL |= ADC_CH_START_bm; // Start conversion
		while (ADCA.INTFLAGS==0) ; // Wait for complete
		return ADCA.CH0RES ;
		break;
		
		case MEAS_BAT_V:
		ADCA.CH3.CTRL |= ADC_CH_START_bm; // Start conversion
		while (ADCA.INTFLAGS==0) ; // Wait for complete
		return ADCA.CH3RES ;
		break;
		
		default:
		return 0;
		break;
	}
}
float BAT_read_voltage(void){ // 560 = 6V
	//690 = 8v
	
	float voltage = (float)ReadADC(MEAS_BAT_V)*0.0153;
// 	voltage = voltage - 0.120;
// 	voltage = voltage * 18;
	return voltage;
}

// void init_TIM_0C(void)// Kundt tube DAC interupt
// {
// 	HIRESC.CTRLA      =    HIRES_HREN_TC0_gc;//|(1<<2);        // interupt on
// 	TCC0.CTRLB        =    TC_WGMODE_FRQ_gc|TC0_CCAEN_bm;  // normal mode
// 	//TCC0.CTRLFSET   =    TC0_DIR_bm;                 // decrementing
// 	TCC0.CTRLA        =    TC_CLKSEL_DIV1_gc;       // timer start and prescaler enable
// 	TCC0.INTCTRLA     =    TC_OVFINTLVL_LO_gc;
// 	PORTC.DIRSET = PIN0_bm;
// }
