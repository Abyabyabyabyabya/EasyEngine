#include <iostream>
#include <chrono>
#include "egeg.hpp"
#include "id.hpp"
#include "event_container.hpp"
#include "task_manager.hpp"
#include "field.hpp"
#include "property.hpp"
#include "result.hpp"
#include "utility_function.hpp"
#include "angle.hpp"
//#define EGEG_MLIB_USE_COMPILE_TIME_CALCULATION
#include "mvector.hpp"
#include "mvector.hpp"

using namespace egeg;
using namespace easy_engine::t_lib;
using namespace easy_engine::m_lib;


static constexpr float vec_d[] = {1, 1};
static constexpr float mat_d[9] {
    1,2,3,
    4,1,5,
    6,1,7
};

using m_lib::Vector2D;
using m_lib::Matrix3x3;

constexpr Vector4D c_v0{1.0F, 2.0F, 3.0F, 4.0F};
constexpr Vector4D c_v1{5.0F, 6.0F, 7.0F, 8.0F};

int main() {
    using namespace std::chrono;
  // run-time
    auto start = high_resolution_clock::now();
    for(size_t i=0; i<10000000; ++i)
        run_time_calculation::dot(c_v0, Vector4D{
            rand()%10000+0.1F,
            rand()%10000+0.1F,
            rand()%10000+0.1F,
            rand()%10000+0.1F,
            });
    auto end = high_resolution_clock::now();
    auto run = duration_cast<milliseconds>(end-start).count();
  // compile-time
    start = high_resolution_clock::now();
    for(size_t i=0; i<10000000; ++i)
        compile_time_calculation::dot(c_v0, Vector4D{
            rand()%10000+0.1F,
            rand()%10000+0.1F,
            rand()%10000+0.1F,
            rand()%10000+0.1F,
            });
    end = high_resolution_clock::now();
    auto cmp = duration_cast<milliseconds>(end-start).count();

    std::cout << "run-time: " << run << std::endl;
    std::cout << "cmp_time: " << cmp << std::endl;
}
