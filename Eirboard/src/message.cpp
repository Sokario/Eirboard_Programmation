/*****************************************************/
/*               Message Architecture                */
/*                   STM32F429ZI                     */
/*                                                   */
/*****************************************************/

#include "include/message.hpp"
#include "include/calcul.hpp"

// Public

Message::Message() : 
	m_boardID (s2bin ("0000")),
	m_function (s2bin ("0000000")),
	m_parityFunction (s2bin ("0")),
	m_data(s2bin ("0000000000000000000")),
	m_parityData(s2bin ("0"))
{}

Message::Message(u32 boardID, u32 function, u32 data) : 
	m_boardID (boardID),
	m_function (function),
	m_parityFunction (s2bin ("0")),
	m_data (data),
	m_parityData(s2bin ("0"))
{}

Message::Message(char* boardID, char* function, char* data) : 
	m_boardID(s2bin (boardID)),
	m_function(s2bin (function)),
	m_parityFunction(s2bin ("0")),
	m_data(s2bin (data)),
	m_parityData(s2bin ("0"))
{}

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

void Message::createMessage(const char* boardID, const char* function, const char* data)
{
	Message::setBoardID (boardID);
	Message::setFunction (function);
	Message::setData (data);
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
	// switch (m_function)
	// {
	// // "DEPLACEMENT" function 1
	// 	case s2bin ("0000001") : // Move the robot
	// 		return true;
	// 		break;

	// // "POSITION" function 2
	// 	case s2bin ("0000010") : // Return the robot's relative position
	// 		return true;
	// 		break;

	// // "ORIGIN" function 3
	// 	case s2bin ("0000011") : // Change the robot's relative position
	// 		return true;
	// 		break;

	// // "READ GP2_1" function 4
	// 	case s2bin ("0000100") : // Return the concerned GP2's value
	// 		return true;
	// 		break;

	// // "READ GP2_2" function 5
	// 	case s2bin ("0000101") : // Return the concerned GP2's value
	// 		return true;
	// 		break;

	// // "READ GP2_3" function 6
	// 	case s2bin ("0000110") : // Return the concerned GP2's value
	// 		return true;
	// 		break;

	// // "READ GP2_4" function 7
	// 	case s2bin ("0000111") : // Return the concerned GP2's value
	// 		return true;
	// 		break;

	// // "READ GP2_5" function 8
	// 	case s2bin ("0001000") : // Return the concerned GP2's value
	// 		return true;
	// 		break;

	// // "READ GP2_6" function 9
	// 	case s2bin ("0001001") : // Return the concerned GP2's value
	// 		return true;
	// 		break;

	// // "READ GP2_7" function 10
	// 	case s2bin ("0001010") : // Return the concerned GP2's value
	// 		return true;
	// 		break;

	// // "READ GP2_8" function 11
	// 	case s2bin ("0001011") : // Return the concerned GP2's value
	// 		return true;
	// 		break;

	// // "PROG SERVO_1" function 12
	// 	case s2bin ("0001100") : // Affect the concerned servo's value
	// 		return true;
	// 		break;

	// // "PROG SERVO_2" function 13
	// 	case s2bin ("0001101") : // Affect the concerned servo's value
	// 		return true;
	// 		break;

	// // "PROG SERVO_3" function 14
	// 	case s2bin ("0001110") : // Affect the concerned servo's value
	// 		return true;
	// 		break;

	// // "PROG SERVO_4" function 15
	// 	case s2bin ("0001111") : // Affect the concerned servo's value
	// 		return true;
	// 		break;

	// // "PROG SERVO_5" function 16
	// 	case s2bin ("0010000") : // Affect the concerned servo's value
	// 		return true;
	// 		break;

	// // "PROG SERVO_6" function 17
	// 	case s2bin ("0010001") : // Affect the concerned servo's value
	// 		return true;
	// 		break;

	// // "PROG SERVO_7" function 18
	// 	case s2bin ("0010010") : // Affect the concerned servo's value
	// 		return true;
	// 		break;

	// // "PROG SERVO_8" function 19
	// 	case s2bin ("0010011") : // Affect the concerned servo's value
	// 		return true;
	// 		break;

	// // "READ SERVO_1" function 20
	// 	case s2bin ("0010100") : // Read the concerned servo's value
	// 		return true;
	// 		break;

	// // "READ SERVO_2" function 21
	// 	case s2bin ("0010101") : // Read the concerned servo's value
	// 		return true;
	// 		break;

	// // "READ SERVO_3" function 22
	// 	case s2bin ("0010110") : // Read the concerned servo's value
	// 		return true;
	// 		break;

	// // "READ SERVO_4" function 23
	// 	case s2bin ("0010111") : // Read the concerned servo's value
	// 		return true;
	// 		break;

	// // "READ SERVO_5" function 24
	// 	case s2bin ("0011000") : // Read the concerned servo's value
	// 		return true;
	// 		break;

	// // "READ SERVO_6" function 25
	// 	case s2bin ("0011001") : // Read the concerned servo's value
	// 		return true;
	// 		break;

	// // "READ SERVO_7" function 26
	// 	case s2bin ("0011010") : // Read the concerned servo's value
	// 		return true;
	// 		break;

	// // "READ SERVO_8" function 27
	// 	case s2bin ("0011011") : // Read the concerned servo's value
	// 		return true;
	// 		break;

	// // "P ASSERV" function 28
	// 	case s2bin ("0011100") : // Change the Proportionnal asserv' value
	// 		return true;
	// 		break;

	// // "I ASSERV" function 29
	// 	case s2bin ("0011101") : // Change the Integral asserv' value
	// 		return true;
	// 		break;

	// // "D ASSERV" function 30
	// 	case s2bin ("0011110") : // Change the Derivative asserv' value
	// 		return true;
	// 		break;

	// // "DEFAULT ASSERV" function 31
	// 	case s2bin ("0011111") : // Change to the Default asserv' values
	// 		return true;
	// 		break;

	// 	default :
	// 		return false;
	// }
	return true;
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
	// switch (m_data)
	// {
	// 	case "000010100101001" : // A modifier
	// 		return true;
	// 		break;

	// 	case "000011000100010" : // A modifier
	// 		return true;
	// 		break;

	// 	case "100111010100000" : // A modifier
	// 		return true;
	// 		break;		

	// 	default :
	// 		return false;
	// }
	return true;
}

bool Message::isParityData() const
{
	if (bitsParity (m_data) == m_parityData)
		return true;
	else
		return false;
}