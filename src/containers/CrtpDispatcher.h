#ifndef CORETYPES_CONTAINERS_CRTPDISPATCHER_H
#define CORETYPES_CONTAINERS_CRTPDISPATCHER_H
#include <algorithm>
#include <concepts>

namespace ct {
template <typename BaseType>
    requires std::move_constructible<BaseType>
class CrtpDispatcher final {
   public:
    explicit CrtpDispatcher(BaseType&& value)
        : value(std::move(value)) {}

    CrtpDispatcher(CrtpDispatcher&&) = delete;
    CrtpDispatcher& operator=(CrtpDispatcher&&) = delete;
    CrtpDispatcher(const CrtpDispatcher&) = delete;
    CrtpDispatcher& operator=(const CrtpDispatcher&) = delete;

    ~CrtpDispatcher() {
        CrtpDispatcher::dispatchDestruct<BaseType>();
    }

    template <typename T>
        requires requires(T value) { value.getDerived(); }
    void dispatchDestruct(T& value) {
        CrtpDispatcher::dispatchDestruct<BaseType::DerivedType>(
            value.getDerived());
    }

    template <typename T>
    void dispatchDestruct(T& value) {
        value.~T();
    }

   private:
    union {
        BaseType value;
    };
};
}  // namespace ct
#endif  // CORETYPES_CONTAINERS_CRTPDISPATCHER_H