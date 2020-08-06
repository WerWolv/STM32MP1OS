#pragma once

#include "stm32mp1.hpp"

namespace mp1::gpio {

    enum class Bank : addr_t {
        GPIOA = 0x5000'2000,
        GPIOB = 0x5000'3000,
        GPIOC = 0x5000'4000,
        GPIOD = 0x5000'5000,
        GPIOE = 0x5000'6000,
        GPIOF = 0x5000'7000,
        GPIOG = 0x5000'8000,
        GPIOH = 0x5000'9000,
        GPIOI = 0x5000'A000,
        GPIOJ = 0x5000'B000,
        GPIOK = 0x5000'C000,
        GPIOZ = 0x5400'4000
    };

    enum class Register : offset_t {
        MODER  = 0x00,
        OTYPER  = 0x04,
        OSPEEDR = 0x08,
        PUPDR  = 0x0C,
        IDR = 0x10,
        ODR = 0x14,
        BSRR  = 0x18,
        LCKR = 0x1C,
        AFRL  = 0x20,
        AFRH  = 0x24,
        BRR = 0x28,
        SECCFGR  = 0x30
    };

    enum class Mode : u8 {
        Input       = 0x00,
        Output      = 0x01,
        Alternate   = 0x02,
        Analog      = 0x03,
    };

    enum class Type : u8 {
        PushPull = 0x00,
        OpenDrain = 0x01
    };

    enum class Speed : u8 {
        Low         = 0x00,
        Medium      = 0x01,
        High        = 0x02,
        VeryHigh    = 0x03
    };

    enum class PullResistor : u8 {
        None        = 0x00,
        PullUp      = 0x01,
        PullDown    = 0x02
    };

    enum class Status : u8 {
        Disabled = 0,
        Enabled  = 1
    };

    void configure(Bank bank, u8 pin, Mode mode, Type type, Speed speed = Speed::Medium, PullResistor pullResistor = PullResistor::None) noexcept;
    void set(Bank bank, u8 pin, Status status) noexcept;
    Status get(Bank bank, u8 pin) noexcept;

}