#pragma once

#include "stm32mp1.hpp"
#include <cstring>
#include <concepts>

namespace mp1::utl {

    template<std::unsigned_integral T>
    consteval T encodeMagic(const char* magic) {
        /*if (!(std::strlen(magic) <= 8 && std::strlen(magic) <= sizeof(T)))
            throw "Magic too long!";*/

        T encoded = 0;

        for (offset_t offset = 0; offset < std::strlen(magic); offset++)
            encoded |= (*(magic + offset)) << (offset * 8);

        return encoded;
    }

    [[noreturn]] void panic();

}