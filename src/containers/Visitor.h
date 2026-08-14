#ifndef CORETYPES_VISITOR_H
#define CORETYPES_VISITOR_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace ct {
class Visitor final {
   public:
    Visitor() {}

    void push() {}

   private:
    std::vector<std::uint8_t> objectBytes;
    std::vector<std::size_t> objectHeads;
};
}  // namespace ct
#endif  // CORETYPES_VISITOR_H