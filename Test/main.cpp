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

constexpr float a[]{0.0F, 0.0F, 0.0F, 0.0F};
constexpr float b[]{1.0F, 1.0F, 1.0F, 1.0F};
constexpr float c[]{2.0F, 2.0F, 2.0F, 2.0F};
constexpr Vector4D va = a;
constexpr Vector4D vb = b;
constexpr Vector4D vc = c;
constexpr Vec4Add sum = (va, Vec4Add(vb,vc));
constexpr Vector4D sumv = sum;

constexpr float has2[] = {0.0F, 0.0F};
constexpr Vector2D temporary{has2};


struct OBJ {
    static int d;
    double dum;
    static constexpr bool is = true;
};
int OBJ::d;

int main() {
   /* float vec2_1[]{0.0F, 0.0F, 0.0F, 0.0F};
    const float vec2_2[]{1.0F, 1.0F, 1.0F, 1.0F};
        arr_add<4> add{};
    for(uint64_t i=0; i<1000000; ++i) {
        add(vec2_1, vec2_2);
        add(vec2_1, vec2_1);
        add(vec2_1, vec2_2);
    }

    Vector4D vec_1{};
    Vector4D vec_2{1.0F, 1.0F, 1.0F, 1.0F};*/
    
    {
        using namespace default_operation;
        Vector4D v1{0.0F, 0.08F, 0.0F, 0.002F};
        Vector4D v2{0.23F, -0.003F, 0.0009F, 0.06F};
        Vector4D v3{-0.05F, 0.0F, 0.09F, 0.0F};
    for(uint64_t i=0; i<100000; ++i) {
        v1 += v2 + v3 + v2 * 10.0F;
        for(uint64_t j=0; j<10; ++j)
            v2 += v1 + v3 * 12.0F + v1;
    }
    std::cout << v1.x << " " << v1.y << " " << v1.z << " " << v1.w << std::endl;
        
    }
    {
        using namespace default_noncopy_operation;
        Vector4D v1{0.0F, 0.08F, 0.0F, 0.002F};
        Vector4D v2{0.23F, -0.003F, 0.0009F, 0.06F};
        Vector4D v3{-0.05F, 0.0F, 0.09F, 0.0F};
    for(uint64_t i=0; i<100000; ++i) {
        v1 += v2 + v3 + v2 * 10.0F;
        for(uint64_t j=0; j<10; ++j)
            v2 += v1 + v3 * 12.0F + v1;
    }
    std::cout << v1.x << " " << v1.y << " " << v1.z << " " << v1.w << std::endl;
    }

    /*Vector4DA veca_1{};
    Vector4DA veca_2{1.0F, 1.0F, 1.0F, 1.0F};
    for(uint64_t i=0; i<1000000; ++i) {
    *reinterpret_cast<__m128*>(&veca_1) = 
        simd_operation::vectorAdd(
            simd_operation::vectorAdd(
                simd_operation::vectorAdd(veca_1, veca_2), veca_1),
                veca_2
        );
    }*/
}
