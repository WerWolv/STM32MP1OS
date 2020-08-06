#pragma once

#include "types.hpp"

namespace mp1 {

    /* Frequency [Hz] */

    using freq_t = u64;

    constexpr freq_t operator ""_Hz(unsigned long long value) {
        return value;
    }

    constexpr freq_t operator ""_kHz(unsigned long long value) {
        return value * 1000ULL;
    }

    constexpr freq_t operator ""_kHz(long double value) {
        return static_cast<freq_t>(value * 1000ULL);
    }

    constexpr freq_t operator ""_MHz(unsigned long long value) {
        return value * 1000'0000ULL;
    }

    constexpr freq_t operator ""_MHz(long double value) {
        return static_cast<freq_t>(value * 1000'0000ULL);
    }

    


    /* Voltage [V] */

    using volt_t = u64;

    constexpr volt_t operator ""_mV(unsigned long long value) {
        return value;
    }

    constexpr volt_t operator ""_V(unsigned long long value) {
        return value * 1000ULL;
    }

    constexpr volt_t operator ""_V(long double value) {
        return static_cast<volt_t>(value * 1000ULL);
    }

}