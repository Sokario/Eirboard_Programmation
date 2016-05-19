/*****************************************************/
/*                Nucleo Architecture                */
/*                    STM32F429ZI                    */
/*                                                   */
/*****************************************************/

/*****************************************************/
/*                 Valeur Remarquable                */
/*                    STM32F429ZI                    */
/*                                                   */
/*             "&&&'" => 2 28 1 201491 0             */
/*             "***'" => 2 28 1 333077 0             */
/*             ";;;'" => 2 28 1 892317 0             */
/*             ",,,'" => 2 28 1 398870 0             */
/*             ">>>'" => 2 28 1 991007 0             */
/*             "111'" => 2 28 1 563352 0             */
/*                                                   */
/*****************************************************/

/*#include <hal/gpio.hpp>
#include <hal/timer.hpp>
#include <hal/pwm.hpp>

#include <device/hal/encoder.hpp>

#include "include/define.hpp"
#include "include/communication.hpp"
#include "include/global.hpp"

using namespace HAL;*/

/*// Encodeurs
struct LeftEncoderSettings : public Device::HAL::DefaultEncoderSettings {
  static constexpr auto& timer = TIMER3; // C'est à vous de configurer
  static constexpr auto& channel1 = C6;  // C'est à vous de configurer
  static constexpr auto& channel2 = C7;  // C'est à vous de configurer

  static constexpr auto channel1_polarity = HAL::ENCODER::Polarity::RISING; // Important
  static constexpr auto channel2_polarity = HAL::ENCODER::Polarity::RISING; // Important
};

struct RightEncoderSettings : public Device::HAL::DefaultEncoderSettings {
  static constexpr auto& timer = TIMER1; // C'est à vous de configurer
  static constexpr auto& channel1 = C6;  // C'est à vous de configurer
  static constexpr auto& channel2 = C7;  // C'est à vous de configurer

  static constexpr auto channel1_polarity = HAL::ENCODER::Polarity::RISING; // Important
  static constexpr auto channel2_polarity = HAL::ENCODER::Polarity::RISING; // Important
};

Device::HAL::Encoder<LeftEncoderSettings> encoder_left;
Device::HAL::Encoder<RightEncoderSettings> encoder_right;*/

#include <hal/gpio.hpp>
#include <hal/timer.hpp>
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
Stream::HAL::UARTStream<MySettings> COM_2;
// Nom du format Stream de l'UART "charactère"
Stream::FormattedStreamDecorator<decltype(COM_2)> COM_1(COM_2);

// Début du programme
int main(int, char**)
{
  // char lol;
  // Initialisation des parammètres des GPIOs
  GPIO::Settings gpio_settings;
  gpio_settings.mode = GPIO::Mode::OUTPUT;
  gpio_settings.output_mode = GPIO::OutputMode::PUSH_PULL;
  gpio_settings.pull = GPIO::Pull::DOWN;

  // Initialisation des GPIOs à l'aide des parammètres
  GPIO::init (LED_1,gpio_settings);
  GPIO::init (LED_2,gpio_settings);
  GPIO::init (LED_3,gpio_settings);
  // GPIO::init (LED_8,gpio_settings);

  TIMER::Settings timer_settings;
  timer_settings.period = 100000;
  TIMER::init(TIMER2,timer_settings);
  TIMER::start(TIMER2);

  static char on = '0';
  TIMER::setOverflowHandler(TIMER2,[](){
    if (on == '1')
      GPIO::toggle (LED_2);
  });

  while(1)
  {
    #ifdef ASSERV
      // UART_1 << "left: " << encoder_left.getValue() << "\n\r";
    #endif

    #ifdef COMM
      GPIO::toggle (LED_1);
      GPIO::toggle (LED_3);
      comm_rasp(&on);
      GPIO::toggle (LED_1);
      GPIO::toggle (LED_3);
   
    // COM_1 << "GP2_1 Data: " << gp2_1.getDetection () << "\n\r";
   
      // COM_1 << "GP2 value: " << gp2_1.getDetection() << "\n\r";

      // COM_2.read ((u8*) &lol, sizeof (lol));
      // COM_1 << "[";
      // COM_2.write ((u8*) &lol, sizeof (lol));
      // COM_1 << "]" << "\r\n";

      // const int ID = 1;
      // constexpr int servo_t[2] = {10, 11};
      // HAL::STM32CubeF4::Private::TIMER_Type<servo_t[ID-1]> timer;
      // TIMER::Settings timer_settings;  
      // timer_settings.period = SERVO_PERIOD; //us

      // PWM::Settings pwm_settings;
      // pwm_settings.polarity = PWM::Polarity::HIGH;
      
      // TIMER::init(timer , timer_settings);
      // PWM::init(SERVO_PWM_1, F6, pwm_settings);
      // TIMER::start(SERVO_TIMER_1);
      // PWM::setPulseWidth(SERVO_PWM_1, 40000);

      // servo_1.setAngle (40000);

      // TIMER::Settings timer_settings;  
      // timer_settings.period = SERVO_PERIOD; //us

      // // Initialisation des parammètres des PWMs 
      // PWM::Settings pwm_settings;
      // pwm_settings.polarity = PWM::Polarity::HIGH;

      // TIMER::init(SERVO_TIMER_1, timer_settings);
      // PWM::init(SERVO_PWM_1, F6, pwm_settings);
      // TIMER::start(SERVO_TIMER_1);
      // PWM::setPulseWidth(SERVO_PWM_1, 40000);

      // Servo servo_test (1);
      // servo_test.setAngle (40000);

    #endif
  }

  return 0;
}
