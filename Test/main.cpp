#include <iostream>
#include <chrono>
#include <thread>
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
//#define EGEG_MLIB_USE_RUN_TIME_CALCULATION
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

#include "operation.hpp"



constexpr int dig = digit(92309340394830498,
                                   0b010000);

int main() {
    std::cout << digit(403948, 0b1000) << std::endl;
    std::cout << digit(232938479279238474, 0b10000000) << std::endl;
    float vec2_1[]{1.0F, 1.0F};
    const float vec2_2[]{2.0F, 2.0F};
    for(uint64_t i=0; i<1000000; ++i) {
    arr_add<2>{}(vec2_1, vec2_2);
    //std::cout << (vec2_1[0]+=1) << " " << vec2_1[1] << std::endl; 
    }

    Vector2D vec_1;
    Vector2D vec_2;
    
    for(uint64_t i=0; i<1000000; ++i) {
    vec_1 += vec_2;
    //std::cout << (vec_1[0]+=1) << " " << (vec_1[1]+=1) << std::endl;
    }
}
