#ifndef CORETYPES_NUMBERWRAPPER_H
#define CORETYPES_NUMBERWRAPPER_H
#include <stdfloat>
#include <type_traits>

namespace core_types {
template <typename WrappedType, typename Tag>
    requires(std::is_arithmetic_v<WrappedType>
        && std::is_default_constructible_v<WrappedType>)
class NumberWrapper final {
public:
    constexpr NumberWrapper(WrappedType value)
        : m_value(value)
    {
    }

    NumberWrapper() = default;
    NumberWrapper& operator=(NumberWrapper&&) = default;
    NumberWrapper(const NumberWrapper&) = default;
    NumberWrapper(NumberWrapper&&) = default;
    ~NumberWrapper() = default;

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