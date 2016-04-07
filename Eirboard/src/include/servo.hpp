/*****************************************************/
/*                Servo Architecture                 */
/*                    STM32F429ZI                    */
/*                                                   */
/*****************************************************/

#ifndef SERVO_HPP
#define SERVO_HPP

#include <base/integer.hpp>

class Servo
{
public:
	Servo();
	Servo(u32 servoID, u32 angle = 0);

	bool setServoID(u32 servoID);
	u32 getServoID() const;
	bool setAngle(u32 angle);
	u32 getAngle() const;

	~Servo();

private:
	u32 m_servoID;
	u32 m_angle;
};

#endif