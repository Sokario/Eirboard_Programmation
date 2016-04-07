/*****************************************************/
/*                Define Architecture                */
/*                   STM32F429ZI                     */
/*                                                   */
/*****************************************************/

#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <stm32f4xx_hal.h>
#include <stm32f4xx.h>

#include <hal/timer_interface.hpp>
#include <hal/stm32cubef4/traits.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

#define NUCLEO
// #define EIRBOARD

#define COMM
// #define ASSERV


// Board Define
#ifdef EIRBOARD
	#define LED_1 D6
	#define LED_2 D7
	#define LED_3 G9
	#define LED_4 G10
	#define LED_5 G11
	#define LED_6 G12
	#define LED_7 G13
	#define LED_8 G14
#endif

#ifdef NUCLEO
	#define LED_1 B0
	#define LED_2 B7
	#define LED_3 B14
#endif


// Servos Define
#define SERVO_NUMBER 8
#define SERVO_LIMIT 180
#define SERVO_PERIOD 10 // us
#define SERVO_MULT XXX
#define SERVO_OFFSET XXX
#define adaptCommand(angle) angle * SERVO_MULT + SERVO_OFFSET
#define SERVO_TIMER_1 TIMER10
#define SERVO_PWM_1 TIMER10_CH1
#define SERVO_TIMER_2 TIMER11
#define SERVO_PWM_2 TIMER11_CH1
#define SERVO_TIMER_3 TIMER13
#define SERVO_PWM_3 TIMER13_CH1
#define SERVO_TIMER_4 TIMER14
#define SERVO_PWM_4 TIMER14_CH1
#define SERVO_TIMER_5 TIMER5
#define SERVO_PWM_5 TIMER5_CH3
#define SERVO_TIMER_6 TIMER5
#define SERVO_PWM_6 TIMER5_CH4
#define SERVO_TIMER_7 TIMER8
#define SERVO_PWM_7 TIMER8_CH3
#define SERVO_TIMER_8 TIMER8
#define SERVO_PWM_8 TIMER8_CH4

// extern HAL::STM32CubeF4::Private::TIMER_Type<ID> servo_timer[8] = {TIMER10, TIMER11, TIMER13, TIMER14, TIMER5, TIMER5, TIMER8, TIMER8};
// extern Private::TIMER_Type<ID> servo_pwm[8] = {TIMER10_CH1, TIMER11_CH1, TIMER13_CH1, TIMER14_CH1, TIMER5_CH3, TIMER5_CH4, TIMER8_CH3, TIMER8_CH4};

#endif