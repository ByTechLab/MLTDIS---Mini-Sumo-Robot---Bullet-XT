#ifndef OTHER_H_
#define OTHER_H_

#include "Includes.h"

#define PLL_FACT 8 // pll multiply factor DONT CHANGE! ( f>32MHz)

#define BUZZ_ON TCF0.CTRLB        |=    TC0_CCAEN_bm
#define BUZZ_OFF TCF0.CTRLB       &=   ~ TC0_CCAEN_bm

#define ATK_FAIL 2
#define ATK_PASS 3

enum RET {BUTTON_1,BUTTON_2,BUTTON_3,BUTTON_4};

typedef enum {
	BUTTON_RISING_EDGE, BUTTON_PUSH, BUTTON_RELEASE, BUTTON_FALLING_EDGE
}ButtonStatus;

#define BUTTON_1_CHECK    !(PORTB.IN & PIN0_bm)
#define BUTTON_2_CHECK    !(PORTB.IN & PIN1_bm)
#define BUTTON_3_CHECK    !(PORTB.IN & PIN2_bm)
#define BUTTON_4_CHECK    !(PORTB.IN & PIN3_bm)
#define  LINE_4_CHECK    !(PORTD.IN & PIN6_bm)
#define  LINE_3_CHECK    !(PORTD.IN & PIN7_bm)
#define  DIGITAL_SHARP_CHECK    !(PORTA.IN & PIN5_bm)
#define  DIGITAL_SHARP_CHECK_NEG    (PORTA.IN & PIN5_bm)
#define  ANALOG_SHARP_FRONT_CHECK    !(PORTC.IN & PIN6_bm)

volatile  uint16_t BUZZER_DELAY_TICK;
volatile  uint32_t   RTC_OVF_COUNTER; // Our RTC overflows every minute and inc this var

volatile struct
{
	uint8_t SHARP_DIGIT :1;
	uint8_t SHARP_A_FRONT :1;
	uint8_t SHARP_A_LEFT :1;
	uint8_t SHARP_A_RIGHT :1;
	uint8_t LINE_LEFT :1;
	uint8_t LINE_RIGHT :1;
}SENS_FLAG_s;

volatile struct
{
	uint8_t START_STOP :1;
	uint8_t MODE :3;
	uint8_t FIRST_TURN :1;
}GP_FLAGS_s;

volatile struct
{
		uint32_t SHARP_DIGIT;
		uint32_t SHARP_A_FRONT;
		uint32_t SHARP_A_LEFT;
		uint32_t SHARP_A_RIGHT ;
		uint32_t LINE;
}IGNEORE_SENS_s;

volatile uint8_t USART_RX_DATA;

void init_PORTS(void);
void init_OSC_PLL(uint8_t pllfactor);
void init_PMIC(void);
void init_TIM_0F(void) ;
void init_RTC(void);
void init_WDT(void);
ButtonStatus BUTTON_status(uint8_t input,uint8_t select);
void BUZZ_beep(uint16_t duration);
init_TIM_0E(void);
uint32_t read_rtc_time(void);
uint8_t ATTACK(void);
void FLAGS_clear_all(void);
void Wait_5_sec(void);

#endif /* OTHER_H_ */