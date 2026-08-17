#ifndef CORETYPES_CONTAINERS_VISITOROBJECT_H
#define CORETYPES_CONTAINERS_VISITOROBJECT_H
#include <concepts>
#include <utility>

namespace ct {
template <typename T>
class VisitorVector;

template <typename T>
    requires std::move_constructible<T>
class VisitorObject final {
    friend VisitorVector<T>;

   public:
    explicit VisitorObject(T&& value) : value(std::move(value)) {}
    VisitorObject(VisitorObject&&) = default;

    VisitorObject& operator=(VisitorObject&&) = delete;
    VisitorObject(const VisitorObject&) = delete;
    VisitorObject& operator=(const VisitorObject&) = delete;
    ~VisitorObject() = default;

   private:
    T value;
};
}  // namespace ct
#endif  // CORETYPES_CONTAINERS_VISITOROBJECT_H