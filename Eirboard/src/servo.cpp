/*****************************************************/
/*                Servo Architecture                 */
/*                    STM32F429ZI                    */
/*                                                   */
/*****************************************************/

#include <hal/timer.hpp>
#include <hal/pwm.hpp>

using namespace HAL;

#include "include/define.hpp"
#include "include/servo.hpp"

Servo::Servo() : 
	m_servoID (0),
	m_angle (0)
{}

Servo::Servo(u32 servoID, u32 angle) : 
	m_servoID (0),
	m_angle (0)
{
	setServoID(servoID);
	setAngle(angle);
}

bool Servo::setServoID(u32 servoID)
{
	if (servoID > SERVO_NUMBER)
		return false;
	else
	{
		//arrêt de la pwm précédente
		// TIMER::stop();

		// Initialisation des parammètres des TIMERs
	  	TIMER::Settings timer_settings;  
	 	timer_settings.period = SERVO_PERIOD; //us

	  	// Initialisation des parammètres des PWMs 
	  	PWM::Settings pwm_settings;
	  	pwm_settings.polarity = PWM::Polarity::HIGH;

	  	// Initialisation des TIMERs à l'aide des parammètres
	  	// Initialisation des PWMs à l'aide des parammètres
	  	if (servoID == 1)
	  	{
		  	TIMER::init(SERVO_TIMER_1, timer_settings);
		  	PWM::init(SERVO_PWM_1, F6, pwm_settings);
	  		TIMER::start(SERVO_TIMER_1);
	  		PWM::setPulseWidth(SERVO_PWM_1, 0);
	  	}
	  	else if (servoID == 2)
		{
		  	TIMER::init(SERVO_TIMER_2, timer_settings);
		  	PWM::init(SERVO_PWM_2, F7, pwm_settings);
	  		TIMER::start(SERVO_TIMER_2);
	  		PWM::setPulseWidth(SERVO_PWM_2, 0);
	  	}
	  	else if (servoID == 3)
		{
		  	TIMER::init(SERVO_TIMER_3, timer_settings);
		  	PWM::init(SERVO_PWM_3, F8, pwm_settings);
	  		TIMER::start(SERVO_TIMER_3);
	  		PWM::setPulseWidth(SERVO_PWM_3, 0);
	  	}
	  	else if (servoID == 4)
		{
		  	TIMER::init(SERVO_TIMER_4, timer_settings);
		  	PWM::init(SERVO_PWM_4, F9, pwm_settings);
	  		TIMER::start(SERVO_TIMER_4);
	  		PWM::setPulseWidth(SERVO_PWM_4, 0);
	  	}
	  	else if (servoID == 5)
		{
		  	TIMER::init(SERVO_TIMER_5, timer_settings);
		  	PWM::init(SERVO_PWM_5, A2, pwm_settings);
	  		TIMER::start(SERVO_TIMER_5);
	  		PWM::setPulseWidth(SERVO_PWM_5, 0);
	  	}
	  	else if (servoID == 6)
		{
		  	TIMER::init(SERVO_TIMER_6, timer_settings);
		  	PWM::init(SERVO_PWM_6, A3, pwm_settings);
	  		TIMER::start(SERVO_TIMER_6);
	  		PWM::setPulseWidth(SERVO_PWM_6, 0);
	  	}
	  	else if (servoID == 7)
		{
		  	TIMER::init(SERVO_TIMER_7, timer_settings);
		  	PWM::init(SERVO_PWM_7, C8, pwm_settings);
	  		TIMER::start(SERVO_TIMER_7);
	  		PWM::setPulseWidth(SERVO_PWM_7, 0);
	  	}
	  	else if (servoID == 8)
		{
		  	TIMER::init(SERVO_TIMER_8, timer_settings);
		  	PWM::init(SERVO_PWM_8, C9, pwm_settings);
			TIMER::start(SERVO_TIMER_8);
			PWM::setPulseWidth(SERVO_PWM_8, 0);
		}

		m_servoID = servoID;
		return true;
	}
}

u32 Servo::getServoID() const
{
	return m_servoID;
}

bool Servo::setAngle(u32 angle)
{
	if (angle > SERVO_LIMIT)
		return false;
	else
	{
		if (m_servoID == 1)
		  	PWM::setPulseWidth(SERVO_PWM_1, angle);
	  	else if (m_servoID == 2)
			PWM::setPulseWidth(SERVO_PWM_2, angle);
	  	else if (m_servoID == 3)
			PWM::setPulseWidth(SERVO_PWM_3, angle);
	  	else if (m_servoID == 4)
			PWM::setPulseWidth(SERVO_PWM_4, angle);
	  	else if (m_servoID == 5)
			PWM::setPulseWidth(SERVO_PWM_5, angle);
	  	else if (m_servoID == 6)
			PWM::setPulseWidth(SERVO_PWM_6, angle);
	  	else if (m_servoID == 7)
			PWM::setPulseWidth(SERVO_PWM_7, angle);
	  	else if (m_servoID == 8)
			PWM::setPulseWidth(SERVO_PWM_8, angle);

		m_angle = angle;
		return true;
	}
}

u32 Servo::getAngle() const
{
	return m_angle;
}

Servo::~Servo()
{}