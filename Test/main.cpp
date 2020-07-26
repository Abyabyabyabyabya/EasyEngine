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

int main() {
    Property<Int0, Int1, Int2> prop{};
    Property<Ptr0, decltype(prop)> p;
    //Property<setter> p1;

    prop.field<Int0>() = 1;
    int value = prop.field<Int0>();

    auto output = [](const Property<Int0, Int1, Int2>& P) {
        std::cout << P.field<Int0>() << std::endl;
    };

    //prop.field<int>();
    p.field<Int0>();
    prop.field<Int0>().setPredicate(setter{5});
    
    std::cin >> prop.field<Int0>();

    std::cout << value << std::endl;
    std::cout << std::move(prop).field<Int0>() << std::endl;

    std::cin >> prop;
    std::cout << 
        prop.field<Int0>() <<
        prop.field<Int1>() <<
        prop.field<Int2>() << std::endl;
}
