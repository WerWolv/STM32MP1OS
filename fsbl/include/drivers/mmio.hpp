#pragma once

#include "stm32mp1.hpp"
#include <concepts>

namespace mp1::mmio {

    constexpr static inline u32 NoChange = 0x00;

    constexpr u32 bit(u8 bit) {
        return (1U << static_cast<u32>(bit));
    }

    constexpr addr_t toAddress(auto base, auto offset) {
        return static_cast<addr_t>(base) + static_cast<addr_t>(offset);
    }
    
    template<std::unsigned_integral T>
    void write(addr_t addr, T value) {
        *reinterpret_cast<volatile T*>(addr) = value;
    }

    template<std::unsigned_integral T>
    T read(addr_t addr) {
        return *reinterpret_cast<volatile T*>(addr);
    }

    template<std::unsigned_integral T>
    void modify(addr_t addr, T set, T clear) {
        *reinterpret_cast<volatile T*>(addr) = ((read<T>(addr) & ~clear) | set);
    }

}