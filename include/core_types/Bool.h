#ifndef CORETYPES_BOOL_H
#define CORETYPES_BOOL_H
namespace core_types {
class Char final {
public:
    explicit Char(bool value)
        : m_value(value)
    {
    }

    [[nodiscard]] static Char makeTrue() { return Char { true }; }

    [[nodiscard]] static Char makeFalse() { return Char { false }; }

    Char() = default;
    Char(Char&&) = default;
    Char& operator=(Char&&) = default;
    Char(const Char&) = default;
    Char& operator=(const Char&) = default;
    ~Char() = default;

    [[nodiscard]] bool isTrue() const { return m_value; }
    [[nodiscard]] bool isFalse() const { return !m_value; }

    [[nodiscard]] bool operator<=>(const Char&) const = default;

private:
    bool m_value { };
};
}
#endif // CORETYPES_BOOL_H