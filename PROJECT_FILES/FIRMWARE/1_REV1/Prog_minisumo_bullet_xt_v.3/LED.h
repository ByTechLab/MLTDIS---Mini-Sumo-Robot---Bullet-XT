
/*
 * LED.h
 *
 * Created: 2016-05-31 17:18:49
 *  Author: Andrzej
 */ 


#ifndef LED_H_
#define LED_H_
#include "Includes.h"

#define LED_1_ON	    PORTF.OUTSET = PIN1_bm;
#define LED_2_ON		PORTF.OUTSET = PIN2_bm;
#define LED_3_ON		PORTF.OUTSET = PIN3_bm;
#define LED_4_ON		PORTF.OUTSET = PIN4_bm;
#define LED_5_ON		PORTF.OUTSET = PIN5_bm;
#define LED_6_ON		PORTF.OUTSET = PIN6_bm;
#define LED_7_ON		PORTF.OUTSET = PIN7_bm;
#define LED_8_ON		PORTC.OUTSET = PIN1_bm;

#define LED_1_OFF		PORTF.OUTCLR = PIN1_bm;
#define LED_2_OFF		PORTF.OUTCLR = PIN2_bm;
#define LED_3_OFF		PORTF.OUTCLR = PIN3_bm;
#define LED_4_OFF		PORTF.OUTCLR = PIN4_bm;
#define LED_5_OFF		PORTF.OUTCLR = PIN5_bm;
#define LED_6_OFF		PORTF.OUTCLR = PIN6_bm;
#define LED_7_OFF		PORTF.OUTCLR = PIN7_bm;
#define LED_8_OFF		PORTC.OUTCLR = PIN1_bm;

#define LED_1_TOG       PORTF.OUTTGL = PIN1_bm;
#define LED_2_TOG       PORTF.OUTTGL = PIN2_bm;
#define LED_3_TOG       PORTF.OUTTGL = PIN3_bm;
#define LED_4_TOG       PORTF.OUTTGL = PIN4_bm;
#define LED_5_TOG       PORTF.OUTTGL = PIN5_bm;
#define LED_6_TOG       PORTF.OUTTGL = PIN6_bm;
#define LED_7_TOG       PORTF.OUTTGL = PIN7_bm;
#define LED_8_TOG       PORTC.OUTTGL = PIN1_bm;

void LED_blink(void);
void LED_toggle(void);


#endif /* LED_H_ */