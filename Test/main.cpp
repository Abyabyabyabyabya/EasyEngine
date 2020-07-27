#include <iostream>
#include "egeg.hpp"
#include "id.hpp"
#include "event_container.hpp"
#include "task_manager.hpp"
#include "field.hpp"
#include "property.hpp"
#include "result.hpp"
#include "utility_function.hpp"

using namespace easy_engine::t_lib;

    int arr[10];
    static constexpr size_t size = arraySize(arr);

struct Temp {
    Temp(int) {}

    int handle;
};
Result<int> func() {

    return Failure{};
}

int main() {
    Result<Temp> r{Success{}, Temp{5}};

    std::cout << r->handle << std::endl;
    (*r).handle;
}
