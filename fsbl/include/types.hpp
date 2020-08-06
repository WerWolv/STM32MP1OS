#pragma once

namespace mp1 {

    using u8  = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using s8  = std::int8_t;
    using s16 = std::int16_t;
    using s32 = std::int32_t;
    using s64 = std::int64_t;

    using vu8 = volatile std::uint8_t;
    using vu16 = volatile std::uint16_t;
    using vu32 = volatile std::uint32_t;
    using vu64 = volatile std::uint64_t;

    using vs8 = volatile std::uint8_t;
    using vs16 = volatile std::uint16_t;
    using vs32 = volatile std::uint32_t;
    using vs64 = volatile std::uint64_t;


    using reg_t  = mp1::vu32;
    using addr_t = mp1::u32;
    using offset_t = mp1::s32;

}