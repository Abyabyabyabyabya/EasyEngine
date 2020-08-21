#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <functional>
#include "egeg.hpp"
#include "time.hpp"
#include "update_manager.hpp"
#include <any>

using namespace egeg::t_lib;
using namespace egeg::m_lib;
using namespace egeg::i_lib;

void func(std::unique_ptr<int> v) {
    std::cout << *v;
}
void fu(egeg::Time) {}

int main() {
    using namespace std::chrono;
    
}
