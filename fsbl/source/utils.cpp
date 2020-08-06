#include "utils.hpp"

#include "board_dk2.hpp"

#include "drivers/clk.hpp"
#include "drivers/gpio.hpp"

namespace mp1::utl {

    [[noreturn]] void panic() {

        // Enable clock for GPIOD  
        {
            using namespace mp1::clk;
            mp1::clk::enablePeripheralClock(dk2::YellowLedPortClock);
        }

        // Initiaize and enable orange panic LED 
        {
            using namespace mp1::gpio;

            mp1::gpio::configure(dk2::YellowLedPort, dk2::YellowLedPin, Mode::Output, Type::PushPull);
            mp1::gpio::set(dk2::YellowLedPort, dk2::YellowLedPin, Status::Enabled);
        }

        
        while (true);
    }

}