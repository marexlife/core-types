#ifndef CORETYPES_VISITOR_H
#define CORETYPES_VISITOR_H
#include <bit>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <vector>

#include "VisitorObject.h"

namespace ct {
template <typename ObjectType>
class VisitorList final {
   public:
    VisitorList() = default;
    VisitorList(VisitorList&&) = delete;
    VisitorList& operator=(VisitorList&&) = delete;
    VisitorList(const VisitorList&) = delete;
    VisitorList& operator=(const VisitorList&) = delete;
    ~VisitorList() {
        forEach([&](ObjectType& object) { object.~ObjectType(); });
    }

    template <typename ThisType>
        requires std::move_constructible<ThisType>
    void push(VisitorObject<ThisType, ObjectType> object) {
        constexpr std::size_t objectSize = sizeof(ThisType);

        std::byte* bytes =
            std::bit_cast<std::byte*>(&object.thisTypeValue);

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
            iterFunc(reinterpret_cast<ObjectType&>(*byteIter));

            byteIter += objectHead;
        }
    }

   private:
    std::vector<std::byte> objectBytes;
    std::vector<std::size_t> objectHeads;
};
}  // namespace ct
#endif  // CORETYPES_VISITOR_H