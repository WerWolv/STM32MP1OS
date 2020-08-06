#include "stm32mp1.hpp"
#include "board_dk2.hpp"

#include "drivers/mmio.hpp"
#include "drivers/clk.hpp"
#include "drivers/gpio.hpp"
#include "drivers/i2c.hpp"
#include "utils.hpp"

int main() {

    // Init clocks
    {
        using namespace mp1::clk;

        mp1::clk::enableOscillator(Oscillator::HSE);  
        mp1::clk::setPLLSource(PLL::PLL1 /* | PLL::PLL2 */, Oscillator::HSE);
        
        
        mp1::clk::enablePeripheralClock(AHB4Peripheral::GPIOD);
        mp1::clk::enablePeripheralClock(AHB4Peripheral::GPIOH);

        mp1::clk::enablePeripheralClock(APB5Peripheral::I2C4);

        // Make I2C4 and I2C6 use HSI as clock source
        mp1::mmio::write<mp1::reg_t>(mp1::mmio::toAddress(mp1::clk::Bank::RCC, mp1::clk::Register::I2C46CKSELR), 0x02);
    }

    // Init GPIOs
    {
        using namespace mp1::gpio;

        mp1::gpio::configure(mp1::dk2::BlueLedPort, mp1::dk2::BlueLedPin, Mode::Output, Type::PushPull);
        mp1::gpio::set(mp1::dk2::BlueLedPort, mp1::dk2::BlueLedPin, Status::Enabled);
    }

    // Init I2C
    {
        using namespace mp1::i2c;

        mp1::i2c::enableInterface(Bank::I2C4);

        mp1::u8 send[] = { 0x33, 0x06 }; // STPMIC1 address 0x33, register 0x06
        mp1::u8 recv = 0;
        mp1::i2c::transmit(Bank::I2C4, 2, send);
        mp1::i2c::receive(Bank::I2C4, 1, &recv);

        if (recv == 0)
            mp1::utl::panic();
    }

    while(true);

    return 0;
}