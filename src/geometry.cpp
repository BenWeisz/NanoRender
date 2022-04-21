#include <algorithm>
#include <iostream>

#include "geometry.h"

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

    if (dir[0] == 0) 
        return (mapped_p[0] >= 0) ^ (dir[1] < 0);

    float dir_dydx = dir[1] / dir[0];
    return ((dir_dydx * mapped_p[0]) > mapped_p[1]) ^ (dir[0] * -1 >= 0);
}
