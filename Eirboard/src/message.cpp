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
	if (m_function < 40)
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
	// "DEPLACEMENT"
		case 1 : // Move the robot
			return true;
			break;

	// "POSITION"
		case 2 : // Return the robot's relative position
			return true;
			break;

	// "ORIGIN"
		case 3 : // Change the robot's relative position
			return true;
			break;

	// "PROG GP2_1"
		case 4 : // Affect the concerned GP2's value
			if (m_data <= GP2_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG GP2_2"
		case 5 : // Affect the concerned GP2's value
			if (m_data <= GP2_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG GP2_3"
		case 6 : // Affect the concerned GP2's value
			if (m_data <= GP2_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG GP2_4"
		case 7 : // Affect the concerned GP2's value
			if (m_data <= GP2_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG GP2_5"
		case 8 : // Affect the concerned GP2's value
			if (m_data <= GP2_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG GP2_6"
		case 9 : // Affect the concerned GP2's value
			if (m_data <= GP2_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG GP2_7"
		case 10 : // Affect the concerned GP2's value
			if (m_data <= GP2_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG GP2_8"
		case 11 : // Affect the concerned GP2's value
			if (m_data <= GP2_LIMIT)
				return true;
			else
				return false;
			break;		

	// "READ GP2_1"
		case 12 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_2"
		case 13 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_3"
		case 14 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_4"
		case 15 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_5"
		case 16 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_6"
		case 17 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_7"
		case 18 : // Return the concerned GP2's value
			return true;
			break;

	// "READ GP2_8"
		case 19 : // Return the concerned GP2's value
			return true;
			break;

	// "PROG SERVO_1"
		case 20 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_2"
		case 21 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_3"
		case 22 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_4"
		case 23 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_5"
		case 24 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_6"
		case 25 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_7"
		case 26 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "PROG SERVO_8"
		case 27 : // Affect the concerned servo's value
			if (m_data <= SERVO_LIMIT)
				return true;
			else
				return false;
			break;

	// "READ SERVO_1"
		case 28 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_2"
		case 29 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_3"
		case 30 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_4"
		case 31 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_5"
		case 32 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_6"
		case 33 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_7"
		case 34 : // Read the concerned servo's value
			return true;
			break;

	// "READ SERVO_8"
		case 35 : // Read the concerned servo's value
			return true;
			break;

	// "P ASSERV"
		case 36 : // Change the Proportionnal asserv' value
			return true;
			break;

	// "I ASSERV"
		case 37 : // Change the Integral asserv' value
			return true;
			break;

	// "D ASSERV"
		case 38 : // Change the Derivative asserv' value
			return true;
			break;

	// "DEFAULT ASSERV"
		case 39 : // Change to the Default asserv' values
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