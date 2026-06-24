#ifndef CORETYPES_CHAR_H
#define CORETYPES_CHAR_H
namespace core_types {
class Char final {
public:
    explicit constexpr Char(char value)
        : m_value(value)
    {
    }

    [[nodiscard]] bool operator<=>(const Char&) const = default;

private:
    char m_value { };
};
}
#endif // CORETYPES_CHAR_H