/*****************************************************/
/*                 GP2 Architecture                  */
/*                    STM32F429ZI                    */
/*                                                   */
/*****************************************************/

#include <stm32f4xx_hal.h>

#include "include/define.hpp"
#include "include/global.hpp"
#include "include/gp2.hpp"

ADC_HandleTypeDef handler_ADC_1;
// ADC_HandleTypeDef handler_ADC_2;
ADC_HandleTypeDef handler_ADC_3;

GP2::GP2() : m_id (0), m_limitValue (0)
{
    handler_ADC_1.Instance = ADC1;
    handler_ADC_1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
    handler_ADC_1.Init.Resolution = ADC_RESOLUTION_12B;
    handler_ADC_1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    handler_ADC_1.Init.ScanConvMode = DISABLE;
    handler_ADC_1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    handler_ADC_1.Init.ContinuousConvMode = DISABLE;
    handler_ADC_1.Init.DMAContinuousRequests = DISABLE;
    handler_ADC_1.Init.NbrOfConversion = 1;
    handler_ADC_1.Init.DiscontinuousConvMode = DISABLE;
    handler_ADC_1.Init.NbrOfDiscConversion = 1;
    handler_ADC_1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    handler_ADC_1.Init.ExternalTrigConvEdge = ADC_SOFTWARE_START;

/*
    handler_ADC_2.Instance = ADC2;
    handler_ADC_2.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
    handler_ADC_2.Init.Resolution = ADC_RESOLUTION_12B;
    handler_ADC_2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    handler_ADC_2.Init.ScanConvMode = DISABLE;
    handler_ADC_2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    handler_ADC_2.Init.ContinuousConvMode = DISABLE;
    handler_ADC_2.Init.DMAContinuousRequests = DISABLE;
    handler_ADC_2.Init.NbrOfConversion = 1;
    handler_ADC_2.Init.DiscontinuousConvMode = DISABLE;
    handler_ADC_2.Init.NbrOfDiscConversion = 1;
    handler_ADC_2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    handler_ADC_2.Init.ExternalTrigConvEdge = ADC_SOFTWARE_START;
*/

    handler_ADC_3.Instance = ADC3;
    handler_ADC_3.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
    handler_ADC_3.Init.Resolution = ADC_RESOLUTION_12B;
    handler_ADC_3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    handler_ADC_3.Init.ScanConvMode = DISABLE;
    handler_ADC_3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    handler_ADC_3.Init.ContinuousConvMode = DISABLE;
    handler_ADC_3.Init.DMAContinuousRequests = DISABLE;
    handler_ADC_3.Init.NbrOfConversion = 1;
    handler_ADC_3.Init.DiscontinuousConvMode = DISABLE;
    handler_ADC_3.Init.NbrOfDiscConversion = 1;
    handler_ADC_3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    handler_ADC_3.Init.ExternalTrigConvEdge = ADC_SOFTWARE_START;
}

GP2::GP2(const int id, u32 limitValue) : m_id (0), m_limitValue (0)
{
        setID(id);
        setLimitValue(limitValue);

        handler_ADC_1.Instance = ADC1;
        handler_ADC_1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
        handler_ADC_1.Init.Resolution = ADC_RESOLUTION_12B;
        handler_ADC_1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
        handler_ADC_1.Init.ScanConvMode = DISABLE;
        handler_ADC_1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
        handler_ADC_1.Init.ContinuousConvMode = DISABLE;
        handler_ADC_1.Init.DMAContinuousRequests = DISABLE;
        handler_ADC_1.Init.NbrOfConversion = 1;
        handler_ADC_1.Init.DiscontinuousConvMode = DISABLE;
        handler_ADC_1.Init.NbrOfDiscConversion = 1;
        handler_ADC_1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
        handler_ADC_1.Init.ExternalTrigConvEdge = ADC_SOFTWARE_START;

/*
        handler_ADC_2.Instance = ADC2;
        handler_ADC_2.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
        handler_ADC_2.Init.Resolution = ADC_RESOLUTION_12B;
        handler_ADC_2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
        handler_ADC_2.Init.ScanConvMode = DISABLE;
        handler_ADC_2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
        handler_ADC_2.Init.ContinuousConvMode = DISABLE;
        handler_ADC_2.Init.DMAContinuousRequests = DISABLE;
        handler_ADC_2.Init.NbrOfConversion = 1;
        handler_ADC_2.Init.DiscontinuousConvMode = DISABLE;
        handler_ADC_2.Init.NbrOfDiscConversion = 1;
        handler_ADC_2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
        handler_ADC_2.Init.ExternalTrigConvEdge = ADC_SOFTWARE_START;
*/

        handler_ADC_3.Instance = ADC3;
        handler_ADC_3.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
        handler_ADC_3.Init.Resolution = ADC_RESOLUTION_12B;
        handler_ADC_3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
        handler_ADC_3.Init.ScanConvMode = DISABLE;
        handler_ADC_3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
        handler_ADC_3.Init.ContinuousConvMode = DISABLE;
        handler_ADC_3.Init.DMAContinuousRequests = DISABLE;
        handler_ADC_3.Init.NbrOfConversion = 1;
        handler_ADC_3.Init.DiscontinuousConvMode = DISABLE;
        handler_ADC_3.Init.NbrOfDiscConversion = 1;
        handler_ADC_3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
        handler_ADC_3.Init.ExternalTrigConvEdge = ADC_SOFTWARE_START;
}

