#ifndef CORETYPES_CONTAINERS_CRTPBASE_H
#define CORETYPES_CONTAINERS_CRTPBASE_H
template <typename Derived>
class CrtpBase {
   public:
    using DerivedType = Derived;

    CrtpBase() = default;
    CrtpBase(CrtpBase&&) = delete;
    CrtpBase& operator=(CrtpBase&&) = delete;
    CrtpBase(const CrtpBase&) = delete;
    CrtpBase& operator=(const CrtpBase&) = delete;
    ~CrtpBase() = default;

    [[nodiscard]] Derived& getDerived() {
        return static_cast<Derived&>(*this);
    }

   protected:
   private:
};
#endif  // CORETYPES_CONTAINERS_CRTPBASE_H
