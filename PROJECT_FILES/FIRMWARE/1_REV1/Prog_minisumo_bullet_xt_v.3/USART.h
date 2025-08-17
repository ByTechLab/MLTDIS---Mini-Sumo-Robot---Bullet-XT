/*
 * USART.h
 *
 * Created: 2016-05-30 11:09:04
 *  Author: Andrzej
 */ 


#ifndef USART_H_
#define USART_H_
#include "Includes.h"


#include    <avr/eeprom.h> ///---->!
#include    <util/delay.h>
#include    <math.h>
#include    <avr/interrupt.h>
#include    <avr/pgmspace.h>
#include    <avr/wdt.h>
#include    <stdlib.h>
#include    <stdbool.h>
#include    <string.h>
#include    <util/atomic.h>

#define BAUD_57600 0x23 //34
#define BAUD_9600 0xCF  //207

void init_USART_C0(void) ;
void sendChar(char c, USART_t *_register);
void sendString(char *text);
void sendString_PGM(char* string);
void insert_newline(char * buff);
void send_uint32t(uint32_t int_to_send,bool newline);
void send_int32t(int32_t int_to_send,bool newline);
void sendfloat(float int_to_send,int frac_num,int tot_num ,bool newline);


#endif /* USART_H_ */