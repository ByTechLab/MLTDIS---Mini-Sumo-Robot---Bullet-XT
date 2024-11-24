/*
* USART.c
*
* Created: 2016-05-30 11:08:50
*  Author: Andrzej
*/
#include "USART.h"

int usart_putchar_printf(char var, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);

// this function is called by printf as a stream handler
int usart_putchar_printf(char var, FILE *stream) {
	sendChar(var,&USARTC0);
	return 0;
}
void init_USART_C0(void) //DEBUG
{
	USARTC0.BAUDCTRLB = 0; //BSCALE is 0
	USARTC0.BAUDCTRLA = BAUD_9600; //bsel
	USARTC0.CTRLA = USART_RXCINTLVL_HI_gc; //Disable interrupts
	USARTC0.CTRLC = USART_CHSIZE_8BIT_gc;//8 data bits, no parity and 1 stop bit
	USARTC0.CTRLB = USART_TXEN_bm | USART_RXEN_bm; //Enable receive and transmit
	PORTC.DIRSET = PIN3_bm;
	// setup our stdio stream
	stdout = &mystdout;
}
void sendChar(char c, USART_t *_register)
{
	while( !(_register->STATUS & USART_DREIF_bm) ); //Wait until DATA buffer is empty
	_register->DATA = c;
}
void sendString(char *text)
{
	while(*text)
	{
		sendChar(*text++,&USARTC0);
	}
}

void sendString_PGM(char* string)
{
	while (pgm_read_byte(&(*string)))
	{
		sendChar(pgm_read_byte(&(*string++)),&USARTC0);
	}
}


void insert_newline(char * buff){
	unsigned char z;
	for(z=0; z<30; buff++){
		if(*buff==0){
			*buff   = 13;  //CR (Carrige Return)
			buff++;
			*buff  = 10; //LF (Line Feed)
			buff++;
			*buff  = 0;  // /0
			break;
		}
	}
}

// debug functions
void send_uint32t(uint32_t int_to_send,bool newline)
{
	char usart_bufor[30];
	ultoa(int_to_send, usart_bufor, 10);
	if (newline==true)
	{
		insert_newline(&usart_bufor);
	}
	sendString(usart_bufor);
}

void send_int32t(int32_t int_to_send,bool newline)
{
	char usart_bufor[30];
	ltoa(int_to_send, usart_bufor, 10);
	if (newline==true)
	{
		insert_newline(&usart_bufor);
	}
	sendString(usart_bufor);
}

void sendfloat(float int_to_send,int frac_num,int tot_num ,bool newline)
{
	char usart_bufor[30];
	dtostrf(int_to_send,tot_num,frac_num, usart_bufor);
	if (newline==true)
	{
		insert_newline(&usart_bufor);
	}
	sendString(usart_bufor);
}