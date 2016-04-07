/*****************************************************/
/*               Message Architecture                */
/*                   STM32F429ZI                     */
/*                                                   */
/*****************************************************/

#include "include/message.hpp"
#include "include/calcul.hpp"
#include "include/define.hpp"

// Public

Message::Message() : 
	m_boardID (s2bin ("0000")),
	m_function (s2bin ("0000000")),
	m_parityFunction (s2bin ("0")),
	m_data (s2bin ("0000000000000000000")),
	m_parityData (s2bin ("0"))
{}

Message::Message(u32 boardID, u32 function, u32 data) : 
	m_boardID (boardID),
	m_function (function),
	m_parityFunction (s2bin ("0")),
	m_data (data),
	m_parityData (s2bin ("0"))
{
	m_parityFunction = bitsParity (m_function);
	m_parityData = bitsParity (m_data);
}

Message::Message(char* boardID, char* function, char* data) : 
	m_boardID (s2bin (boardID)),
	m_function (s2bin (function)),
	m_parityFunction (s2bin ("0")),
	m_data (s2bin (data)),
	m_parityData (s2bin ("0"))
{
	m_parityFunction = bitsParity (m_function);
	m_parityData = bitsParity (m_data);	
}

void Message::setBoardID(const char* boardID)
{
	m_boardID = s2bin (boardID);
}

u32 Message::getBoardID() const
{
	return m_boardID;
}

void Message::setFunction(const char* function)
{
	m_function = s2bin (function);
	m_parityFunction = bitsParity (m_function);
}

u32 Message::getFunction() const
{
	return m_function;
}

u32 Message::getParityFunction() const
{
	return m_parityFunction;
}

void Message::setData(const char* data)
{
	m_data = s2bin (data);
	m_parityData = bitsParity (m_data);
}

u32 Message::getData() const
{
	return m_data;
}

u32 Message::getParityData() const
{
	return m_parityData;
}

u32 Message::sendMessage() const
{
	u32 msg = 0;
	msg = (m_parityData) | (m_data << 1) | (m_parityFunction << 21) | (m_function << 22) | (m_boardID << 28);
	return msg;
}

void Message::receiveMessage(u32 msg)
{
	u32 maskID = s2bin ("11110000000000000000000000000000");
	u32 maskFunction = s2bin ("1111110000000000000000000000");
	u32 maskParityFunction = s2bin ("1000000000000000000000");
	u32 maskData = s2bin ("111111111111111111110");
	u32 maskParityData = s2bin ("1");

	m_boardID = (msg & maskID) >> 28;
	m_function = (msg & maskFunction) >> 22;
	m_parityFunction = (msg & maskParityFunction) >> 21;
	m_data = (msg & maskData) >> 1;
	m_parityData = (msg & maskParityData);
}

u32 Message::isGood() const
{
	if (Message::getBoardID () != 15)
	{
		if (Message::isBoard () == true)
		{
			if (Message::isParityFunction () == true)
			{
				if (Message::isFunction () == true)
				{
					if (Message::isParityData () == true)
					{
						if (Message::isData () == true)
							return 0;
						else
							return 6;
					}
					else
						return 5;
				}
				else
					return 4;
			}
			else
				return 3;
		}
		else
			return 2;
	}
	else
		return 1;
}

Message::~Message()
{}

// Private

bool Message::isBoard() const
{
	if (bitsCount (m_boardID) == 1)
	{
		if (m_boardID == s2bin ("0010")) // Correspond à Eirboard
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Message::isFunction() const
{	
	if (m_function < 32)
		return true;
	else if (m_function == 63)
		return true;
	else
		return false;
}

bool Message::isParityFunction() const
{
	if (bitsParity (m_function) == m_parityFunction)
		return true;
	else
		return false;
}

bool Message::isData() const
{
	switch (m_function)
	{
	// "DEPLACEMENT" function 1
		case 1 : // Move the robot
			return true;
			break;

	// "POSITION" function 2
		case 2 : // Return the robot's relative position
			return true;
			break;

	// "ORIGIN" function 3
		case 3 : // Change the robot's relative position
			return true;
			break;

	// "READ GP2_1" function 4
		case 4 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_2" function 5
		case 5 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_3" function 6
		case 6 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_4" function 7
		case 7 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_5" function 8
		case 8 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_6" function 9
		case 9 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_7" function 10
		case 10 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_8" function 11
		case 11 : // Return the concerned GP2's value
			return true;
			break;

	// "PROG SERVO_1" function 12
		case 12 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_2" function 13
		case 13 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_3" function 14
		case 14 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_4" function 15
		case 15 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_5" function 16
		case 16 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_6" function 17
		case 17 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_7" function 18
		case 18 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_8" function 19
		case 19 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "READ SERVO_1" function 20
		case 20 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_2" function 21
		case 21 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_3" function 22
		case 22 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_4" function 23
		case 23 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_5" function 24
		case 24 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_6" function 25
		case 25 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_7" function 26
		case 26 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_8" function 27
		case 27 : // Read the concerned servo's value
			return true;
			break;

	// "P ASSERV" function 28
		case 28 : // Change the Proportionnal asserv' value
			return true;
			break;

	// "I ASSERV" function 29
		case 29 : // Change the Integral asserv' value
			return true;
			break;

	// "D ASSERV" function 30
		case 30 : // Change the Derivative asserv' value
			return true;
			break;

	// "DEFAULT ASSERV" function 31
		case 31 : // Change to the Default asserv' values
			return true;
			break;

		default :
			return false;
	}
}

bool Message::isParityData() const
{
	if (bitsParity (m_data) == m_parityData)
		return true;
	else
		return false;
}