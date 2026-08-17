#ifndef CORETYPES_VISITOR_H
#define CORETYPES_VISITOR_H
#include <bit>
#include <cstddef>
#include <cstring>
#include <vector>

namespace ct {
template <typename ObjectType>
class VisitorVector final {
   public:
    VisitorVector() = default;
    VisitorVector(VisitorVector&&) = delete;
    VisitorVector& operator=(VisitorVector&&) = delete;
    VisitorVector(const VisitorVector&) = delete;
    VisitorVector& operator=(const VisitorVector&) = delete;
    ~VisitorVector() {
        forEach([&](ObjectType* object) { object->~ObjectType(); });
    }

    template <typename PushedObjectType>
    void push(PushedObjectType* object) {
        constexpr std::size_t objectSize = sizeof(PushedObjectType);
        std::byte* bytes = std::bit_cast<std::byte*>(object);

        for (std::byte* iter = bytes; iter != bytes + objectSize;
             ++iter) {
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