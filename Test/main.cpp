#include <iostream>
#include "egeg.hpp"
#include "id.hpp"
#include "event_container.hpp"
#include "task_manager.hpp"
#include "field.hpp"
#include "property.hpp"

using namespace easy_engine::t_lib;

using Task = impl::EventType<void()>;

    template <class U, class T>
    struct is_explicitly_convertible {
        static constexpr bool value = std::is_convertible_v<T,U> && std::is_convertible_v<U,T>;
    };

struct F {
    void operator()(Task&, Task) {}
};

struct setter {
    int value{};
    bool operator()(const int& R) const noexcept {
        return R > value;
    }
};


template <uint32_t Idx=0, class TypeIdx=void>
struct TagIndex;

using Int0 = FieldTag<int, 0, setter>;
using Int1 = FieldTag<int, 1>;
using Int2 = FieldTag<int, 2>;

using Ptr0 = FieldTag<std::unique_ptr<int>, 0>;
using Ptr1 = FieldTag<std::unique_ptr<int>, 1>;
using Ptr2 = FieldTag<std::unique_ptr<int>, 2>;
using Ptr3 = FieldTag<std::unique_ptr<int>, 3>;
using Ptr4 = FieldTag<std::unique_ptr<int>, 4>;
using Ptr5 = FieldTag<std::unique_ptr<int>, 5>;

using UniqueProp = Property<Ptr0, Ptr1, Ptr2, Ptr3>;
using UniqueEx = Property<UniqueProp, Ptr4, Ptr5>;

int main() {
    UniqueEx p0{};
    UniqueEx p1{};

    p0.field<Ptr0>() = std::make_unique<int>();
    p0.field<Ptr1>() = std::make_unique<int>();
    p0.field<Ptr2>() = std::make_unique<int>();
    p0.field<Ptr3>() = std::make_unique<int>();
    p0.field<Ptr4>() = std::make_unique<int>();
    p0.field<Ptr5>() = std::make_unique<int>();

    auto show = [](const UniqueEx& Prop, const char* P) {
        std::cout << P << "'s status\n" <<
            Prop.field<Ptr0>().get() << '\n' <<
            Prop.field<Ptr1>().get() << '\n' <<
            Prop.field<Ptr2>().get() << '\n' <<
            Prop.field<Ptr3>().get() << '\n' <<
            Prop.field<Ptr4>().get() << '\n' <<
            Prop.field<Ptr5>().get() << std::endl;
    };

    show(p0, "p0");

    std::cout << "move" << std::endl;
    p1 = std::move(p0);

    show(p0, "p0");
    show(p1, "p1");
}
