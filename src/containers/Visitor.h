#ifndef CORETYPES_VISITOR_H
#define CORETYPES_VISITOR_H
#include <concepts>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <vector>

namespace ct {
template <typename ObjectType>
class Visitor final {
   public:
    Visitor() = default;
    Visitor(Visitor&&) = delete;
    Visitor& operator=(Visitor&&) = delete;
    Visitor(const Visitor&) = delete;
    Visitor& operator=(const Visitor&) = delete;
    ~Visitor() {
        std::cout << "dtor not implemented yet";
        /*
        Visitor::forEach(
            [&](ObjectType* object) { object->~ObjectType(); });
        */
    }

    template <typename PushedObjectType, typename... Args>
        requires std::constructible_from<PushedObjectType, Args...>
    void create(Args... args) {
        constexpr std::size_t objectSize = sizeof(PushedObjectType);
        std::byte* newObjectBytes = nullptr;
        new (newObjectBytes)
            PushedObjectType(std::forward<Args>(args)...);

        for (std::byte* iter = newObjectBytes;
             iter < newObjectBytes + objectSize; ++iter) {
            objectBytes.emplace_back(*iter);
        }

        objectHeads.emplace_back(objectSize);
    }

    template <typename IterFunc>
    void forEach(IterFunc iterFunc) {
        auto byteIter = objectBytes.begin().base();

        for (auto& objectHead : objectHeads) {
            iterFunc(reinterpret_cast<ObjectType*>(byteIter));

            byteIter += objectHead;
        }
    }

   private:
    std::vector<std::byte> objectBytes;
    std::vector<std::size_t> objectHeads;
};
}  // namespace ct
#endif  // CORETYPES_VISITOR_H