bool GP2::setID(const int id)
{
    if (id > GP2_NUMBER)
        return false;
    else
    {
        GPIO_InitTypeDef gpio_init;
        gpio_init.Pin = GPIO_PIN_0;
        gpio_init.Pull = GPIO_PULLDOWN;
        gpio_init.Mode = GPIO_MODE_ANALOG;

        if (id == 1)
        {
            __GPIOF_CLK_ENABLE(); // F3
            gpio_init.Pin = GPIO_PIN_3;
            HAL_GPIO_Init(GPIOF, &gpio_init);
            __ADC3_CLK_ENABLE();
            HAL_ADC_Init(&handler_ADC_3);
        }
        else if (id == 2)
        {
            __GPIOF_CLK_ENABLE(); // F4
            gpio_init.Pin = GPIO_PIN_4;
            HAL_GPIO_Init(GPIOF, &gpio_init);
            __ADC3_CLK_ENABLE();
            HAL_ADC_Init(&handler_ADC_3);
        }
        else if (id == 3)
        {
            __GPIOF_CLK_ENABLE(); // F5
            gpio_init.Pin = GPIO_PIN_5;
            HAL_GPIO_Init(GPIOF, &gpio_init);
            __ADC3_CLK_ENABLE();
            HAL_ADC_Init(&handler_ADC_3);
        }
        else if (id == 4)
        {
            __GPIOF_CLK_ENABLE(); // F10
            gpio_init.Pin = GPIO_PIN_10;
            HAL_GPIO_Init(GPIOF, &gpio_init);
            __ADC3_CLK_ENABLE();
            HAL_ADC_Init(&handler_ADC_3);
        }
        else if (id == 5)
        {
            #ifdef EIRBOARD
            __GPIOC_CLK_ENABLE(); // C4
            gpio_init.Pin = GPIO_PIN_4;
            HAL_GPIO_Init(GPIOC, &gpio_init);
            #endif
            #ifdef NUCLEO
            __GPIOA_CLK_ENABLE(); // A6
            gpio_init.Pin = GPIO_PIN_6;
            HAL_GPIO_Init(GPIOA, &gpio_init);
            #endif

            __ADC1_CLK_ENABLE();
            HAL_ADC_Init(&handler_ADC_1);
        }
        else if (id == 6)
        {
            #ifdef EIRBOARD
            __GPIOC_CLK_ENABLE(); // A7
            gpio_init.Pin = GPIO_PIN_5;
            HAL_GPIO_Init(GPIOC, &gpio_init);
            #endif
            #ifdef NUCLEO
            __GPIOA_CLK_ENABLE(); // A7
            gpio_init.Pin = GPIO_PIN_7;
            HAL_GPIO_Init(GPIOA, &gpio_init);
            #endif

            __ADC1_CLK_ENABLE();
            HAL_ADC_Init(&handler_ADC_1);
        }
        else if (id == 7)
        {
            __GPIOB_CLK_ENABLE(); // B0
            gpio_init.Pin = GPIO_PIN_0;
            HAL_GPIO_Init(GPIOB, &gpio_init);
            __ADC1_CLK_ENABLE();
            HAL_ADC_Init(&handler_ADC_1);
        }
        else if (id == 8)
        {
            __GPIOB_CLK_ENABLE(); // B1
            gpio_init.Pin = GPIO_PIN_1;
            HAL_GPIO_Init(GPIOB, &gpio_init);
            __ADC1_CLK_ENABLE();
            HAL_ADC_Init(&handler_ADC_1);
        }

        m_id = id;
        return true;
    }
}

