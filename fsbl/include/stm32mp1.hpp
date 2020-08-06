#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdbool>

#include "types.hpp"
#include "units.hpp"

#define PACKED __attribute__((packed))
#define FORCE_INLINE inline __attribute__((always_inline))

#define PADDING(addr, next) std::uint8_t padding_x##addr[next - addr]

namespace mp1 {

}