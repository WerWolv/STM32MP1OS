#pragma once

#include "stm32mp1.hpp"

#include "drivers/clk.hpp"
#include "drivers/gpio.hpp"
#include "drivers/i2c.hpp"
#include "drivers/mmio.hpp"

namespace mp1::dk2 {

    /* GPIO Peripherals */

    constexpr static inline auto YellowLedPortClock = mp1::clk::AHB4Peripheral::GPIOH;
    constexpr static inline auto BlueLedPortClock = mp1::clk::AHB4Peripheral::GPIOD;

    constexpr static inline auto YellowLedPort = mp1::gpio::Bank::GPIOH;
    constexpr static inline auto BlueLedPort = mp1::gpio::Bank::GPIOD;

    constexpr static inline auto YellowLedPin = u8(7);
    constexpr static inline auto BlueLedPin = u8(11);


    /* I2C Peripherals */

    constexpr static inline auto PMICInterface = mp1::i2c::Bank::I2C4;

}