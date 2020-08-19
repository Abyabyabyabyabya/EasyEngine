#pragma once

#include <memory>

template <class ObjectTy>
class HeapAlloced {
public :
    using ObjectType = ObjectTy;

    static void* operator new(size_t) = delete;
    static void operator delete(void*) = delete;

    HeapAlloced(std::unique_ptr<ObjectType>& Ptr) :
        ptr_{std::move(Ptr)}
    {}
    template <class ...ArgTypes>
    HeapAlloced(ArgTypes&& ...Args) :
        ptr_{std::make_unique<ObjectType>(std::forward<ArgTypes>(Args)...)}
    {}

    [[nodiscard]] ObjectType* operator->() const noexcept {
        return ptr_.get();
    }
    [[nodiscard]] ObjectType& operator*() const noexcept {
        return *ptr_;
    }

    operator std::unique_ptr<ObjectType>() && noexcept {
        return std::move(ptr_);
    }

private :
    std::unique_ptr<ObjectType> ptr_;
};

template <class ObjectTy>
class StackAlloced {
public :
    using ObjectType = ObjectTy;

    static void* operator new(size_t) = delete;
    static void operator delete(void*) = delete;

    template <class ...ArgTypes>
    StackAlloced(ArgTypes&& ...Args) :
        obj_{std::forward<ArgTypes>(Args)...}
    {}

    [[nodiscard]] ObjectType* operator->() const noexcept {
        return &obj_;
    }
    [[nodiscard]] ObjectType& operator*() const noexcept {
        return obj_;
    }

private :
    ObjectType obj_;
};
