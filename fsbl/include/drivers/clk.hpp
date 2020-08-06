#pragma once

#include "stm32mp1.hpp"

namespace mp1::clk {

    constexpr freq_t HSIOscillatorFrequency = 64_MHz;
    constexpr freq_t HSEOscillatorFrequency = 24_MHz;
    constexpr freq_t CSIOscillatorFrequency = 4_MHz;
    constexpr freq_t LSIOscillatorFrequency = 32_kHz;
    constexpr freq_t LSEOscillatorFrequency = 32.768_kHz;

    enum class Bank : addr_t {
        RCC = 0x5000'0000
    };

    enum class Register : offset_t {
        TZCR = 0x000,
        OCENSETR = 0x00C,
        OCENCLRR = 0x010,
        HSICFGR = 0x018,
        CSICFGR = 0x01C,
        MPCKSELR = 0x020,
        ASSCKSELR = 0x024,
        RCK12SELR = 0x028,
        MSSCKSELR = 0x048,

        I2C46CKSELR = 0x0C0,

        GRSTCSETR = 0x404,

        MP_APB1ENSETR = 0xA00,
        MP_APB1ENCLRR = 0xA04,
        MP_APB2ENSETR = 0xA08,
        MP_APB2ENCLRR = 0xA0C,
        MP_APB3ENSETR = 0xA10,
        MP_APB3ENCLRR = 0xA14,
        MP_APB4ENSETR = 0x200,
        MP_APB4ENCLRR = 0x204,
        MP_APB5ENSETR = 0x208,
        MP_APB5ENCLRR = 0x20C,
        MP_AHB2ENSETR = 0xA18,
        MP_AHB2ENCLRR = 0xA1C,
        MP_AHB3ENSETR = 0xA20,
        MP_AHB3ENCLRR = 0xA24,
        MP_AHB4ENSETR = 0xA28,
        MP_AHB4ENCLRR = 0xA2C,
        MP_AHB5ENSETR = 0x210,
        MP_AHB5ENCLRR = 0x214,
        MP_AHB6ENSETR = 0x218,
        MP_AHB6ENCLRR = 0x21C,
        MP_TZAHB6ENSETR = 0x220,
        MP_TZAHB6ENCLRR = 0x224,

        MC_APB1ENSETR = 0xA80,
        MC_APB1ENCLRR = 0xA84,
        MC_APB2ENSETR = 0xA88,
        MC_APB2ENCLRR = 0xA8C,
        MC_APB3ENSETR = 0xA90,
        MC_APB3ENCLRR = 0xA94,
        MC_APB4ENSETR = 0x280,
        MC_APB4ENCLRR = 0x284,
        MC_APB5ENSETR = 0x288,
        MC_APB5ENCLRR = 0x28C,
        MC_AHB2ENSETR = 0xA98,
        MC_AHB2ENCLRR = 0xA9C,
        MC_AHB3ENSETR = 0xAA0,
        MC_AHB3ENCLRR = 0xAA4,
        MC_AHB4ENSETR = 0xAA8,
        MC_AHB4ENCLRR = 0xAAC,
        MC_AHB5ENSETR = 0x290,
        MC_AHB5ENCLRR = 0x294,
        MC_AHB6ENSETR = 0x298,
        MC_AHB6ENCLRR = 0x29C,


        MCO1CFGR = 0x800,
        MCO2CFGR = 0x804,
        OCRDYR = 0x808,
        DBGCFGR = 0x80C,
        RCK3SELR = 0x820,
        RCK4SELR = 0x824,
    };

    enum class Oscillator : u8 {
        None,
        HSI,
        HSE,
        CSI,
        LSI,
        LSE
    };

    enum class PLL : u8 {
        PLL1,   // 800 - 1600 MHz
        PLL2,   // 800 - 1600 MHz
        PLL3,   // 400 - 800 MHz
        PLL4    // 400 - 800 MHz
    };

    enum class ClockDomain : u8 {
        AHB2,
        AHB3,
        AHB4,
        AHB5,
        AHB6,

        APB1,
        APB2,
        APB3,
        APB4,
        APB5,
    };

    enum class AHB4Peripheral : u8 {
        GPIOA   = 0,
        GPIOB   = 1,
        GPIOC   = 2,
        GPIOD   = 3,
        GPIOE   = 4,
        GPIOF   = 5,
        GPIOG   = 6,
        GPIOH   = 7,
        GPIOI   = 8,
        GPIOJ   = 9,
        GPIOK   = 10
    };

    enum class APB1Peripheral : u8 {
        TIM2    = 0,
        TIM3    = 1,
        TIM4    = 2,
        TIM5    = 3,
        TIM6    = 4,
        TIM7    = 5,
        TIM12   = 6,
        TIM13   = 7,
        TIM14   = 8,
        LPTIM1  = 9,
        SPI2    = 11,
        SPI3    = 12,
        USART2  = 14,
        USART3  = 15,
        UART4   = 16,
        UART5   = 17,
        UART7   = 18,
        UART8   = 19,
        I2C1    = 21,
        I2C2    = 22,
        I2C3    = 23,
        I2C5    = 24,
        SPDIF   = 26,
        CEC     = 27,
        DAC12   = 29,
        MDIOS   = 31
    };

    enum class APB5Peripheral : u8 {
        SPI6        = 0,
        I2C4        = 2,
        I2C6        = 3,
        USART1      = 4,
        RTCAPB      = 8,
        TZC1        = 11,
        TZC2        = 12,
        TCPC        = 13,
        IWDG1APB    = 15,
        BSEC        = 16,
        STGEN       = 20
    };

    void enableOscillator(Oscillator oscillator, bool force = false);
    void disableOscillator(Oscillator oscillator);   

    void setPLLSource(PLL pll, Oscillator source); 

    void enablePeripheralClock(AHB4Peripheral peripheral);
    void enablePeripheralClock(APB1Peripheral peripheral);
    void enablePeripheralClock(APB5Peripheral peripheral);

}