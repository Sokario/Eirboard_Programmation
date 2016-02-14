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

// Nom du format Stream de l'UART
Stream::FormattedUARTStream<MySettings> UART_1;
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
  
  // Utilisation des GPIOs: changement d'états
  GPIO::toggle (LED_1);
  GPIO::toggle (LED_2);
  GPIO::toggle (LED_3);

  // Création du message
  Message sending;
  sending.createMessage ("0011", "00100000", "0011001001010");
  UART_2.write ((u8*) &sending, sizeof (sending));
  UART_2.write ((u8*) "\n\r", 2);
  Message receiving;
  receiving.receiveMessage (s2bin ("00011001011000010000001000000011"));
  UART_2.write ((u8*) &receiving, sizeof (receiving));
  UART_2.write ((u8*) "\n\r", 2);

  while(1)
  {

    // u32 a = s2bin ("1000001");
    // UART_1 << s2bin ("1000001") << " " << bitsCount (a) << " " << bitsParity (a) << "\n\r";
    // UART_1 << "Sending message : " << sending.sendMessage () << " || Verification : " << s2bin ("00011001011000010000001000000011") << "\n\r";
    // UART_1 << "Receiving message : " << receiving.getBoardID () << " = " << s2bin ("0001") << " || " << receiving.getFunction () << " = " << s2bin ("100101") << " || " << receiving.getParityFunction () << " = " << 1 << " || " << receiving.getData () << " = " << s2bin ("00001000000100000001") << " || " << receiving.getParityData () << " = " << 1 << "\n\r";
    // UART_1 << "\n\r";    

    // u32 var = ((u32)'b'<<24) + ((u32)'\r'<<16) + ((u32)'a'<<8) + (u32)'1';
    // UART_2.write((u8*) &var, sizeof (var));
    // UART_2.write((u8*) "\n\r", 2);
    // UART_2.write((u8*) "--------------------", 20);
    // UART_2.write((u8*) "\n\r", 2);
    // u32 var1 = ((u32)'b'<<24) + ((u32)'\r'<<16) + ((u32)'a'<<8) + (u32)'8';
    // UART_2.write((u8*) &var1, sizeof (var1));
    // UART_2.write((u8*) "\n\r", 2);
    // UART_2.write((u8*) "--------------------", 20);
    // UART_2.write((u8*) "\n\r", 2);

    u32 buffer;
    UART_2.read ((u8*) &buffer, sizeof (buffer));
    receiving.receiveMessage (buffer);
    UART_2.write ((u8*) &buffer, sizeof (buffer));
    UART_2.write ((u8*) "\n\r", 2);
    UART_1 << "Receiving message : " << receiving.sendMessage () << " || Verification : " << buffer << "\n\r";
    if (receiving.isGood () != 0)
    {
      UART_1 << "Error message : " << receiving.isGood () << "\n\r";
    }
    else
      UART_1 << "Receiving message, || BoardID : " << receiving.getBoardID () << " || Function : " << receiving.getFunction () << " || Data : " << receiving.getData () << " ||\n\r";
  }

  return 0;
 
}
