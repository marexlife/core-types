#ifndef CORETYPES_BOOL_H
#define CORETYPES_BOOL_H
namespace ct {

class Bool final {
   public:
    explicit constexpr Bool(bool value) noexcept : value(value) {}

    [[nodiscard]] static Bool makeTrue() noexcept {
        return Bool{true};
    }

    [[nodiscard]] static Bool makeFalse() noexcept {
        return Bool{false};
    }

    [[nodiscard]] bool isTrue() const noexcept { return value; }
    [[nodiscard]] bool isFalse() const noexcept { return !value; }

    [[nodiscard]] bool operator<=>(const Bool&) const noexcept =
        default;

   private:
    bool value;
};
}  // namespace ct
#endif  // CORETYPES_BOOL_H