#pragma once

#include "stm32mp1.hpp"

namespace mp1::ddr {

    enum class Bank : addr_t {
        DDRPERFM    = 0x5A00'7000,
        DDRCTRL     = 0x5A00'3000
    };

    enum class Register : offset_t {
        MSTR = 0x000
    };


    enum class Type : u8 {
        Invalid,
        DDR3,
        LPDDR2,
        LPDDR3
    };

    Type getConnectedType();

}