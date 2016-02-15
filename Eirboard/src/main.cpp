/*****************************************************/
/*                Nucleo Architecture                */
/*                    STM32F429ZI                    */
/*                                                   */
/*****************************************************/

#include <hal/gpio.hpp>
#include <hal/timer.hpp>
#include <hal/pwm.hpp>
#include <hal/uart.hpp>

#include "include/calcul.hpp"
#include "include/message.hpp"

#define LED_1 B0
#define LED_2 B7
#define LED_3 B14

using namespace HAL;

// Gestion De l'objet UART/USART
#include <stream/hal/uart_stream.hpp>

using namespace Stream;

struct MySettings : public DefaultUARTStreamSettings {
    static constexpr auto& uart = SERIAL_USART3;
    static constexpr auto& tx = D8;
    static constexpr auto& rx = D9;

    static constexpr auto baudrate = 9600;
    static constexpr auto parity = UART::Parity::NONE;
    static constexpr auto stop_bit = UART::StopBit::ONE_BIT;
    static constexpr auto word_size = 8;
};

// Nom du format Stream de l'UART "charactère"
Stream::FormattedUARTStream<MySettings> UART_1;
// Nom du format Stream de l'UART "binaire"
Stream::UARTStream<MySettings> UART_2;


// Début du programme
int main(int, char**)
{

  // Initialisation des parammètres des GPIOs
  GPIO::Settings settings;
  settings.mode = GPIO::Mode::OUTPUT;
  settings.output_mode = GPIO::OutputMode::PUSH_PULL;
  settings.pull = GPIO::Pull::DOWN;

  // Initialisation des GPIOs à l'aide des parammètres
  GPIO::init (LED_1,settings);
  GPIO::init (LED_2,settings);
  GPIO::init (LED_3,settings);
  
  // // Utilisation des GPIOs: changement d'états
  // GPIO::toggle (LED_1);
  // GPIO::toggle (LED_2);
  // GPIO::toggle (LED_3);

  // Message creation
  Message sending;
  sending.createMessage ("0010", "001000", "0011001001010");
  Message receiving;
  receiving.receiveMessage (s2bin ("00011001011000010000001000000011"));
  Message error;
  error.createMessage ("1111", "111111", "11111111111111111111");

  while(1)
  {
    UART_1 << "=============================================" << "\n\r";
    UART_1 << "Board listenning, enter your binary message :" << "\n\r";

    // Board "free"    
    GPIO::toggle (LED_1);
    GPIO::toggle (LED_2);
    GPIO::toggle (LED_3);
    u32 buffer;
    UART_2.read ((u8*) &buffer, sizeof (buffer));
    receiving.receiveMessage (buffer);
    UART_1 << "Binary received : ";
    UART_2.write ((u8*) &buffer, sizeof (buffer));
    UART_2.write ((u8*) "\n\r", 2);
    UART_1 << "---------------------------------------------" << "\n\r";
    UART_1 << "Receiving message structure : || BoardID : " << receiving.getBoardID () << " || Function : " << receiving.getFunction () << " || Parity : " << receiving.getParityFunction () << " || Data : " << receiving.getData () << " || Parity : " << receiving.getParityData () << " ||\n\r";
    
    // Board "locked"
    GPIO::toggle (LED_1);
    GPIO::toggle (LED_2);
    GPIO::toggle (LED_3);
    u32 verification = receiving.isGood ();
    if (verification == 0)
    {
      UART_1 << "The message received is good!" << "\n\r"; // "&&&'"
    }
    else if (verification == 1)
    {
      UART_1 << "Error message occure, resend the previous message!" << "\n\r";
    }
    else
    {
      error.createMessage ("1111", "111111", "11111111111111111111");
      UART_1 << "Error return : " << receiving.isGood () << "\n\r";
      UART_1 << "Binary error sended : ";
      UART_2.write ((u8*) &error, sizeof (error));
      UART_2.write ((u8*) "\n\r", 2);
      UART_1 << "Integer error sended : " << error.sendMessage () << "\n\r";
      UART_1 << "Error message structure : || BoardID : " << error.getBoardID () << " || Function : " << error.getFunction () << " || Parity : " << error.getParityFunction () << " || Data : " << error.getData () << " || Parity : " << error.getParityData () << " ||\n\r";
    }
    UART_1 << "=============================================" << "\n\r" << "\n\r";
  }

  return 0;
}