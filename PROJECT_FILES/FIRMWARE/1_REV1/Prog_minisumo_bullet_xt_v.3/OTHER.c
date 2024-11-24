
/*
* OTHER.c
*
* Created: 2016-05-31 17:26:04
*  Author: Andrzej
*/
#include "Includes.h"

/*BUZZER_DELAY_TICK=0;*/

void init_OSC_PLL(uint8_t pllfactor)
{
	CPU_CCP           =    CCP_IOREG_gc;                // Unlock changing im reg
	CLK.PSCTRL        =    CLK_PSADIV_1_gc|CLK_PSBCDIV_2_2_gc;
	OSC.XOSCCTRL    =      OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_16KCLK_gc;   // Set oscilator frequency ant time to start -----------------------------------------<DONT CHANGE 16K cLK!
	OSC.CTRL          =    OSC_XOSCEN_bm;               // Start 16Mhz crystal
	while(!(OSC.STATUS & OSC_XOSCRDY_bm));              // Wait for crystal to stabilize                                       ----------------------------------------< ADD waiting TIMEOUT!
	CPU_CCP           =    CCP_IOREG_gc;                // Unlock changing im reg
	CLK.CTRL          =    CLK_SCLKSEL_XOSC_gc;         // Change clock source to crystal
	OSC.CTRL         &=   ~OSC_PLLEN_bm;                // Disable PLL
	OSC.PLLCTRL       =    OSC_PLLSRC_XOSC_gc |  pllfactor;        // Select crystal as pll sig source
	OSC.CTRL          =    OSC_PLLEN_bm;                // Enable PLL
	while(!(OSC.STATUS & OSC_PLLRDY_bm));	            // Wait for PLL to stabilize
	CPU_CCP           =    CCP_IOREG_gc;                // Unlock changing im reg
	CLK.CTRL          =    CLK_SCLKSEL_PLL_gc;          // Change clock source to PLL
	CPU_CCP           =    CCP_IOREG_gc;                // Unlock changing im reg
	OSC.XOSCFAIL      =    OSC_PLLFDEN_bm| OSC_XOSCFDEN_bm;      // Turn on PLL safety devices

}

void init_TIM_0F(void) // Buzzer freq generator
{
	TCF0.CTRLB        =    TC_WGMODE_FRQ_gc|TC0_CCAEN_bm;  // normal mode
	//TCC0.CTRLFSET   =    TC0_DIR_bm;                 // decrementing
	TCF0.CTRLA        =    TC_CLKSEL_DIV1024_gc;       // timer start and prescaler enable
	TCF0.INTCTRLA     =    TC_OVFINTLVL_OFF_gc;
	TCF0.CCA=15;
}

init_TIM_0E(void){ // interupt for buttons
	TCE0.CTRLB        =    TC_WGMODE_NORMAL_gc;        // tryb normalny
	//TCC0.CTRLFSET     =    TC0_DIR_bm;                 // liczenie w dó³
	TCE0.CTRLA        =    TC_CLKSEL_DIV1024_gc;       // ustawienie preskalera i uruchom
	TCE0.INTCTRLA     =    TC_OVFINTLVL_LO_gc;
	TCE0.PER  = (F_CPU/1024)/250;
}

uint32_t read_rtc_time(void)
{
	return  RTC.CNT + (RTC_OVF_COUNTER*60000);
}

void BUZZ_beep(uint16_t duration)
{
	BUZZER_DELAY_TICK= duration ;
	BUZZ_ON;
}
void init_PMIC(void)
{
	sei();
	PMIC.CTRL = PMIC_LOLVLEN_bm|PMIC_MEDLVLEN_bm|PMIC_HILVLEN_bm;         // odblokowanie przerwa? o priorytecie LO
}
void init_RTC(void)
{
	CLK.RTCCTRL = CLK_RTCSRC_RCOSC_gc|CLK_RTCEN_bm; //external TOSC and clock enable ( 16 bit rtc)
	RTC.CTRL = RTC_PRESCALER_DIV1_gc;
	while(RTC.STATUS & RTC_SYNCBUSY_bm);//wait for CPU to sync with other freq
	RTC.INTCTRL = RTC_OVFINTLVL_MED_gc; // med lvl interupt (<< GPS )
	while(RTC.STATUS & RTC_SYNCBUSY_bm);//wait for CPU to sync with other freq
	RTC.PER = 60000; // overflow value
	while(RTC.STATUS & RTC_SYNCBUSY_bm);//wait for CPU to sync with other freq
	RTC.CNT= 0; // start value
}
void init_WDT(void)
{
	CPU_CCP  =   CCP_IOREG_gc;// unolc change in important registers
	WDT.CTRL=WDT_ENABLE_bm|WDT_PER_2KCLK_gc|WDT_CEN_bm; //2s WDT timeout
	while (WDT.STATUS & WDT_SYNCBUSY_bm);
}

