#ifndef CORETYPES_CONTAINERS_VISITOROBJECT_H
#define CORETYPES_CONTAINERS_VISITOROBJECT_H
#include <concepts>
#include <utility>

namespace ct {
template <typename T>
class VisitorList;

template <typename ThisType, typename BaseType>
    requires std::move_constructible<ThisType>
class VisitorObject final {
    friend VisitorList<BaseType>;

   public:
    explicit VisitorObject(ThisType&& value)
        : thisTypeValue(std::move(value)) {}
    VisitorObject(VisitorObject&&) = default;

    VisitorObject& operator=(VisitorObject&&) = delete;
    VisitorObject(const VisitorObject&) = delete;
    VisitorObject& operator=(const VisitorObject&) = delete;
    ~VisitorObject() = default;

   private:
    union {
        ThisType thisTypeValue;
    };
};
}  // namespace ct
#endif  // CORETYPES_CONTAINERS_VISITOROBJECT_H