u32 GP2::getID() const
{
        return m_id;
}

bool GP2::setLimitValue(u32 limitValue)
{
        if (limitValue <= GP2_LIMIT)
            return false;
        else
        {
            m_limitValue = limitValue;
            return true;
        }
}

u32 GP2::getLimitValue() const
{
    return m_limitValue;
}

u32 GP2::getDetection() const
{
    u32 value = 0;
    ADC_ChannelConfTypeDef conf;

    conf.Rank = 1;
    conf.SamplingTime = ADC_SAMPLETIME_56CYCLES;
    conf.Offset = 0;
    
    if (m_id == 1)
        {
            conf.Channel = ADC_CHANNEL_9;
            HAL_ADC_ConfigChannel(&handler_ADC_3, &conf);
            HAL_ADC_Start(&handler_ADC_3);
            HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&handler_ADC_3, 1000);
            value = HAL_ADC_GetValue(&handler_ADC_3);
        }
        else if (m_id == 2)
        {
            conf.Channel = ADC_CHANNEL_14;
            HAL_ADC_ConfigChannel(&handler_ADC_3, &conf);
            HAL_ADC_Start(&handler_ADC_3);
            HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&handler_ADC_3, 1000);
            value = HAL_ADC_GetValue(&handler_ADC_3);
        }
        else if (m_id == 3)
        {
            conf.Channel = ADC_CHANNEL_15;
            HAL_ADC_ConfigChannel(&handler_ADC_3, &conf);
            HAL_ADC_Start(&handler_ADC_3);
            HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&handler_ADC_3, 1000);
            value = HAL_ADC_GetValue(&handler_ADC_3);
        }
        else if (m_id == 4)
        {
            conf.Channel = ADC_CHANNEL_8;
            HAL_ADC_ConfigChannel(&handler_ADC_3, &conf);
            HAL_ADC_Start(&handler_ADC_3);
            HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&handler_ADC_3, 1000);
            value = HAL_ADC_GetValue(&handler_ADC_3);
        }
        else if (m_id == 5)
        {
            conf.Channel = ADC_CHANNEL_14;
            HAL_ADC_ConfigChannel(&handler_ADC_1, &conf);
            HAL_ADC_Start(&handler_ADC_1);
            HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&handler_ADC_1, 1000);
            value = HAL_ADC_GetValue(&handler_ADC_1);
        }
        else if (m_id == 6)
        {
            conf.Channel = ADC_CHANNEL_15;
            HAL_ADC_ConfigChannel(&handler_ADC_1, &conf);
            HAL_ADC_Start(&handler_ADC_1);
            HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&handler_ADC_1, 1000);
            value = HAL_ADC_GetValue(&handler_ADC_1);
        }
        else if (m_id == 7)
        {
            conf.Channel = ADC_CHANNEL_8;
            HAL_ADC_ConfigChannel(&handler_ADC_1, &conf);
            HAL_ADC_Start(&handler_ADC_1);
            HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&handler_ADC_1, 1000);
            value = HAL_ADC_GetValue(&handler_ADC_1);
        }
        else if (m_id == 8)
        {
            conf.Channel = ADC_CHANNEL_9;
            HAL_ADC_ConfigChannel(&handler_ADC_1, &conf);
            HAL_ADC_Start(&handler_ADC_1);
            HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&handler_ADC_1, 1000);
            value = HAL_ADC_GetValue(&handler_ADC_1);
        }

    return value;
}

bool GP2::detection() const
{
    return getDetection() > m_limitValue;
}

GP2::~GP2()
{}