void init_PORTS(void)
{
	/*----------------------ANALOG--------------------------*/
	// --------------PORTA--------------
	PORTA.DIRCLR = PIN0_bm;//PIN0 --> AREF 3.3v
	PORTA.DIRCLR = PIN1_bm;//PIN1 --> ADC  SHARP 1
	PORTA.DIRCLR = PIN2_bm;//PIN2 --> ADC  SHARP 2
	PORTA.DIRCLR = PIN3_bm;//PIN3 --> ADC  SHARP 3
	PORTA.DIRCLR = PIN4_bm;//PIN4 --> ADC BAT VOLTAGE
	PORTA.DIRCLR = PIN5_bm;//PIN5 --> DIGITAL SHARP
	PORTA.DIRCLR = PIN6_bm;//PIN6 --> SHARP_INT_3
	PORTA.PIN6CTRL  =    PORT_ISC_RISING_gc;
	PORTA.INT0MASK  =    PIN6_bm;
	PORTA.PIN5CTRL  =    PORT_ISC_FALLING_gc;
	PORTA.INT1MASK  =    PIN5_bm;
	PORTA.INTCTRL   =    PORT_INT0LVL_MED_gc|PORT_INT1LVL_MED_gc;
	PORTA.DIRCLR = PIN7_bm;//PIN7 --> IR_RECEIVER
	// --------------PORTB--------------
	PORTB.DIRCLR = PIN0_bm;//PIN0 --> BUTTON 1 //use interupt
	PORTB.DIRCLR = PIN1_bm;//PIN1 --> BUTTON 2 //use interupt
	PORTB.DIRCLR = PIN2_bm;//PIN2 --> BUTTON 3
	PORTB.DIRCLR = PIN3_bm;//PIN3 --> BUTTON 4
	PORTB.PIN0CTRL  =    PORT_OPC_PULLUP_gc;
	PORTB.PIN1CTRL  =    PORT_OPC_PULLUP_gc;
	PORTB.PIN2CTRL  =    PORT_OPC_PULLUP_gc;
	PORTB.PIN3CTRL  =    PORT_OPC_PULLUP_gc;
	
	PORTB.DIRSET = PIN4_bm;//PIN4 --> M1_IN1
	PORTB.DIRSET = PIN5_bm;//PIN5 --> M1_IN2
	PORTB.DIRSET = PIN6_bm;//PIN6 --> M2_IN1
	PORTB.DIRSET = PIN7_bm;//PIN7 --> M2_IN2
	/*----------------------END----ANALOG--------------------------*/
	// --------------PORTC--------------
	PORTC.DIRSET = PIN0_bm;//PIN0 -->M1 PWM
	PORTC.DIRSET = PIN1_bm;//PIN1 -->LED 0
	PORTC.DIRCLR = PIN2_bm;//PIN2 -->DBG RX
	PORTC.DIRSET = PIN3_bm;//PIN3 -->DBG TX
	//PIN4 -->
	//PIN5 -->
	PORTC.DIRCLR = PIN6_bm;//PIN6 -->SHARP_INT_2
	PORTC.PIN6CTRL  =    PORT_ISC_RISING_gc;
	PORTC.INT0MASK  =    PIN6_bm;
	
	PORTC.DIRCLR = PIN7_bm;//PIN7 -->SHARP_INT_1
	PORTC.PIN7CTRL  =    PORT_ISC_RISING_gc;
	PORTC.INT1MASK  =    PIN7_bm;
	PORTC.INTCTRL   =    PORT_INT0LVL_MED_gc|PORT_INT1LVL_MED_gc;
	// --------------PORTD--------------
	PORTD.DIRSET = PIN0_bm;//PIN0 -->M2 PWM
	//PIN1 -->
	//PIN2 -->SONAR2_ECHO
	//PIN3 -->SONAR2_TRIG
	//PIN4 -->SONAR1_ECHO
	//PIN5 -->SONAR1_TRIG
	PORTD.DIRCLR = PIN6_bm;//PIN6 -->EDGE_SENS_4
	
	PORTD.PIN6CTRL  =    PORT_ISC_FALLING_gc;//|PORT_OPC_PULLDOWN_gc;
	PORTD.INT0MASK  =    PIN6_bm;
	
	PORTD.DIRCLR = PIN7_bm;//PIN7 -->EDGE_SENS_3
	
	PORTD.PIN7CTRL  =    PORT_ISC_FALLING_gc;//|PORT_OPC_PULLDOWN_gc;
	PORTD.INT1MASK  =    PIN7_bm;
	PORTD.INTCTRL   =    PORT_INT0LVL_MED_gc|PORT_INT1LVL_MED_gc;

	// --------------PORTE--------------
	PORTE.DIRCLR    =    PIN0_bm;//PIN0 -->EDGE_SENS_2
	
	PORTE.PIN6CTRL  =    PORT_ISC_FALLING_gc;//|PORT_OPC_PULLDOWN_gc;
	PORTE.INT0MASK  =    PIN0_bm;
	
	PORTE.DIRCLR    =    PIN1_bm;//PIN1 -->EDGE_SENS_1
	
	PORTE.PIN1CTRL  =    PORT_ISC_FALLING_gc;//|PORT_OPC_PULLDOWN_gc;
	PORTE.INT1MASK  =    PIN1_bm;
	PORTE.INTCTRL   =    PORT_INT0LVL_MED_gc|PORT_INT1LVL_MED_gc;
	
	PORTE.DIRSET    =    PIN2_bm;//PIN2 -->DISP_RST
	PORTE.DIRSET    =    PIN3_bm;//PIN3 -->DISP_D/C
	PORTE.DIRSET    =    PIN4_bm;//PIN4 -->DISP_SS
	PORTE.DIRSET    =    PIN5_bm;//PIN5 -->DISP_MOSI
	//PIN6 -->
	PORTE.DIRSET    =    PIN7_bm;//PIN7 -->DISP_SCK
	// --------------PORTF--------------
	PORTF.DIRSET    =    PIN0_bm; // BUZZER
	PORTF.DIRSET    =    PIN1_bm; // LED
	PORTF.DIRSET    =    PIN2_bm; // LED
	PORTF.DIRSET    =    PIN3_bm; // LED
	PORTF.DIRSET    =    PIN4_bm; // LED
	PORTF.DIRSET    =    PIN5_bm; // LED
	PORTF.DIRSET    =    PIN6_bm; // LED
	PORTF.DIRSET    =    PIN7_bm; // LED
	//------------------------------------------------------------------------------------------
}
ButtonStatus BUTTON_status(uint8_t input,uint8_t select)
{
	static uint8_t button[10]={0,0,0,0,0,0,0,0,0};
	button[select]<<=1;
	if(input){
		button[select]|=0x01;
	}
	if(button[select]==0x7f){
		return BUTTON_RISING_EDGE;
	}
	if(button[select]==0xfe){
		return BUTTON_FALLING_EDGE;
	}
	if(button[select]>0){
		return BUTTON_PUSH;
	}
	return BUTTON_RELEASE;
}
uint8_t ATTACK(void)
{
	SENS_FLAG_s.LINE_RIGHT=0;
	SENS_FLAG_s.LINE_LEFT=0;
	BUZZ_beep(50);
	
	MOT_go_forward(80);
	IGNEORE_SENS_s.SHARP_DIGIT = read_rtc_time();
	while( read_rtc_time()-IGNEORE_SENS_s.SHARP_DIGIT<10000 && SENS_FLAG_s.LINE_LEFT==0 && SENS_FLAG_s.LINE_RIGHT==0);
	_delay_ms(1000);
	MOT_brake();
	GP_FLAGS_s.START_STOP=0;
	
// 	while( read_rtc_time()-IGNEORE_SENS_s.SHARP_DIGIT<600 )
// 	{
// 		if (SENS_FLAG_s.LINE_LEFT==1 || SENS_FLAG_s.LINE_RIGHT==1)
// 		{
// 			if (DIGITAL_SHARP_CHECK) // if we are on the line and the enemy is below us push him away
// 			{
// 				MOT_go_forward(80);
// 				_delay_ms(120);
// 				MOT_brake();
// 				GP_FLAGS_s.START_STOP=0;
// 			}
// 			else
// 			{
// 				MOT_brake();
// 				_delay_ms(20);
// 				for (uint16_t i=0;i<100;i++)
// 				{
// 					MOT_go_backward(i);
// 					_delay_ms(1);
// 				}
// 				MOT_go_backward(90);
// 				_delay_ms(60);
// 				break;
// 			}
// 			
// 		}
// 		
// 	}
	//&& DIGITAL_SHARP_CHECK); //&& DIGITAL_SHARP_CHECK);// dodac sprawdzacza stanu sharpa
	//_delay_ms(120); //insert a loop over there with check statements
	//to wsadzic do ifów do petli::
	// 	if ((SENS_FLAG_s.LINE_LEFT==1 || SENS_FLAG_s.LINE_RIGHT==1) && DIGITAL_SHARP_CHECK) // check if we are on the line and we see the enemy if yes then go away ring with full power
	// 	{
	// 		_delay_ms(120);
	// 		MOT_brake();
	// 		GP_FLAGS_s.START_STOP=0; // enemy pushed away clear flags
	// 		FLAGS_clear_all();
	// 		return ATK_PASS;
	// 	}
	// 	else
	// 	{
	// 		MOT_brake();
	// 		FLAGS_clear_all();
	// 		return ATK_FAIL;
	// 	}
}
void FLAGS_clear_all(void)
{
	SENS_FLAG_s.LINE_RIGHT=0; // clear all flags
	SENS_FLAG_s.LINE_LEFT=0;
	SENS_FLAG_s.SHARP_DIGIT=0;
	SENS_FLAG_s.SHARP_A_FRONT=0;
	SENS_FLAG_s.SHARP_A_LEFT=0;
	SENS_FLAG_s.SHARP_A_RIGHT=0;
}
void Wait_5_sec(void){
	_delay_ms(1000);
	BUZZ_beep(50);
	_delay_ms(1000);
	BUZZ_beep(50);
	_delay_ms(1000);
	BUZZ_beep(50);
	_delay_ms(1000);
	BUZZ_beep(50);
	_delay_ms(1000);
	BUZZ_beep(100); // 5s delay
}


