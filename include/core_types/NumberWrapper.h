#ifndef CORETYPES_NUMBERWRAPPER_H
#define CORETYPES_NUMBERWRAPPER_H
#include "IntDef.h"
#include <limits>
#include <stdfloat>
#include <type_traits>

namespace core_types {
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
    NumberWrapper& operator=(NumberWrapper&&) = default;
    NumberWrapper(const NumberWrapper&) = default;
    NumberWrapper(NumberWrapper&&) = default;
    ~NumberWrapper() = default;

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
        m_value += rhs.m_value;

        return *this;
    }

    [[nodiscard]] constexpr NumberWrapper& operator-=(
        NumberWrapper& rhs)
    {
        m_value -= rhs.m_value;

        return *this;
    }

    [[nodiscard]] constexpr NumberWrapper& operator*=(
        NumberWrapper& rhs)
    {
        m_value *= rhs.m_value;

        return *this;
    }

    constexpr void operator++() { ++m_value; }

    [[nodiscard]] constexpr NumberWrapper& operator/=(
        NumberWrapper& rhs)
    {
        m_value /= rhs.m_value;

        return *this;
    }

    [[nodiscard]] bool operator<=>(const NumberWrapper&) const
        = default;

    [[nodiscard]] constexpr NumberWrapper operator+(
        NumberWrapper& rhs) const
    {
        return NumberWrapper(m_value + rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper operator-(
        NumberWrapper& rhs) const
    {
        return NumberWrapper(m_value + rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper operator*(
        NumberWrapper& rhs) const
    {
        return NumberWrapper(m_value * rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper operator/(
        NumberWrapper& rhs) const
    {
        return NumberWrapper(m_value / rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper& operator=(
        const NumberWrapper& rhs)
    {
        m_value = rhs.m_value;
        return *this;
    }

    [[nodiscard]] constexpr WrappedType operator*() const
    {
        return m_value;
    }

    [[nodiscard]] constexpr WrappedType getRaw() const
    {
        return m_value;
    }

private:
    WrappedType m_value { };
};
} // namespace core_types
#endif // CORETYPES_NUMBERWRAPPER_H