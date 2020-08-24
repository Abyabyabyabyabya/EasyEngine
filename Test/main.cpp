#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <functional>
#include <any>
#include "graphics_manager.hpp"

//using namespace egeg::t_lib;
//using namespace egeg::m_lib;
//using namespace egeg::i_lib;

struct Base {
    Base() = default;
    Base(const Base& Right) {
        std::cout << "base copy" << std::endl;
    }
    Base(Base&& Right) {
        std::cout << "base move" << std::endl;
    }
};

struct D : Base {
    D() = default;
};

int main() {
    using namespace std::chrono;

    D d;
    D c = d;
    D m = std::move(d);
}
