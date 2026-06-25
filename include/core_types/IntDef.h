#ifndef CORETYPES_NUMBERWRAPPER_H
#define CORETYPES_NUMBERWRAPPER_H
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <stdfloat>
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

template <typename WrappedType, typename Tag>
    requires(std::is_arithmetic_v<WrappedType>
        && std::is_default_constructible_v<WrappedType>)
class NumberWrapper final {
public:
    using UnderlyingType = WrappedType;

    explicit constexpr NumberWrapper(WrappedType value)
        : m_value(value)
    {
    }

    NumberWrapper() = default;

    template <typename Fn>
        requires std::is_invocable_v<Fn,
            NumberWrapper<WrappedType, Tag>>
    constexpr static void forLoop(
        Fn fn, NumberWrapper<WrappedType, Tag> count)
    {
        for (NumberWrapper<WrappedType, Tag> i = 0; i < count; ++i) {
            fn(i);
        }
    }

    [[nodiscard]] consteval static Usize max()
    {
        return std::numeric_limits<WrappedType>::max();
    }

    [[nodiscard]] consteval static Usize min()
    {
        return std::numeric_limits<WrappedType>::min();
    }

    [[nodiscard]] constexpr NumberWrapper& operator+=(
        NumberWrapper& rhs)
    {
        *this += rhs;

        return *this;
    }

    [[nodiscard]] constexpr NumberWrapper& operator-=(
        NumberWrapper& rhs)
    {
        *this -= rhs;

        return *this;
    }

    [[nodiscard]] constexpr NumberWrapper& operator*=(
        NumberWrapper& rhs)
    {
        *this *= rhs;

        return *this;
    }

    constexpr void operator++() { ++m_value; }

    [[nodiscard]] constexpr NumberWrapper& operator/=(
        NumberWrapper& rhs)
    {
        *this /= rhs;

        return *this;
    }

    [[nodiscard]] bool operator<=>(const NumberWrapper&) const
        = default;

    [[nodiscard]] constexpr NumberWrapper operator+(
        NumberWrapper& rhs) const
    {
        if (std::numeric_limits<WrappedType>::max() - rhs < m_value)
            [[unlikely]] {
            throw std::overflow_error("Addition was too big");
        }

        return NumberWrapper(m_value + rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper operator-(
        NumberWrapper& rhs) const
    {
        if (std::numeric_limits<WrappedType>::min() + rhs > m_value)
            [[unlikely]] {
            throw std::underflow_error("Subtraction was too big");
        }

        return NumberWrapper(m_value + rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper operator*(
        NumberWrapper& rhs) const
    {
        if (std::numeric_limits<WrappedType>::max() / rhs < m_value)
            [[unlikely]] {
            throw std::overflow_error("Multiplication was too big");
        }

        return NumberWrapper(m_value * rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper operator/(
        NumberWrapper& rhs) const
    {
        if (m_value == NumberWrapper { 0 }) [[unlikely]] {
            throw std::underflow_error("division by zero");
        }

        return NumberWrapper(m_value / rhs.m_value);
    }

    [[nodiscard]] constexpr WrappedType operator*() const
    {
        return m_value;
    }

private:
    WrappedType m_value { };
};
} // namespace core_types
#endif // CORETYPES_NUMBERWRAPPER_H