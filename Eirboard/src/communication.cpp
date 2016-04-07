/*****************************************************/
/*            Communication Architecture             */
/*                   STM32F429ZI                     */
/*                                                   */
/*****************************************************/

#include <hal/gpio.hpp>
#include <hal/uart.hpp>

#include "include/define.hpp"
#include "include/communication.hpp"
#include "include/calcul.hpp"
#include "include/message.hpp"

using namespace HAL;

// Gestion De l'objet UART/USART
#include <stream/hal/uart_stream.hpp>

struct MySettings : public Stream::HAL::DefaultUARTStreamSettings {
    static constexpr auto& uart = SERIAL_USART3;
    static constexpr auto& tx = D8;
    static constexpr auto& rx = D9;

    static constexpr auto baudrate = 9600;
    static constexpr auto parity = UART::Parity::NONE;
    static constexpr auto stop_bit = UART::StopBit::ONE_BIT;
    static constexpr auto word_size = 8;
};

// Nom du format Stream de l'UART "binaire"
Stream::HAL::UARTStream<MySettings> UART_2;
// Nom du format Stream de l'UART "charactère"
Stream::FormattedStreamDecorator<decltype(UART_2)> UART_1(UART_2);

void comm_rasp (char *on)
{
  Message sending ("0010", "001000", "0011001001010");
  Message receiving;
  receiving.receiveMessage (s2bin ("00011001011000010000001000000011"));
  Message error ("1111", "111111", "11111111111111111111");

  UART_1 << "=============================================" << "\n\r";
  UART_1 << "Board listenning, enter your binary message :" << "\n\r";

  // Board "free"
  u32 buffer;
  UART_2.read ((u8*) &buffer, sizeof (buffer));
  receiving.receiveMessage (buffer);
  UART_1 << "Binary received : ";
  UART_2.write ((u8*) &buffer, sizeof (buffer));
  UART_2.write ((u8*) "\n\r", 2);
  UART_1 << "---------------------------------------------" << "\n\r";
  UART_1 << "Receiving message structure : || BoardID : " << receiving.getBoardID () << " || Function : " << receiving.getFunction () << " || Parity : " << receiving.getParityFunction () << " || Data : " << receiving.getData () << " || Parity : " << receiving.getParityData () << " ||\n\r";

  u32 verification = receiving.isGood ();
  if (verification == 0)
  {
    UART_1 << "The message received is good!" << "\n\r"; // "&&&'"
    if (receiving.getFunction () == 28)
    {
      if (receiving.getData () == 201491)
        *on = '1';
      else if (receiving.getData () == 333077)
        *on = '0';
    }
  }
  else if (verification == 1)
  {
    UART_1 << "Error message occure, resend the previous message!" << "\n\r";
  }
  else
  {
    UART_1 << "Error return : " << receiving.isGood () << "\n\r";
    UART_1 << "Binary error sended : ";
    UART_2.write ((u8*) &error, sizeof (error));
    UART_2.write ((u8*) "\n\r", 2);
    UART_1 << "Integer error sended : " << error.sendMessage () << "\n\r";
    UART_1 << "Error message structure : || BoardID : " << error.getBoardID () << " || Function : " << error.getFunction () << " || Parity : " << error.getParityFunction () << " || Data : " << error.getData () << " || Parity : " << error.getParityData () << " ||\n\r";
  }
  UART_1 << "=============================================" << "\n\r" << "\n\r";
}