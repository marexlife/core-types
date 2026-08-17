#ifndef CORETYPES_VISITOR_H
#define CORETYPES_VISITOR_H
#include <concepts>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <vector>

namespace ct {
template <typename ObjecType>
class Visitor final {
   public:
    Visitor() : objectHeads(), bump(), objectBytes() {}

    template <typename PushedObjectType, typename... Args>
        requires std::constructible_from<PushedObjectType, Args...>
    void create(Args... args) {
        constexpr std::size_t objectSize = sizeof(PushedObjectType);
        new (objectBytes + bump)
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
            void* objectStorage = nullptr;

            std::memcpy(objectStorage, byteIter, objectHead);

            iterFunc(reinterpret_cast<ObjecType*>(byteIter));

            byteIter += objectHead;
        }
    }

    ~Visitor() {
        std::cout << "dtor not implemented yet";
        /*
        Visitor::forEach(
            [&](ObjectType* object) { object->~ObjectType(); });
        */
    }

   private:
    std::vector<std::size_t> objectHeads;
    std::size_t bump = 0;
    std::byte* objectBytes;
};
}  // namespace ct
#endif  // CORETYPES_VISITOR_H