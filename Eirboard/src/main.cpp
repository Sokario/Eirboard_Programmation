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

#include <hal/gpio.hpp>
#include <hal/timer.hpp>
#include <hal/pwm.hpp>

#include <device/hal/encoder.hpp>

#include "include/define.hpp"
#include "include/communication.hpp"

using namespace HAL;

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

// Début du programme
int main(int, char**)
{

  // Initialisation des parammètres des GPIOs
  GPIO::Settings gpio_settings;
  gpio_settings.mode = GPIO::Mode::OUTPUT;
  gpio_settings.output_mode = GPIO::OutputMode::PUSH_PULL;
  gpio_settings.pull = GPIO::Pull::DOWN;

  // Initialisation des GPIOs à l'aide des parammètres
  GPIO::init (LED_1,gpio_settings);
  GPIO::init (LED_2,gpio_settings);
  GPIO::init (LED_3,gpio_settings);

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

    #endif
  }

  return 0;
}
