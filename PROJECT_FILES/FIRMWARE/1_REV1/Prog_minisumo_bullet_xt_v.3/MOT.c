/*
* MOT.c
*
* Created: 2016-05-31 17:16:08
*  Author: Andrzej
*/
#include "Includes.h"

void init_MOT_PWM(void)
{
	TCD0.CTRLB        =    TC_WGMODE_DSBOTH_gc|TC0_CCAEN_bm;
	TCD0.PER          =    100;// rozdzielczosc pwm
	TCD0.CCA          =    0;
	TCD0.CTRLA        =    TC_CLKSEL_DIV8_gc;
	//------------------------------------------------------------------
	TCC0.CTRLB        =    TC_WGMODE_DSBOTH_gc|TC0_CCAEN_bm;
	TCC0.PER          =    100;// rozdzielczosc pwm
	TCC0.CCA          =    0;
	TCC0.CTRLA        =    TC_CLKSEL_DIV8_gc;
}

void MOT_stop(void)
{
	M2_IN1_OFF
	M2_IN2_OFF
	M1_IN1_OFF
	M1_IN2_OFF
	TCC0.CCA  =  0;
	TCD0.CCA  =  0;
}

void MOT_brake(void)
{
	M2_IN1_ON
	M2_IN2_ON
	M1_IN1_ON
	M1_IN2_ON
	TCC0.CCA  =  0;
	TCD0.CCA  =  0;
}

void MOT_go_forward(uint8_t speed)
{
	#ifdef M2_INVERT
	M2_IN1_ON
	M2_IN2_OFF
	#endif
	#ifndef M2_INVERT//<<-----
	M2_IN1_OFF
	M2_IN2_ON
	#endif
	//-----------------------------------
	#ifdef M1_INVERT
	M1_IN1_OFF
	M1_IN2_ON
	#endif
	#ifndef M1_INVERT//<<-----
	M1_IN1_ON
	M1_IN2_OFF
	#endif
	TCC0.CCA  =  speed;
	TCD0.CCA  =  speed;
}

void MOT_go_backward(uint8_t speed)
{
	#ifdef M2_INVERT
	M2_IN1_OFF
	M2_IN2_ON
	#endif
	#ifndef M2_INVERT//<<-----
	M2_IN1_ON
	M2_IN2_OFF
	#endif
	//-----------------------------------
	#ifdef M1_INVERT
	M1_IN1_ON
	M1_IN2_OFF
	#endif
	#ifndef M1_INVERT//<<-----
	M1_IN1_OFF
	M1_IN2_ON
	#endif
	
	TCC0.CCA  =  speed;
	TCD0.CCA  =  speed;
}

void MOT_turn_left(uint8_t speed)
{
	#ifdef M2_INVERT
	M2_IN1_OFF
	M2_IN2_ON
	#endif
	#ifndef M2_INVERT//<<-----
	M2_IN1_ON
	M2_IN2_OFF
	#endif
	//-----------------------------------
	#ifdef M1_INVERT
	M1_IN1_OFF
	M1_IN2_ON
	#endif
	#ifndef M1_INVERT//<<-----
	M1_IN1_ON
	M1_IN2_OFF
	#endif
	
	TCC0.CCA  =  speed;
	TCD0.CCA  =  speed;
}
void MOT_turn_right(uint8_t speed)
{
	#ifdef M2_INVERT
	M2_IN1_ON
	M2_IN2_OFF
	#endif
	#ifndef M2_INVERT//<<-----
	M2_IN1_OFF
	M2_IN2_ON
	#endif
	//-----------------------------------
	#ifdef M1_INVERT
	M1_IN1_ON
	M1_IN2_OFF
	#endif
	#ifndef M1_INVERT//<<-----
	M1_IN1_OFF
	M1_IN2_ON
	#endif
	
	TCC0.CCA  =  speed;
	TCD0.CCA  =  speed;
}
void MOT_go_forward_arc(uint8_t ML_speed,uint8_t MR_speed)
{
	#ifdef M2_INVERT
	M2_IN1_ON
	M2_IN2_OFF
	#endif
	#ifndef M2_INVERT//<<-----
	M2_IN1_OFF
	M2_IN2_ON
	#endif
	//-----------------------------------
	#ifdef M1_INVERT
	M1_IN1_OFF
	M1_IN2_ON
	#endif
	#ifndef M1_INVERT//<<-----
	M1_IN1_ON
	M1_IN2_OFF
	#endif
	
	TCC0.CCA  =  ML_speed;
	TCD0.CCA  =  MR_speed;
}
void MOT_go_backward_arc(uint8_t ML_speed,uint8_t MR_speed) // define motor invert
{
	#ifdef M2_INVERT
	M2_IN1_OFF
	M2_IN2_ON
	#endif
	#ifndef M2_INVERT//<<-----
	M2_IN1_ON
	M2_IN2_OFF
	#endif
	//-----------------------------------
	#ifdef M1_INVERT
	M1_IN1_ON
	M1_IN2_OFF
	#endif
	#ifndef M1_INVERT//<<-----
	M1_IN1_OFF
	M1_IN2_ON
	#endif
	
	TCC0.CCA  =  ML_speed;
	TCD0.CCA  =  MR_speed;
}

// void MOT_delay_ms(uint16_t i)
// {
//     for (;i>=0;i--)
//     {
// 		_delay_ms(1);
//     }
// }

void MOT_turn_45_deg(uint8_t dir)
{
	if (dir==DIR_LEFT) 	MOT_turn_left(60);
    if (dir==DIR_RIGHT)	MOT_turn_right(60);
	
    _delay_ms(60);//115
//     MOT_time = read_rtc_time();
//     while(read_rtc_time()-MOT_time <= 60 && SENS_FLAG_s.LINE_LEFT==0 && SENS_FLAG_s.LINE_RIGHT==0 )

	MOT_brake();
}
void MOT_turn_90_deg(uint8_t dir)
{
	if (dir==DIR_LEFT) 	MOT_turn_left(60);
	if (dir==DIR_RIGHT)	MOT_turn_right(60);
	_delay_ms(110);//115
	MOT_brake();
}
void MOT_turn_180_deg(uint8_t dir)
{
	if (dir==DIR_LEFT) 	MOT_turn_left(60);
	if (dir==DIR_RIGHT)	MOT_turn_right(60);
	_delay_ms(190);//115
	MOT_brake();
}

// void MOT_turn_180_deg_s(uint8_t dir,uint16_t speed)
// {
// 	MOT_turn_right(speed);
// 	for (uint16_t x =-(3*speed)+360;x>=0;x--)
// 	{
// 		_delay_ms(1);
//	}
//	MOT_brake();
//}