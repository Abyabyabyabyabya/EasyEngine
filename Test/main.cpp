#include <iostream>
#include "egeg.hpp"
#include "id.hpp"
#include "egeg_math.hpp"

using namespace egeg::t_lib;
using namespace egeg::m_lib;

constexpr Matrix3x4 m {
    1.0F, 2.0F, 3.0F, 4.0F,
    5.0F, 6.0F, 7.0F, 8.0F,
    9.0F, 0.0F, 1.0F, 2.0F
};

constexpr Matrix4x3 r {
    1.0F, 2.0F, 3.0F,
    4.0F, 5.0F, 6.0F,
    7.0F, 8.0F, 9.0F,
    0.0F, 1.0F, 2.0F
};

constexpr Matrix4x4 o {
    1.0F, 2.0F, 3.0F, 4.0F,
    5.0F, 6.0F, 7.0F, 8.0F,
    9.0F, 0.0F, 1.0F, 2.0F,
    3.0F, 4.0F, 5.0F, 6.0F
};


inline constexpr Matrix4x4
tra(const Matrix4x4& M) noexcept {
    return Matrix4x4{
        M._00, M._10, M._20, M._30,
        M._01, M._11, M._21, M._31,
        M._02, M._12, M._22, M._32,
        M._03, M._13, M._23, M._33
    };
}

constexpr Matrix4x4 t = tra(o);

inline constexpr Matrix4x4
cmul(const Matrix4x4& L, const Matrix4x4& R) noexcept {
    return Matrix4x4 {
        dot(L.row[0], R.row[0]), dot(L.row[0], R.row[1]), dot(L.row[0], R.row[2]), dot(L.row[0], R.row[3]),
        dot(L.row[1], R.row[0]), dot(L.row[1], R.row[1]), dot(L.row[1], R.row[2]), dot(L.row[1], R.row[3]),
        dot(L.row[2], R.row[0]), dot(L.row[2], R.row[1]), dot(L.row[2], R.row[2]), dot(L.row[2], R.row[3]),
        dot(L.row[3], R.row[0]), dot(L.row[3], R.row[1]), dot(L.row[3], R.row[2]), dot(L.row[3], R.row[3]),
    };
}

constexpr Vector4D v1{1.0F, 1.0F, 1.0F, 1.0F};
constexpr Vector4D v2{2.0F, 2.0F, 2.0F, 2.0F};
constexpr Vector4D v3{3.0F, 3.0F, 3.0F, 3.0F};
constexpr Vector4D v4{4.0F, 4.0F, 4.0F, 4.0F};
constexpr Matrix4x4 l{{v1, v2, v3, v4}};
constexpr Matrix4x4 r2{{v4, v3, v2, v1}};
constexpr auto mul = cmul(l, r2);


int main() {
    
    auto showMatrix = [](const auto& M) {
        for(int i=0; i<M.kRowDimension; ++i) {
            for(int j=0; j<M.kColumnDimension; ++j)
                std::cout << M[i][j] << " ";
            std::cout << std::endl;
        }
    };

    showMatrix(m);
    std::cout << std::endl;
    showMatrix(transpose(m));
    std::cout << std::endl;
    showMatrix(m*r);
}
