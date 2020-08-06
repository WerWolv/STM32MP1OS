#include "drivers/i2c.hpp"

#include "drivers/mmio.hpp"
#include "utils.hpp"

namespace mp1::i2c {

    void enableInterface(Bank bank) {
        // Enable Analog noise filter
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::CR1), mmio::bit(12), mmio::NoChange);

        // Configure timing register with following settings: Standard mode, 100kHz, Analog filter
        mmio::write<reg_t>(mmio::toAddress(bank, Register::TIMINGR), 0x1070'7DBC);

        // Set PE (Peripheral Enable) bit in register CR1
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::CR1), mmio::bit(0), mmio::NoChange);
    }

    void disableInterface(Bank bank) {
        // Clear PE (Peripheral Enable) bit in register CR1
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::CR1), mmio::NoChange, mmio::bit(0));
    }

    void transmit(Bank bank, size_t numBytes, u8 *data) {
        if (numBytes > 0xFF) 
            utl::panic();

        // Set NBYTES value
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::CR2), (numBytes & 0xFF) << 16, 0xFF << 16);

        // Enable auto end mode
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::CR2), mmio::bit(25), mmio::NoChange);

        // Transmit N bytes
        for (u16 i = 0; i < numBytes; i++) {
            // Wait till transmission is complete
            do {
                // Bail out if a NACK was received
                if (mmio::read<reg_t>(mmio::toAddress(bank, Register::ISR)) & mmio::bit(4) != 0)
                    return;
            }
            while (mmio::read<reg_t>(mmio::toAddress(bank, Register::ISR)) & mmio::bit(1) == 0);

            // Write next byte to transmit into TXDR
            mmio::write<reg_t>(mmio::toAddress(bank, Register::TXDR), data[i]);

        }

    }

    void receive(Bank bank, size_t numBytes, u8 *data) {
        if (numBytes > 0xFF) 
            utl::panic();

        // Set NBYTES value
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::CR2), (numBytes & 0xFF) << 16, 0xFF << 16);

        // Enable auto end mode
        mmio::modify<reg_t>(mmio::toAddress(bank, Register::CR2), mmio::bit(25), mmio::NoChange);

        // Receive N bytes
        for (u16 i = 0; i < numBytes; i++) {
            // Wait till there's data in the receive register
            while (mmio::read<reg_t>(mmio::toAddress(bank, Register::ISR)) & mmio::bit(2) == 0);

            // Write next byte to transmit into TXDR
            data[i] = static_cast<u8>(mmio::read<reg_t>(mmio::toAddress(bank, Register::RXDR)) & 0xFF);
        }
    }

}