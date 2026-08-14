#ifndef CORETYPES_VISITOR_H
#define CORETYPES_VISITOR_H
#include <concepts>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <vector>

namespace ct {
template <typename ObjectType>
class Visitor final {
   public:
    Visitor() noexcept(
        std::is_nothrow_constructible_v<decltype(objectBytes)> &&
        std::is_nothrow_constructible_v<decltype(objectHeads)>)
        : objectBytes(), objectHeads() {}

    template <typename PushedObjectType, typename... Args>
        requires std::derived_from<PushedObjectType, ObjectType> &&
                 std::constructible_from<PushedObjectType, Args...>
    void create(Args... args) noexcept(
        std::is_nothrow_constructible_v<ObjectType, Args...>) {
        constexpr std::size_t objectSize = sizeof(ObjectType);
        std::byte* rawObjectBytes;

        new (rawObjectBytes)
            ObjectType(std::forward<ObjectType>(args)...);

        for (std::byte* iter = rawObjectBytes;
             iter != rawObjectBytes + objectSize; ++iter) {
            objectBytes.emplace_back(*iter);
        }

        objectHeads.emplace_back(objectSize);
    }

    template <typename IterFunc>
    void forEach(IterFunc iterFunc) {
        auto byteIter = objectBytes.begin();

        for (auto& objectHead : objectHeads) {
            auto object =
                reinterpret_cast<ObjectType&>(*byteIter.base());

            std::invoke(iterFunc, *object);

            byteIter += objectHead;
        }
    }

    ~Visitor() noexcept(std::is_nothrow_constructible_v<ObjectType>) {
        Visitor::forEach(
            [&](ObjectType& object) { object.~ObjectType(); });
    }

   private:
    std::vector<std::size_t> objectHeads;
    std::vector<std::byte> objectBytes;
};
}  // namespace ct
#endif  // CORETYPES_VISITOR_H