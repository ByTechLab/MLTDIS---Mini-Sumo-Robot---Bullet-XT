#include "Includes.h"

int main(void)
{
	init_OSC_PLL(PLL_FACT);
	init_PORTS();
	init_USART_C0();
	init_ADC();
	init_SPI_LCD();
	init_MOT_PWM();
	init_TIM_0E();
	init_TIM_0F();
	init_RTC();
	init_PMIC();
	BUZZ_beep(200);
	init_LCD();
	GP_FLAGS_s.MODE =MODE_STANDARD;
	SENS_FLAG_s.SHARP_DIGIT=0;
	GP_FLAGS_s.FIRST_TURN=1;
	
	uint32_t start=0;

	while(1)
	{
		LCD_menu_handle();
		if (GP_FLAGS_s.START_STOP == 1)
		{
			switch (GP_FLAGS_s.MODE)
			{
				case MODE_TORNADO :
				
				// 				if(GP_FLAGS_s.FIRST_TURN==1)
				// 				{
				// 					//Wait_5_sec();
				// 					GP_FLAGS_s.FIRST_TURN=0;
				// 				}
				//
				//  				while(GP_FLAGS_s.START_STOP == 1)
				//  				{
				//
				// //					MOT_turn_right(30);
				// // 					if (SENS_FLAG_s.SHARP_A_FRONT==1)
				// // 					{
				// // 						MOT_brake();
				// // 						_delay_ms(50);
				// // 						MOT_go_forward(70);
				// // 						_delay_ms(250);
				// // 						SENS_FLAG_s.SHARP_A_FRONT=0;
				// // 					}
				//
				// // 					else
				// // 					{
				// // 						MOT_turn_right(30);
				// // 					}
				// //
				// // 					if (DIGITAL_SHARP_CHECK)
				// // 					{
				// // 						MOT_go_forward(60);
				// // 						_delay_ms(50);
				// // 					}
				// // 					else
				// // 					{
				// // 						MOT_turn_right(30);
				// // 					}
				//
				//
				// 					//----------------------------------------------------------------LINE::::---->>>>>
				//
				//
				//
				// 					if ((SENS_FLAG_s.LINE_LEFT==1 && SENS_FLAG_s.LINE_RIGHT==1)&&read_rtc_time()-IGNEORE_SENS_s.LINE>250) // line sense escape + delay
				// 					{
				// 						MOT_brake();
				// 						_delay_ms(20);
				// 						//MOT_go_backward(90);
				//
				// 						for (uint16_t i=0;i<100;i++)
				// 						{
				// 							MOT_go_backward(i);
				// 							_delay_ms(1);
				// 						}
				// 						MOT_go_backward(90);
				// 						_delay_ms(60);
				// 						MOT_brake();
				//
				// 						MOT_turn_180_deg(DIR_RIGHT);
				//
				// 						SENS_FLAG_s.LINE_RIGHT=0;
				// 						SENS_FLAG_s.LINE_LEFT=0;
				// 						IGNEORE_SENS_s.LINE = read_rtc_time();
				// 						BUZZ_beep(10);
				// 					}
				//
				// 					if ( SENS_FLAG_s.LINE_RIGHT==1 && read_rtc_time()-IGNEORE_SENS_s.LINE>250) // line sense escape + delay
				// 					{
				// 						MOT_brake();
				// 						_delay_ms(20);
				// 						//MOT_go_backward(90);
				//
				// 						for (uint16_t i=0;i<100;i++)
				// 						{
				// 							MOT_go_backward(i);
				// 							_delay_ms(1);
				// 						}
				//
				// 						MOT_go_backward(90);
				// 						_delay_ms(60);
				// 						MOT_brake();
				//
				// 						MOT_turn_90_deg(DIR_LEFT);
				//
				// 						MOT_turn_left(50);
				// 						_delay_ms(60); // turn a little more
				// 						MOT_brake();
				//
				// 						SENS_FLAG_s.LINE_RIGHT=0;
				// 						SENS_FLAG_s.LINE_LEFT=0;
				// 						IGNEORE_SENS_s.LINE = read_rtc_time();
				// 						BUZZ_beep(10);
				// 					}
				//
				// 					if (SENS_FLAG_s.LINE_LEFT==1 && read_rtc_time()-IGNEORE_SENS_s.LINE>250) // line sense escape + delay
				// 					{
				// 						MOT_brake();
				// 						_delay_ms(20);
				//
				// 						for (uint16_t i=0;i<100;i++)
				// 						{
				// 							MOT_go_backward(i);
				// 							_delay_ms(1);
				// 						}
				//
				// 						MOT_go_backward(90);
				// 						_delay_ms(60);
				// 						MOT_brake();
				//
				// 						MOT_turn_90_deg(DIR_RIGHT);
				//
				// 						MOT_turn_right(50);
				// 						_delay_ms(60);
				// 						MOT_brake();
				//
				// 						SENS_FLAG_s.LINE_RIGHT=0;
				// 						SENS_FLAG_s.LINE_LEFT=0;
				// 						IGNEORE_SENS_s.LINE = read_rtc_time();
				// 						BUZZ_beep(50);
				// 					}
				//
				// 					if (SENS_FLAG_s.SHARP_A_FRONT==1)
				// 					{
				// 						MOT_brake();
				// 						MOT_go_forward(40);
				//
				// 						IGNEORE_SENS_s.SHARP_A_FRONT  = read_rtc_time();
				// 						while(read_rtc_time()-IGNEORE_SENS_s.SHARP_A_FRONT <1000 && DIGITAL_SHARP_CHECK)
				// 						{
				// 							//	if (SENS_FLAG_s.SHARP_A_LEFT==1)break; // we have sensed left sharp so we dont clear flag and go out that loop
				// 							//	if (SENS_FLAG_s.SHARP_A_RIGHT==1)break;
				// 								if (SENS_FLAG_s.LINE_LEFT==1)break;// we have sensed that during comeup we are on the line so break and dont clear flag
				// 								if (SENS_FLAG_s.LINE_RIGHT==1)break;
				// 						}
				// 						MOT_brake();
				// 						SENS_FLAG_s.SHARP_A_FRONT=0;
				// 					}
				// 					else
				// 					{
				// 							MOT_turn_right(35);
				// 					}
				//
				// 					// to dac to wew petli od frontu bo nie mozemy skerecec podczas wolnej jazdy
				//
				// 					if (SENS_FLAG_s.SHARP_A_LEFT==1 && read_rtc_time()-IGNEORE_SENS_s.SHARP_A_LEFT>100) //&& SENS_FLAG_s.LINE_LEFT==0 && SENS_FLAG_s.LINE_RIGHT==0) // czy to nie musi byc przed frontowym?
				// 					{
				// 						MOT_turn_45_deg(DIR_LEFT);
				// 						SENS_FLAG_s.SHARP_A_LEFT=0;
				// 						IGNEORE_SENS_s.SHARP_A_LEFT = read_rtc_time();
				// 					}
				//
				// 					if (SENS_FLAG_s.SHARP_A_RIGHT==1 && read_rtc_time()-IGNEORE_SENS_s.SHARP_A_RIGHT>100)// && SENS_FLAG_s.LINE_LEFT==0 && SENS_FLAG_s.LINE_RIGHT==0)
				// 					{
				// 						MOT_turn_45_deg(DIR_RIGHT);
				// 						SENS_FLAG_s.SHARP_A_RIGHT=0;
				// 						IGNEORE_SENS_s.SHARP_A_RIGHT = read_rtc_time();
				// 					}
				//
				//
				// 				}
				//
				//
				
				break;
				
				case MODE_LF :
				break;
				
				case MODE_STANDARD :
				
				//----------first rotate
				if(GP_FLAGS_s.FIRST_TURN==1)
				{
					Wait_5_sec();
					MOT_turn_right(30);
					_delay_ms(50); // opoznienie dla klapki
					IGNEORE_SENS_s.SHARP_A_FRONT  = read_rtc_time();
					while(read_rtc_time()-IGNEORE_SENS_s.SHARP_A_FRONT <650 && (SENS_FLAG_s.LINE_LEFT==0 && SENS_FLAG_s.LINE_RIGHT==0))
					{
						if (SENS_FLAG_s.SHARP_A_FRONT==1||SENS_FLAG_s.SHARP_DIGIT==1)
						{
							MOT_go_forward(40);
							SENS_FLAG_s.SHARP_A_LEFT=0;
							SENS_FLAG_s.SHARP_A_RIGHT=0;
							break;
						}
					}
					if (SENS_FLAG_s.SHARP_A_FRONT==0 && SENS_FLAG_s.SHARP_DIGIT==0)
					{
						MOT_brake();
					}
					GP_FLAGS_s.FIRST_TURN=0;
				}
				else
				{
					MOT_go_forward(40);
				}
				
				//----------------------------------------------------------------LINE::::---->>>>>

				
				if ((SENS_FLAG_s.LINE_LEFT==1 && SENS_FLAG_s.LINE_RIGHT==1)&&read_rtc_time()-IGNEORE_SENS_s.LINE>250) // line sense escape + delay
				{
					MOT_brake();
					_delay_ms(20);
					//MOT_go_backward(90);
					
					for (uint16_t i=0;i<100;i++)
					{
						MOT_go_backward(i);
						_delay_ms(1);
					}
					MOT_go_backward(90);
					_delay_ms(60);
					MOT_brake();
					
					MOT_turn_180_deg(DIR_RIGHT);
					
					SENS_FLAG_s.LINE_RIGHT=0;
					SENS_FLAG_s.LINE_LEFT=0;
					IGNEORE_SENS_s.LINE = read_rtc_time();
					BUZZ_beep(10);
				}
				
				if ( SENS_FLAG_s.LINE_RIGHT==1 && read_rtc_time()-IGNEORE_SENS_s.LINE>250) // line sense escape + delay
				{
					MOT_brake();
					_delay_ms(20);
					//MOT_go_backward(90);
					
					for (uint16_t i=0;i<100;i++)
					{
						MOT_go_backward(i);
						_delay_ms(1);
					}
					
					MOT_go_backward(90);
					_delay_ms(60);
					MOT_brake();
					
					MOT_turn_90_deg(DIR_LEFT);
					
					MOT_turn_left(50);
					_delay_ms(60); // turn a little more
					MOT_brake();
					
					SENS_FLAG_s.LINE_RIGHT=0;
					SENS_FLAG_s.LINE_LEFT=0;
					IGNEORE_SENS_s.LINE = read_rtc_time();
					BUZZ_beep(10);
				}
				
				if (SENS_FLAG_s.LINE_LEFT==1 && read_rtc_time()-IGNEORE_SENS_s.LINE>250) // line sense escape + delay
				{
					MOT_brake();
					_delay_ms(20);
					
					for (uint16_t i=0;i<100;i++)
					{
						MOT_go_backward(i);
						_delay_ms(1);
					}
					
					MOT_go_backward(90);
					_delay_ms(60);
					MOT_brake();
					
					MOT_turn_90_deg(DIR_RIGHT);
					
					MOT_turn_right(50);
					_delay_ms(60);
					MOT_brake();
					
					SENS_FLAG_s.LINE_RIGHT=0;
					SENS_FLAG_s.LINE_LEFT=0;
					IGNEORE_SENS_s.LINE = read_rtc_time();
					BUZZ_beep(50);
				}
				//------------------------------------------------------------------------------SHARPS::::---->>>>
				
				if (SENS_FLAG_s.SHARP_DIGIT==1)
				{
					//<<<---------check loop for a some time to ensure that enemy is below us
					ATTACK();
					// 					IGNEORE_SENS_s.SHARP_DIGIT = read_rtc_time();
					// 					MOT_brake();
					// 					while(1)
					// 					{
					// 						if (read_rtc_time()-IGNEORE_SENS_s.SHARP_DIGIT>60)
					// 						{
					// 							if (DIGITAL_SHARP_CHECK)
					// 							{
					// 								ATTACK();
					// 								break;
					// 							}
					// 							else
					// 							{
					// 								break;
					// 							}
					// 						}
					//
					// 					}
					SENS_FLAG_s.SHARP_DIGIT=0;
				}
				
				
				if (SENS_FLAG_s.SHARP_A_FRONT==1)
				{
					MOT_brake();
					IGNEORE_SENS_s.SHARP_A_FRONT = read_rtc_time();
					while(read_rtc_time()-IGNEORE_SENS_s.SHARP_A_FRONT <50 && ANALOG_SHARP_FRONT_CHECK);
					//----------------------------------------------------------
					MOT_go_forward(40);
					
					IGNEORE_SENS_s.SHARP_A_FRONT  = read_rtc_time();
					while(read_rtc_time()-IGNEORE_SENS_s.SHARP_A_FRONT <650 && ANALOG_SHARP_FRONT_CHECK)
					{
						if (SENS_FLAG_s.SHARP_DIGIT==1)
						{
							MOT_go_forward(40);
							IGNEORE_SENS_s.SHARP_DIGIT = read_rtc_time();
							while (read_rtc_time()-IGNEORE_SENS_s.SHARP_DIGIT <350)
							{
								if (DIGITAL_SHARP_CHECK_NEG)
								{
									SENS_FLAG_s.SHARP_DIGIT=0;
									break;
								}
								if (SENS_FLAG_s.SHARP_A_LEFT==1)
								{
									SENS_FLAG_s.SHARP_DIGIT=0;
									break;
								} // we have sensed left sharp so we dont clear flag and go out that loop
								if (SENS_FLAG_s.SHARP_A_RIGHT==1)
								{
									SENS_FLAG_s.SHARP_DIGIT=0;
									break;
								}
								if (SENS_FLAG_s.LINE_LEFT==1)
								{
									SENS_FLAG_s.SHARP_DIGIT=0;
									break;
								}// we have sensed that during comeup we are on the line so break and dont clear flag
								if (SENS_FLAG_s.LINE_RIGHT==1)
								{
									SENS_FLAG_s.SHARP_DIGIT=0;
									break;
								}
							}
							MOT_brake();
							//<<<---------check loop for a some time to ensure that enemy is below us
							//if (ATTACK()==ATK_FAIL) break;
							break;
						}
						else
						{
							if (SENS_FLAG_s.SHARP_A_LEFT==1)break; // we have sensed left sharp so we dont clear flag and go out that loop
							if (SENS_FLAG_s.SHARP_A_RIGHT==1)break;
							if (SENS_FLAG_s.LINE_LEFT==1)break;// we have sensed that during comeup we are on the line so break and dont clear flag
							if (SENS_FLAG_s.LINE_RIGHT==1)break;
						}
					}
					MOT_brake();
					SENS_FLAG_s.SHARP_A_FRONT=0;
				}
				
				// to dac to wew petli od frontu bo nie mozemy skerecec podczas wolnej jazdy
				
				if (SENS_FLAG_s.SHARP_A_LEFT==1 && read_rtc_time()-IGNEORE_SENS_s.SHARP_A_LEFT>100) //&& SENS_FLAG_s.LINE_LEFT==0 && SENS_FLAG_s.LINE_RIGHT==0) // czy to nie musi byc przed frontowym?
				{
					MOT_turn_45_deg(DIR_LEFT);
					SENS_FLAG_s.SHARP_A_LEFT=0;
					IGNEORE_SENS_s.SHARP_A_LEFT = read_rtc_time();
				}
				
				if (SENS_FLAG_s.SHARP_A_RIGHT==1 && read_rtc_time()-IGNEORE_SENS_s.SHARP_A_RIGHT>100)// && SENS_FLAG_s.LINE_LEFT==0 && SENS_FLAG_s.LINE_RIGHT==0)
				{
					MOT_turn_45_deg(DIR_RIGHT);
					SENS_FLAG_s.SHARP_A_RIGHT=0;
					IGNEORE_SENS_s.SHARP_A_RIGHT = read_rtc_time();
				}

				break;
			}
		}
		else
		{
			FLAGS_clear_all();
			GP_FLAGS_s.FIRST_TURN=1;
			MOT_brake();
			MOT_stop();
		}
		
		//LED_blink();
		//uint32_t range = ReadADC(MEAS_SHARP_FRONT);
		//send_uint32t(range,1);
	}
}

