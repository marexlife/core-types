#ifndef CORETYPES_DEFER_H
#define CORETYPES_DEFER_H
#include <concepts>
#include <type_traits>
#include <utility>

namespace ct {
template <typename Functor>
    requires std::invocable<Functor> &&
             std::copy_constructible<Functor>
class Defer final {
   public:
    explicit Defer(Functor&& functor) noexcept(
        std::is_nothrow_move_constructible_v<Functor>)
        : functor(std::move(functor)) {}

    Defer(Defer&&) = delete;
    Defer& operator=(Defer&&) = delete;
    Defer(const Defer&) = delete;
    Defer& operator=(const Defer&) = delete;

    ~Defer() noexcept(std::is_nothrow_destructible_v<Functor>) =
        default;

   private:
    Functor functor;
};
}  // namespace ct
#endif  // CORETYPES_DEFER_H