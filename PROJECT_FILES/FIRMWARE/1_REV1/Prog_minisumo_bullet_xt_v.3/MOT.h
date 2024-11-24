/*
 * MOT.h
 *
 * Created: 2016-05-31 17:16:19
 *  Author: Andrzej
 */ 


#ifndef MOT_H_
#define MOT_H_
#include "Includes.h"

#define DIR_LEFT 1
#define DIR_RIGHT 2
//-------------------------------------------------------------------------------
#define M1_PWM_ON PORTC.OUTSET = PIN0_bm;
#define M1_PWM_OFF PORTC.OUTCLR = PIN0_bm;

#define M1_IN1_ON PORTB.OUTSET = PIN4_bm;
#define M1_IN1_OFF PORTB.OUTCLR = PIN4_bm;

#define  M1_IN2_ON PORTB.OUTSET = PIN5_bm;
#define  M1_IN2_OFF PORTB.OUTCLR = PIN5_bm;
//-------------------------------------------------------------------------------
#define M2_PWM_ON PORTD.OUTSET = PIN0_bm;
#define M2_PWM_OFF PORTD.OUTCLR = PIN0_bm;

#define M2_IN1_ON PORTB.OUTSET = PIN6_bm;
#define M2_IN1_OFF PORTB.OUTCLR = PIN6_bm;

#define  M2_IN2_ON PORTB.OUTSET = PIN7_bm;
#define  M2_IN2_OFF PORTB.OUTCLR = PIN7_bm;

uint32_t MOT_time;

//#define M1_INVERT 1 //uncomment to invert motor
//#define M2_INVERT 1 //uncomment to invert motor

void init_MOT_PWM(void);
void MOT_stop(void);
void MOT_brake(void);
void MOT_go_forward(uint8_t speed);
void MOT_go_backward(uint8_t speed);
void MOT_turn_left(uint8_t speed);
void MOT_turn_right(uint8_t speed);
void MOT_go_forward_arc(uint8_t ML_speed,uint8_t MR_speed);
void MOT_go_backward_arc(uint8_t ML_speed,uint8_t MR_speed);
void MOT_turn_45_deg(uint8_t dir);
void MOT_turn_90_deg(uint8_t dir);
void MOT_turn_180_deg(uint8_t dir);
//void MOT_turn_180_deg_s(uint8_t dir,uint16_t speed);

#endif /* MOT_H_ */