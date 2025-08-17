/*
 * LCD.h
 *
 * Created: 2016-05-30 12:24:40
 *  Author: Andrzej
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Includes.h"

#define SPI_TIMEOUT 50

#define	SPI_SD_LOW_SPEED     SPIC.CTRL = SPI_PRESCALER_DIV128_gc		//SCK == 500KHz
#define	SPI_SD_HIGH_SPEED 	   SPIC.CTRL &= ~(SPI_PRESCALER_DIV128_gc)  // SCK== 16MHz

#define	SPI_TX_LOW_SPEED     SPIE.CTRL = SPI_MODE_0_gc|SPI_ENABLE_bm|SPI_PRESCALER_DIV64_gc|SPI_CLK2X_bm|SPI_MASTER_bm;	// SCK == 1MHz
#define	SPI_TX_HIGH_SPEED 	   SPIE.CTRL = SPI_MODE_0_gc|SPI_ENABLE_bm|SPI_PRESCALER_DIV16_gc|SPI_CLK2X_bm|SPI_MASTER_bm; // SCK == 4Mhz

#define  LCD_RST_ON PORTE.OUTSET = PIN2_bm;
#define  LCD_RST_OFF PORTE.OUTCLR = PIN2_bm;
#define  LCD_DC_ON PORTE.OUTSET = PIN3_bm;
#define  LCD_DC_OFF PORTE.OUTCLR = PIN3_bm;
#define  LCD_SS_ON PORTE.OUTSET = PIN4_bm;
#define  LCD_SS_OFF PORTE.OUTCLR = PIN4_bm;

void init_SPI_LCD(void);
//void transmit_SPI_LCD(unsigned char data);
//unsigned char receive_SPI_LCD(void);
void init_LCD(void);
void LCD_write_byte(unsigned char c_d, unsigned char data );
void LCD_image(unsigned char s[],char  x, char y, char w, char h);
void LCD_clear(void);
void LCD_text(char s[], unsigned char x, unsigned char y);
void LCD_menu_print(void);
void LCD_menu_mode_print(void);
void LCD_menu_handle(void);

/* 84 x 6 bajtów */
#define LCD_X 84
#define LCD_Y 6

#define LCD_CMD     0
#define LCD_DATA    1

#define LCD_HOME LCD_write_byte(LCD_CMD, 0x40);LCD_write_byte(LCD_CMD, 0x80);
#define LCD_GOTO(x,y) LCD_write_byte(LCD_CMD, 0x40|(y));LCD_write_byte(LCD_CMD, 0x80|(x));

#define LCD_SETX  0x80
#define LCD_SETY  0x40

// menu
#define SUBMENU_MAIN 1
#define SUBMENU_MODE 2
#define SUBMENU_TEST_SENS 3
#define SUBMENU_VOLTAGE 4

#define MODE_TORNADO 1
#define MODE_STANDARD 2
#define MODE_LF 3

volatile int8_t Menu_option_counter;
volatile int8_t Menu_sub_flag;
unsigned char buff [15];


struct
{
	uint8_t _1 :1;
	uint8_t _2 :1;
	uint8_t _3 :1;
	uint8_t _4 :1;
}BTN_s;


#endif /* LCD_H_ */