#include "drivers/clk.hpp"

#include "drivers/mmio.hpp"
#include "utils.hpp"

namespace mp1::clk {

    void enableOscillator(Oscillator oscillator, bool force) {
        if (!force) {
            switch (oscillator) {
                case Oscillator::HSI:
                    mmio::modify(mmio::toAddress(Bank::RCC, Register::OCENSETR), mmio::bit(0), mmio::NoChange);
                    break;
                case Oscillator::CSI:
                    mmio::modify(mmio::toAddress(Bank::RCC, Register::OCENSETR), mmio::bit(4), mmio::NoChange);
                    break;
                case Oscillator::HSE:
                    mmio::modify(mmio::toAddress(Bank::RCC, Register::OCENSETR), mmio::bit(8), mmio::NoChange);
                    break;
                default: utl::panic();
            }
        } else {
            switch (oscillator) {
                case Oscillator::HSI:
                    mmio::modify(mmio::toAddress(Bank::RCC, Register::OCENSETR), mmio::bit(1), mmio::NoChange);
                    break;
                case Oscillator::CSI:
                    mmio::modify(mmio::toAddress(Bank::RCC, Register::OCENSETR), mmio::bit(5), mmio::NoChange);
                    break;
                case Oscillator::HSE:
                    mmio::modify(mmio::toAddress(Bank::RCC, Register::OCENSETR), mmio::bit(9), mmio::NoChange);
                    break;
                default: utl::panic();
            }
        }
    }

    void disableOscillator(Oscillator oscillator) {
        switch (oscillator) {
            case Oscillator::HSI:
                mmio::modify(mmio::toAddress(Bank::RCC, Register::OCENCLRR), mmio::bit(0), mmio::NoChange);
                break;
            case Oscillator::CSI:
                mmio::modify(mmio::toAddress(Bank::RCC, Register::OCENCLRR), mmio::bit(4), mmio::NoChange);
                break;
            case Oscillator::HSE:
                mmio::modify(mmio::toAddress(Bank::RCC, Register::OCENCLRR), mmio::bit(8), mmio::NoChange);
                break;
            default: utl::panic();
        }
    } 

    void setPLLSource(PLL pll, Oscillator source) {
        switch (pll) {
            case PLL::PLL1:
            case PLL::PLL2:
                switch (source) {
                    case Oscillator::HSI:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK12SELR), mmio::NoChange, mmio::bit(0) | mmio::bit(1));
                        break;
                    case Oscillator::HSE:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK12SELR), mmio::bit(0), mmio::bit(0) | mmio::bit(1));
                        break;
                    case Oscillator::None:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK12SELR), mmio::bit(1), mmio::bit(0) | mmio::bit(1));
                    default: utl::panic();
                }
                break;
            case PLL::PLL3:
                switch (source) {
                    case Oscillator::HSI:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK3SELR), 0x00U, mmio::bit(0) | mmio::bit(1));
                        break;
                    case Oscillator::HSE:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK3SELR), 0x01U, mmio::bit(0) | mmio::bit(1));
                        break;
                    case Oscillator::CSI:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK3SELR), 0x02U, mmio::bit(0) | mmio::bit(1));
                        break;
                    case Oscillator::None:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK3SELR), 0x03U, mmio::bit(0) | mmio::bit(1));
                        break;
                    default: utl::panic();
                }
                break;
            case PLL::PLL4:
                switch (source) {
                    case Oscillator::HSI:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK4SELR), 0x00U, mmio::bit(0) | mmio::bit(1));
                        break;
                    case Oscillator::HSE:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK4SELR), 0x01U, mmio::bit(0) | mmio::bit(1));
                        break;
                    case Oscillator::CSI:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK4SELR), 0x02U, mmio::bit(0) | mmio::bit(1));
                        break;
                    /*
                    case Oscillator::I2C_CKIN:
                        mmio::modify(mmio::toAddress(Bank::RCC, Register::RCK4SELR), 0x03U, mmio::bit(0) | mmio::bit(1));
                        break;
                    */
                    default: utl::panic();
                }
                break;

        }
    }

    void enablePeripheralClock(AHB4Peripheral peripheral) {
        addr_t registerAddress = mmio::toAddress(Bank::RCC, Register::MP_AHB4ENSETR);

        mmio::modify(registerAddress, mmio::bit(static_cast<reg_t>(peripheral)), mmio::NoChange);
    }

    void enablePeripheralClock(APB1Peripheral peripheral) {
        addr_t registerAddress = mmio::toAddress(Bank::RCC, Register::MP_APB1ENSETR);

        mmio::modify(registerAddress, mmio::bit(static_cast<reg_t>(peripheral)), mmio::NoChange);
    }

    void enablePeripheralClock(APB5Peripheral peripheral) {
        addr_t registerAddress = mmio::toAddress(Bank::RCC, Register::MP_APB5ENSETR);

        mmio::modify(registerAddress, mmio::bit(static_cast<reg_t>(peripheral)), mmio::NoChange);
    }

}