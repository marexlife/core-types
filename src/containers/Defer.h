#ifndef CORETYPES_DEFER_H
#define CORETYPES_DEFER_H
#include <cstdint>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

namespace ct {
template <typename Functor>
class Defer final {
   public:
    explicit constexpr Defer(Functor functor) noexcept(
        std::is_nothrow_move_constructible_v<Functor>)
        : functor(std::forward<Functor>(functor)) {}

    Defer(Defer&&) = delete;
    Defer& operator=(Defer&&) = delete;
    Defer(const Defer&) = delete;
    Defer& operator=(const Defer&) = delete;

    constexpr ~Defer() noexcept(
        std::is_nothrow_destructible_v<Functor> &&
        std::is_nothrow_invocable_v<Functor>) {
        std::invoke(functor);

        std::vector<std::int32_t> v;
    }

   private:
    Functor functor;
};
}  // namespace ct
#endif  // CORETYPES_DEFER_H