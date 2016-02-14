/*****************************************************/
/*               Message Architecture                */
/*                   STM32F429ZI                     */
/*                                                   */
/*****************************************************/

#pragma once

#include <base/integer.hpp>

class Message
{
public:
	Message();
	Message(u32 boardID, u32 function, u32 data);
	Message(char* boardID, char* function, char* data);

	void createMessage(const char* boardID, const char* function, const char* data);
	u32 sendMessage() const;
	void receiveMessage(u32 msg);
	u32 isGood() const;

	~Message();

// A placer en private
	void setBoardID(const char* boardID);
	u32 getBoardID() const;
	void setFunction(const char* function);
	u32 getFunction() const;
	u32 getParityFunction() const;
	void setData(const char* data);
	u32 getData() const;
	u32 getParityData() const;

private:
	bool isBoard() const;
	bool isFunction() const;
	bool isParityFunction() const;
	bool isData() const;
	bool isParityData() const;

	u32 m_boardID;
	u32 m_function;
	u32 m_parityFunction;
	u32 m_data;
	u32 m_parityData;
	bool m_good;
};