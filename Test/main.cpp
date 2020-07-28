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

constexpr Vector2D c_v0{};
constexpr Vector2D c_v1{};
//constexpr Vector2D c_sum = vectorAdd(c_v0, c_v1);
  //constexpr Vector2D c_sum = c_v0 + c_v1;

namespace {
    int func() {return 0;}
}
void func() {}

int main() {
    Vector2D v;
    v.x = 0;
    v.y = 5;
    Vector2D v2{vec_d};
    noexcept(v2 = std::move(v));
    //v2 = std::move(v);

    std::cout << v.v[0] << "," << v.v[1] << std::endl;
    std::cout << v2.v[0] << "," << v2.v[1] << std::endl;

    Matrix3x3 mat{mat_d};
    for(int i=0; i<3; ++i) {
      for(int j=0; j<3; ++j)
        std::cout << mat.m[i][j] << ", ";
      std::cout << std::endl;
    }
    //mat[0][3];

    Vector2D t{};
    std::cout << t.x << " " << t.y << " " << std::endl;
    Vector2D t2{1.0F, 2.0F};
    t2 += Vector2D{0.0F, 8.0F};
    std::cout << t2.x << " " << t2.y << " " << std::endl;

    //Vector2D sum = run_time_calculation::vectorAdd(t, t2);

    func();
}
