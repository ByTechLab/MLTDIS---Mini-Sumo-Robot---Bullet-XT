/*
 * LED.c
 *
 * Created: 2016-05-31 17:18:13
 *  Author: Andrzej
 */ 
#include "Includes.h"


// ustawiamy czas w zmiennej ktora okresla czas swiecenia
// ustawiamy czas wlaczenia do zminnej  pomocniczej
// wlaczamy diode

void LED_blink(void)
{
	PORTF.OUTSET = PIN1_bm;
	PORTF.OUTSET = PIN2_bm;
	PORTF.OUTSET = PIN3_bm;
	PORTF.OUTSET = PIN4_bm;
	PORTF.OUTSET = PIN5_bm;
	PORTF.OUTSET = PIN6_bm;
	PORTF.OUTSET = PIN7_bm;
	_delay_ms(200);
	PORTF.OUTCLR = PIN1_bm;
	PORTF.OUTCLR = PIN2_bm;
	PORTF.OUTCLR = PIN3_bm;
	PORTF.OUTCLR = PIN4_bm;
	PORTF.OUTCLR = PIN5_bm;
	PORTF.OUTCLR = PIN6_bm;
	PORTF.OUTCLR = PIN7_bm;
	_delay_ms(200);
}
void LED_toggle(void)
{
	LED_1_TOG
	LED_2_TOG
	LED_3_TOG
	LED_4_TOG
	LED_5_TOG
	LED_6_TOG
	LED_7_TOG
	LED_8_TOG
}