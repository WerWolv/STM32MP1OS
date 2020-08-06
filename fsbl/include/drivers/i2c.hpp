#pragma once

#include "stm32mp1.hpp"

namespace mp1::i2c {

    enum class Bank : addr_t {
        I2C1 = 0x4001'2000,
        I2C2 = 0x4001'3000,
        I2C3 = 0x4001'4000,
        I2C4 = 0x5C00'2000,
        I2C5 = 0x4001'5000,
        I2C6 = 0x5C00'9000
    };

    enum class Register : offset_t {
        CR1         = 0x000,
        CR2         = 0x004,
        OAR1        = 0x008,
        OAR2        = 0x00C,
        TIMINGR     = 0x010,
        TIMEOUTR    = 0x014,
        ISR         = 0x018,
        ICR         = 0x01C,
        PECR        = 0x020,
        RXDR        = 0x024,
        TXDR        = 0x028,
        HWCFGR      = 0x3F0,
        VERR        = 0x3F4,
        IPIDR       = 0x3F8,
        SIDR        = 0x3FC,
    };

    void enableInterface(Bank bank);
    void disableInterface(Bank bank);

    void transmit(Bank bank, size_t numBytes, u8 *data);
    void receive(Bank bank, size_t numBytes, u8 *data);

}