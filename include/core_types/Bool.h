#ifndef CORETYPES_BOOL_H
#define CORETYPES_BOOL_H
namespace core_types {

class Bool final {
public:
    explicit constexpr Bool(char value)
        : m_value(value)
    {
    }

    Bool() = default;

    [[nodiscard]] static Bool makeTrue() { return Bool { true }; }

    [[nodiscard]] static Bool makeFalse() { return Bool { false }; }

    [[nodiscard]] bool isTrue() const { return m_value; }
    [[nodiscard]] bool isFalse() const { return !m_value; }

    [[nodiscard]] bool operator<=>(const Bool&) const = default;

private:
    bool m_value { };
};
}
#endif // CORETYPES_BOOL_H