#ifndef CORETYPES_VISITOR_H
#define CORETYPES_VISITOR_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace ct {
class Visitor final {
   public:
    Visitor() : objectBytes(), objectHeads() {}

    template <typename ObjectType, typename... Args>
    void push(ObjectType&& object) {
        
        objectHeads.emplace_back(sizeof(ObjectType));
    }

    template <typename ObjectType, typename... Args>
    void create(Args... args) {
        new (objectBytes)
            ObjectType(std::forward<ObjectType>(args)...);

        objectHeads.emplace_back(sizeof(ObjectType));
    }

    void forEach() {
        for (auto& objectHead : objectHeads) {
        }
    }

   private:
    std::vector<std::size_t> objectHeads;
    std::vector<std::uint8_t> objectBytes;
};
}  // namespace ct
#endif  // CORETYPES_VISITOR_H