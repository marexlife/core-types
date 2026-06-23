#ifndef CORETYPES_INT32_H_
#define CORETYPES_INT32_H_

#include <cmath>
#include <cstdint>
#include <stdfloat>
#include <type_traits>

namespace CoreTypes {
template <typename WrappedType, typename Tag>
    requires std::is_arithmetic_v<WrappedType>
class NumberWrapper final {
public:
    constexpr NumberWrapper(WrappedType value)
        : m_value(value)
    {
    }
    ~NumberWrapper() = default;

    NumberWrapper& operator=(NumberWrapper&&) = default;
    NumberWrapper(const NumberWrapper&) = default;
    NumberWrapper(NumberWrapper&&) = default;

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

    [[nodiscard]] constexpr NumberWrapper& operator/=(
        NumberWrapper& rhs)
    {
        this->m_value /= rhs.m_value;

        return *this;
    }

    [[nodiscard]] constexpr bool operator==(NumberWrapper& rhs) const
    {
        return this->m_value == rhs.m_value;
    }

    [[nodiscard]] constexpr bool operator!=(NumberWrapper& rhs) const
    {
        return this->m_value != rhs.m_value;
    }

    [[nodiscard]] constexpr NumberWrapper operator+(
        NumberWrapper& rhs) const
    {
        return NumberWrapper(this->m_value + rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper operator-(
        NumberWrapper& rhs) const
    {
        return NumberWrapper(this->m_value + rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper operator*(
        NumberWrapper& rhs) const
    {
        return NumberWrapper(this->m_value * rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper operator/(
        NumberWrapper& rhs) const
    {
        return NumberWrapper(this->m_value / rhs.m_value);
    }

    [[nodiscard]] constexpr NumberWrapper& operator=(
        const NumberWrapper& rhs)
    {
        this->m_value = rhs.m_value;
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
    WrappedType m_value;
};

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
} // namespace CoreTypes
#endif // CORETYPES_INT32_H_