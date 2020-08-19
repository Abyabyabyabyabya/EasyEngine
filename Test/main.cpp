#include <iostream>
#include <vector>
#include <memory>
#include "egeg.hpp"
#include "id.hpp"
#include "egeg_math.hpp"
#include "utility_function.hpp"
#include "xinput_gamepad.hpp"
#include "alloc.hpp"
#include "input_manager.hpp"

using namespace egeg::t_lib;
using namespace egeg::m_lib;
using namespace egeg::i_lib;

void func(std::unique_ptr<int> v) {
    std::cout << *v;
}

int main() {
}
