#include <iostream>
#include "egeg.hpp"
#include "id.hpp"
#include "event_container.hpp"
#include "task_manager.hpp"
#include "field.hpp"
#include "property.hpp"
#include "result.hpp"
#include "utility_function.hpp"
#include "angle.hpp"

using namespace easy_engine::t_lib;
using namespace easy_engine::m_lib;

Degrees deg{180.0F};
Radians rad{deg};

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

    std::cout << deg << " " << rad << std::endl;
    std::cout << deg++ << " " << deg << std::endl; 

}
