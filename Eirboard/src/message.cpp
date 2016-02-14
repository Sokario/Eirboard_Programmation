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
	// 	case s2bin ("0000000") : // Correspond à la fonction
	// 		return true;
	// 		break;

	// 	case s2bin ("0000001") : // Correspond à la fonction
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