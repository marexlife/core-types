#ifndef CORETYPES_BOOL_H
#define CORETYPES_BOOL_H
namespace ct {

class Bool final {
   public:
    explicit constexpr Bool(char value) : value(value) {}

    Bool() = default;

    [[nodiscard]] static Bool makeTrue() { return Bool{true}; }

    [[nodiscard]] static Bool makeFalse() { return Bool{false}; }

    [[nodiscard]] bool isTrue() const { return value; }
    [[nodiscard]] bool isFalse() const { return !value; }

    [[nodiscard]] bool operator<=>(const Bool&) const = default;

   private:
    bool value{};
};
}  // namespace ct
#endif  // CORETYPES_BOOL_H