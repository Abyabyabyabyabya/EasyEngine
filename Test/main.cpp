#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include "egeg.hpp"
#include "id.hpp"
#include "egeg_math.hpp"
#include "utility_function.hpp"
#include "xinput_gamepad.hpp"
#include "alloc.hpp"
#include "input_manager.hpp"
#include "clock.hpp"
#include "time.hpp"

using namespace egeg::t_lib;
using namespace egeg::m_lib;
using namespace egeg::i_lib;

void func(std::unique_ptr<int> v) {
    std::cout << *v;
}

int main() {
    using namespace std::chrono;

    Clock clock;
    for(int i=0; i<10; ++i) {
    auto start = high_resolution_clock::now();
        Clock wait{};

        std::cout << "delta " << clock.delta().microseconds() << std::endl;
        std::cout << "elapsed " << clock.elapsed().microseconds() << std::endl;
   
        std::this_thread::sleep_for(microseconds{10000});
        do {
            wait.update();
        } while(wait.elapsed().microseconds()<16666);
    auto end = high_resolution_clock::now();

       // std::cout << "elapsed " << duration_cast<microseconds>(end-start).count() << std::endl;
    }
    clock.update();
    std::cout << "milli" << clock.elapsed().milliseconds() << std::endl;
    std::cout << "micro" << clock.elapsed().microseconds() << std::endl;

    egeg::Time t;
    egeg::Time t1;
    t += t1;

    t == t1;

    t == egeg::Nanoseconds(10);
    t == egeg::Seconds{10};

    t = egeg::Minutes{60};
    std::cout << t.hours() << std::endl;
}
