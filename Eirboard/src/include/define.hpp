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
	// LEDS
	#define LED_1 D6
	#define LED_2 D7
	#define LED_3 G9
	#define LED_4 G10
	#define LED_5 G11
	#define LED_6 G12
	#define LED_7 G13
	#define LED_8 G14
	// UART
	#define UART_TX B10
	#define UART_RX B11
	// SERVO
	#define PIN_SERVO_1 F6
	#define SERVO_TIMER_1 TIMER10 //HAL::STM32CubeF4::Private::TIMER_Type<10>
	#define SERVO_PWM_1 TIMER10_CH1 // Max: 8000 | Min: 4 | Variation: 100
	#define PIN_SERVO_2 F7
	#define SERVO_TIMER_2 TIMER11
	#define SERVO_PWM_2 TIMER11_CH1 // Max: XXXX | Min: x | Variation: XXX
	#define PIN_SERVO_3 F8
	#define SERVO_TIMER_3 TIMER13
	#define SERVO_PWM_3 TIMER13_CH1 // Max: XXXX | Min: x | Variation: XXX
	#define PIN_SERVO_4 F9
	#define SERVO_TIMER_4 TIMER14
	#define SERVO_PWM_4 TIMER14_CH1
	#define PIN_SERVO_5 A2
	#define SERVO_TIMER_5 TIMER5
	#define SERVO_PWM_5 TIMER5_CH3
	#define PIN_SERVO_6 A3
	#define SERVO_TIMER_6 TIMER5
	#define SERVO_PWM_6 TIMER5_CH4
	#define PIN_SERVO_7 C8
	#define SERVO_TIMER_7 TIMER8
	#define SERVO_PWM_7 TIMER8_CH3
	#define PIN_SERVO_8 C9
	#define SERVO_TIMER_8 TIMER8
	#define SERVO_PWM_8 TIMER8_CH4
#endif

#ifdef NUCLEO
	// LEDS
	#define LED_1 B0
	#define LED_2 B7
	#define LED_3 B14
	// UART
	#define UART_TX D8
	#define UART_RX D9
	// SERVO
	#define PIN_SERVO_1 B8 // OK
	#define SERVO_TIMER_1 TIMER10 //HAL::STM32CubeF4::Private::TIMER_Type<10>
	#define SERVO_PWM_1 TIMER10_CH1 // Max: 8000 | Min: 4 | Variation: 100
	#define PIN_SERVO_2 F7 // OK
	#define SERVO_TIMER_2 TIMER11
	#define SERVO_PWM_2 TIMER11_CH1
	#define PIN_SERVO_3 F8 // OK
	#define SERVO_TIMER_3 TIMER13
	#define SERVO_PWM_3 TIMER13_CH1
	#define PIN_SERVO_4 F9 // OK
	#define SERVO_TIMER_4 TIMER14
	#define SERVO_PWM_4 TIMER14_CH1
	#define PIN_SERVO_5 C6 // OK
	#define SERVO_TIMER_5 TIMER8
	#define SERVO_PWM_5 TIMER8_CH1
	#define PIN_SERVO_6 C7 // OK
	#define SERVO_TIMER_6 TIMER8
	#define SERVO_PWM_6 TIMER8_CH2
	#define PIN_SERVO_7 C8 // OK
	#define SERVO_TIMER_7 TIMER8
	#define SERVO_PWM_7 TIMER8_CH3
	#define PIN_SERVO_8 C9 // OK
	#define SERVO_TIMER_8 TIMER8
	#define SERVO_PWM_8 TIMER8_CH4
#endif


// Servos Define
#define SERVO_NUMBER 8
#define SERVO_LIMIT 10000
#define SERVO_PERIOD 20000 // us

// GP2 Define
#define GP2_NUMBER 8
#define GP2_LIMIT 500


#endif
