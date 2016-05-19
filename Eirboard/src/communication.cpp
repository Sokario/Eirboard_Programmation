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
#include "include/global.hpp"

using namespace HAL;

// Gestion De l'objet UART/USART
#include <stream/hal/uart_stream.hpp>

struct MySettings : public Stream::HAL::DefaultUARTStreamSettings {
    static constexpr auto& uart = SERIAL_USART3;
    static constexpr auto& tx = UART_TX;
    static constexpr auto& rx = UART_RX;

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
    u32 value = receiving.getData ();
    UART_1 << "The message received is good!" << "\n\r";
    if (receiving.getFunction () == 4)
    {
      gp2_1.setLimitValue (value);
      UART_1 << "GP2_1 Data detection changed!" << "\n\r";
    }
    else if (receiving.getFunction () == 5)
    {
      gp2_2.setLimitValue (value);
      UART_1 << "GP2_2 Data detection changed!" << "\n\r";
    }
    else if (receiving.getFunction () == 6)
    {
      gp2_3.setLimitValue (value);
      UART_1 << "GP2_3 Data detection changed!" << "\n\r";
    }
    else if (receiving.getFunction () == 7)
    {
      gp2_4.setLimitValue (value);
      UART_1 << "GP2_4 Data detection changed!" << "\n\r";
    }
    else if (receiving.getFunction () == 8)
    {
      gp2_5.setLimitValue (value);
      UART_1 << "GP2_5 Data detection changed!" << "\n\r";
    }
    else if (receiving.getFunction () == 9)
    {
      gp2_6.setLimitValue (value);
      UART_1 << "GP2_6 Data detection changed!" << "\n\r";
    }
    else if (receiving.getFunction () == 10)
    {
      gp2_7.setLimitValue (value);
      UART_1 << "GP2_7 Data detection changed!" << "\n\r";
    }
    else if (receiving.getFunction () == 11)
    {
      gp2_8.setLimitValue (value);
      UART_1 << "GP2_8 Data detection changed!" << "\n\r";
    }
    else if (receiving.getFunction () == 12)
    {
      value = gp2_1.getDetection ();
      UART_1 << "GP2_1 Data: " << value << "\n\r";
      // UART_2.write ((u8*) &value, sizeof (value));
    }
    else if (receiving.getFunction () == 13)
    {
      value = gp2_2.getDetection ();
      UART_1 << "GP2_2 Data: " << value << "\n\r";
      // UART_2.write ((u8*) &value, sizeof (value));
    }
    else if (receiving.getFunction () == 14)
    {
      value = gp2_3.getDetection ();
      UART_1 << "GP2_3 Data: " << value << "\n\r";
      // UART_2.write ((u8*) &value, sizeof (value));
    }
    else if (receiving.getFunction () == 15)
    {
      value = gp2_4.getDetection ();
      UART_1 << "GP2_4 Data: " << value << "\n\r";
      // UART_2.write ((u8*) &value, sizeof (value));
    }
    else if (receiving.getFunction () == 16)
    {
      value = gp2_5.getDetection ();
      UART_1 << "GP2_5 Data: " << value << "\n\r";
      // UART_2.write ((u8*) &value, sizeof (value));
    }
    else if (receiving.getFunction () == 17)
    {
      value = gp2_6.getDetection ();
      UART_1 << "GP2_6 Data: " << value << "\n\r";
      // UART_2.write ((u8*) &value, sizeof (value));
    }
    else if (receiving.getFunction () == 18)
    {
      value = gp2_7.getDetection ();
      UART_1 << "GP2_7 Data: " << value << "\n\r";
      // UART_2.write ((u8*) &value, sizeof (value));
    }
    else if (receiving.getFunction () == 19)
    {
      value = gp2_8.getDetection ();
      UART_1 << "GP2_8 Data: " << value << "\n\r";
      // UART_2.write ((u8*) &value, sizeof (value));
    }
    else if (receiving.getFunction () == 20)
    {
      servo_1.setAngle (value);
      UART_1 << "ServoMoteur 1 déplacé!" << "\n\r";
    }
    else if (receiving.getFunction () == 21)
    {
      servo_2.setAngle (value);
      UART_1 << "ServoMoteur 2 déplacé!" << "\n\r";
    }
    else if (receiving.getFunction () == 22)
    {
      servo_3.setAngle (value);
      UART_1 << "ServoMoteur 3 déplacé!" << "\n\r";
    }
    else if (receiving.getFunction () == 23)
    {
      servo_4.setAngle (value);
      UART_1 << "ServoMoteur 4 déplacé!" << "\n\r";
    }
    else if (receiving.getFunction () == 24)
    {
      servo_5.setAngle (value);
      UART_1 << "ServoMoteur 5 déplacé!" << "\n\r";
    }
    else if (receiving.getFunction () == 25)
    {
      servo_6.setAngle (value);
      UART_1 << "ServoMoteur 6 déplacé!" << "\n\r";
    }
    else if (receiving.getFunction () == 26)
    {
      servo_7.setAngle (value);
      UART_1 << "ServoMoteur 7 déplacé!" << "\n\r";
    }
    else if (receiving.getFunction () == 27)
    {
      servo_8.setAngle (value);
      UART_1 << "ServoMoteur 8 déplacé!" << "\n\r";
    }
    else if (receiving.getFunction () == 28)
    {
      value = servo_1.getAngle ();
      UART_1 << "ServoMoteur 1 Data: " << value << "\n\r";
    }
    else if (receiving.getFunction () == 29)
    {
      value = servo_2.getAngle ();
      UART_1 << "ServoMoteur 2 Data: " << value << "\n\r";
    }
    else if (receiving.getFunction () == 30)
    {
      value = servo_3.getAngle ();
      UART_1 << "ServoMoteur 3 Data: " << value << "\n\r";
    }
    else if (receiving.getFunction () == 31)
    {
      value = servo_4.getAngle ();
      UART_1 << "ServoMoteur 4 Data: " << value << "\n\r";
    }
    else if (receiving.getFunction () == 32)
    {
      value = servo_5.getAngle ();
      UART_1 << "ServoMoteur 5 Data: " << value << "\n\r";
    }
    else if (receiving.getFunction () == 33)
    {
      value = servo_6.getAngle ();
      UART_1 << "ServoMoteur 6 Data: " << value << "\n\r";
    }
    else if (receiving.getFunction () == 34)
    {
      value = servo_7.getAngle ();
      UART_1 << "ServoMoteur 7 Data: " << value << "\n\r";
    }
    else if (receiving.getFunction () == 35)
    {
      value = servo_8.getAngle ();
      UART_1 << "ServoMoteur 8 Data: " << value << "\n\r";
    }
    else if (receiving.getFunction () == 36)
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
    UART_1 << "Error return : " << verification << "\n\r";
    UART_1 << "Binary error sended : [";
    UART_2.write ((u8*) &error, sizeof (error));
    UART_1 << "]";
    UART_2.write ((u8*) "\n\r", 2);
    UART_1 << "Integer error sended : " << error.sendMessage () << "\n\r";
    UART_1 << "Error message structure : || BoardID : " << error.getBoardID () << " || Function : " << error.getFunction () << " || Parity : " << error.getParityFunction () << " || Data : " << error.getData () << " || Parity : " << error.getParityData () << " ||\n\r";
  }
  UART_1 << "=============================================" << "\n\r" << "\n\r";
}