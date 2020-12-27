#include <algorithm>
#include <iostream>

#include "geometry.h"

Vec3f::Vec3f(const float &v1, const float &v2, const float &v3) {
    m_v1 = v1;
    m_v2 = v2;
    m_v3 = v3;
}

Vec2f::Vec2f(const float &v1, const float &v2) {
    m_v1 = v1;
    m_v2 = v2;
}

Vec2f Vec2f::operator-(const Vec2f &o) {
    Vec2f v;
    v.m_v1 = this->m_v1 - o.m_v1;
    v.m_v2 = this->m_v2 - o.m_v2;
    return v;
};

float Vec2f::dydx() {
    return this->m_v2 / this->m_v1;
}

bool point_is_in_triangle(Vec2f &v1, Vec2f &v2, Vec2f &v3, Vec2f &p) {
    // This code would be dependent on the rotational order of v1, v2, v3.
    // But as long as we define vec_1, vec_2, vec_3 to be vectors in a 3-cycle
    // the booleans only need be the same value.
    bool v1_side = point_is_on_right_side(v1, v2, p);
    bool v2_side = point_is_on_right_side(v2, v3, p);
    bool v3_side = point_is_on_right_side(v3, v1, p);

    return v1_side == v2_side && v2_side == v3_side;
}

bool point_is_on_right_side(Vec2f &v1, Vec2f &v2, Vec2f &p) {
    Vec2f dir = v2 - v1;
    Vec2f mapped_p = p - v1;

    if (dir.m_v1 == 0) 
        return (mapped_p.m_v1 >= 0) ^ (dir.m_v2 < 0);

    return ((dir.dydx() * mapped_p.m_v1) > mapped_p.m_v2) ^ (dir.m_v1 * -1 >= 0);
}
