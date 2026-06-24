#ifndef CORETYPES_BOOL_H
#define CORETYPES_BOOL_H
namespace core_types {
class Bool final {
public:
    explicit constexpr Bool(char value)
        : m_value(value)
    {
    }

    [[nodiscard]] static Bool makeTrue() { return Bool { true }; }

    [[nodiscard]] static Bool makeFalse() { return Bool { false }; }

    Bool() = default;
    Bool(Bool&&) = default;
    Bool& operator=(Bool&&) = default;
    Bool(const Bool&) = default;
    Bool& operator=(const Bool&) = default;
    ~Bool() = default;

    [[nodiscard]] bool isTrue() const { return m_value; }
    [[nodiscard]] bool isFalse() const { return !m_value; }

    [[nodiscard]] bool operator<=>(const Bool&) const = default;

private:
    bool m_value { };
};
}
#endif // CORETYPES_BOOL_H