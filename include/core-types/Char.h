#ifndef CORETYPES_CHAR_H
#define CORETYPES_CHAR_H
namespace core_types {
class Char final {
public:
    explicit Char(char value)
        : m_value(value)
    {
    }

    Char() = default;
    Char(Char&&) = default;
    Char& operator=(Char&&) = default;
    Char(const Char&) = default;
    Char& operator=(const Char&) = default;
    ~Char() = default;

    [[nodiscard]] bool operator<=>(const Char&) const = default;

private:
    char m_value { };
};
}
#endif // CORETYPES_CHAR_H