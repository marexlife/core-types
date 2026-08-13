#ifndef CORETYPES_CHAR_H
#define CORETYPES_CHAR_H
namespace core_types {
class Char final {
   public:
    explicit constexpr Char(char value) : value(value) {}

    Char() = default;

    [[nodiscard]] bool operator<=>(const Char&) const = default;

   private:
    char value{};
};
}  // namespace core_types
#endif  // CORETYPES_CHAR_H