ISR(PORTD_INT0_vect) {// line sensor r
	SENS_FLAG_s.LINE_RIGHT=1;
}
ISR(PORTD_INT1_vect) {// line sensor l
	SENS_FLAG_s.LINE_LEFT=1;
	//cli();
	//sei();
}
ISR(PORTE_INT0_vect) {// line sensor
}
ISR(PORTE_INT1_vect) {// line sensor
}
ISR(PORTC_INT0_vect) {// sharp analog front
	//BUZZ_beep(10);
	SENS_FLAG_s.SHARP_A_FRONT=1;
}
ISR(PORTC_INT1_vect) {// sharp analog left
	SENS_FLAG_s.SHARP_A_LEFT=1;
}
ISR(PORTA_INT0_vect) {// sharp analg right
	SENS_FLAG_s.SHARP_A_RIGHT=1;
}
ISR(PORTA_INT1_vect) {// // sharp digital
	SENS_FLAG_s.SHARP_DIGIT=1;
}
ISR(TCE0_OVF_vect) {		//button sense interupt 4ms
	if (BUTTON_status(BUTTON_1_CHECK,BUTTON_1)==BUTTON_RISING_EDGE) BTN_s._1=1;
	if (BUTTON_status(BUTTON_2_CHECK,BUTTON_2)==BUTTON_RISING_EDGE) BTN_s._2=1;
	if (BUTTON_status(BUTTON_3_CHECK,BUTTON_3)==BUTTON_RISING_EDGE) BTN_s._3=1;
	if (BUTTON_status(BUTTON_4_CHECK,BUTTON_4)==BUTTON_RISING_EDGE) BTN_s._4=1;
	
	if (BUZZER_DELAY_TICK == 0) BUZZ_OFF;
	if (BUZZER_DELAY_TICK > 0)BUZZER_DELAY_TICK--;
}
ISR(RTC_OVF_vect){
	RTC_OVF_COUNTER++;
}
ISR(USARTC0_RXC_vect)
{
	//	LED_toggle();
	USART_RX_DATA = USARTC0.DATA;
	
	switch (USART_RX_DATA)
	{
		case 'R':
		MOT_turn_right(50);
		break;
		
		case 'L':
		MOT_turn_left(50);
		break;
		
		case 'U':
		MOT_go_forward(100);
		break;
		
		case 'D':
		MOT_go_backward(50);
		break;
		
		case 'C':
		MOT_stop();
		break;
		
		
		case 'a':
		BUZZ_beep(50);
		GP_FLAGS_s.START_STOP ^= 1 << 0;
		break;
		
		case 'b':
		GP_FLAGS_s.MODE=MODE_STANDARD;
		break;
		
		case 'c':
		GP_FLAGS_s.MODE=MODE_TORNADO;
		break;
		
	}
	
}


