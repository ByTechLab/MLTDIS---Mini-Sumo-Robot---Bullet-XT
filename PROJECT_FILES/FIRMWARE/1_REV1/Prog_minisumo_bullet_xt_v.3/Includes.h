/*
 * Includes.h
 *
 * Created: 2016-05-31 17:20:33
 *  Author: Andrzej
 */ 

#ifndef INCLUDES_H_
#define INCLUDES_H_

#define F_CPU 32000000UL

#include <avr/io.h>
#include <stdio.h>
#include    <avr/eeprom.h> ///---->!
#include    <util/delay.h>
#include    <math.h>
#include    <avr/interrupt.h>
#include    <avr/pgmspace.h>
#include    <avr/wdt.h>
#include    <stdlib.h>
#include    <stdbool.h>
#include    <string.h>
#include    <util/atomic.h> //--------------
//  #include    <util/setbaud.h>//--------------
//  #include    <util/twi.h> //-------------
//  #include    <util/crc16.h>//------------

#include "OTHER.h"
#include "USART.h"
#include "ADC.h"
#include "MOT.h"
#include "LED.h"
#include "LCD.h"



#endif /* INCLUDES_H_ */