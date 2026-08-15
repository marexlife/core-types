#ifndef CORETYPES_VISITOR_H
#define CORETYPES_VISITOR_H
#include <concepts>
#include <cstddef>
#include <cstring>
#include <vector>

namespace ct {
template <typename ObjectType>
class Visitor final {
   public:
    Visitor() : objectBytes(), objectHeads() {}

    template <typename PushedObjectType, typename... Args>
        requires std::derived_from<PushedObjectType, ObjectType> &&
                 std::constructible_from<PushedObjectType, Args...>
    void create(Args... args) {
        constexpr std::size_t objectSize = sizeof(ObjectType);
        new (objectBytes)
            PushedObjectType(std::forward<Args>(args)...);

        objectHeads.emplace_back(objectSize);
    }

    Visitor(Visitor&&) = delete;
    Visitor& operator=(Visitor&&) = delete;
    Visitor(const Visitor&) = delete;
    Visitor& operator=(const Visitor&) = delete;

    template <typename IterFunc>
    void forEach(IterFunc iterFunc) {
        std::byte* byteIter = objectBytes;

        for (auto& objectHead : objectHeads) {
            ObjectType* objectType;

            std::memcpy(objectType, byteIter, objectHead);

            iterFunc(objectType);

            byteIter += objectHead;
        }
    }

    ~Visitor() {
        Visitor::forEach(
            [&](ObjectType* object) { object->~ObjectType(); });
    }

   private:
    std::vector<std::size_t> objectHeads;
    std::byte objectBytes[];
};
}  // namespace ct
#endif  // CORETYPES_VISITOR_H