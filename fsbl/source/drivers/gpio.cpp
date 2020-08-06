#include "drivers/gpio.hpp"
#include "drivers/mmio.hpp"

namespace mp1::gpio {

    void configure(Bank bank, u8 pin, Mode mode, Type type, Speed speed, PullResistor pullResistor) noexcept {
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::MODER), static_cast<reg_t>(mode) << (pin * 2), 0b11 << (pin * 2));
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::OTYPER), static_cast<reg_t>(type) << pin, 0b1 << pin);
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::OSPEEDR), static_cast<reg_t>(speed) << (pin * 2), 0b11 << (pin * 2));
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::PUPDR), static_cast<reg_t>(pullResistor) << (pin * 2), 0b11 << (pin * 2));
    }

    void set(Bank bank, u8 pin, Status status) noexcept {
        if (status == Status::Enabled)
            mmio::write<reg_t>(mmio::toAddress(bank, Register::BSRR), 0b1 << pin);
        else
            mmio::write<reg_t>(mmio::toAddress(bank, Register::BSRR), 0b1 << (pin + 16));
    }

    Status get(Bank bank, u8 pin) noexcept {
        return mmio::read<reg_t>(mmio::toAddress(bank, Register::IDR)) & (0b1 << pin) > 0 ? Status::Enabled : Status::Disabled;
    }

}