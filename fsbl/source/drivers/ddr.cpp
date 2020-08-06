#include "drivers/ddr.hpp"

#include "drivers/mmio.hpp"

namespace mp1::ddr {

    Type getConnectedType() {
        reg_t mstr = mmio::read<reg_t>(mmio::toAddress(Bank::DDRCTRL, Register::MSTR));

        if (mstr & mmio::bit(0) != 0)
            return Type::DDR3;
        else if (mstr & mmio::bit(2) != 0)
            return Type::LPDDR2;
        else if (mstr & mmio::bit(3) != 0)
            return Type::LPDDR3;
        else
            return Type::Invalid;
    }

}