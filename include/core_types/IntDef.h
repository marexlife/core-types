#ifndef CORETYPES_INTDEF_H
#define CORETYPES_INTDEF_H
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace core_types {
template <typename WrappedType, typename Tag>
    requires(std::is_arithmetic_v<WrappedType>
        && std::is_default_constructible_v<WrappedType>)
class NumberWrapper;

using Uint8 = NumberWrapper<std::uint8_t, class Uint8Tag>;
using Uint16 = NumberWrapper<std::uint16_t, class Uint16Tag>;
using Uint32 = NumberWrapper<std::uint32_t, class Uint32Tag>;
using Uint64 = NumberWrapper<std::uint64_t, class Uint64Tag>;

using Int8 = NumberWrapper<std::int8_t, class Int8Tag>;
using Int16 = NumberWrapper<std::int16_t, class Int16Tag>;
using Int32 = NumberWrapper<std::int32_t, class Int32Tag>;
using Int64 = NumberWrapper<std::int64_t, class Int64Tag>;

using Float = NumberWrapper<float, class FloatTag>;
using Double = NumberWrapper<double, class DoubleTag>;
using Isize = NumberWrapper<std::size_t, class SizeTag>;
using Usize = NumberWrapper<std::intmax_t, class SizeTag>;
}
#endif // CORETYPES_INTDEF_H