#include "geometry.h"

#include <algorithm>
#include <iostream>

int barycentric_coords(Vec3f *points, Vec3f &query, Vec3f &out) {
    float d11 = points[1][1] - points[2][1];
    float d21 = points[2][1] - points[0][1];
    float d31 = points[0][1] - points[1][1];

    float det_A = (points[0][0] * d11) + (points[1][0] * d21) + (points[2][0] * d31);
    if (det_A == 0)
        return -1;

    float d12 = points[2][0] - points[1][0];
    float d22 = points[0][0] - points[2][0];
    float d32 = points[1][0] - points[0][0];

    float d13 = (points[1][0] * points[2][1]) - (points[2][0] * points[1][1]);
    float d23 = (points[2][0] * points[0][1]) - (points[0][0] * points[2][1]);
    float d33 = (points[0][0] * points[1][1]) - (points[1][0] * points[0][1]);

    float c1 = ((d11 * query[0]) + (d12 * query[1]) + d13) / det_A;
    float c2 = ((d21 * query[0]) + (d22 * query[1]) + d23) / det_A;
    float c3 = ((d31 * query[0]) + (d32 * query[1]) + d33) / det_A;
    if (c1 < 0 || c2 < 0 || c3 < 0)
        return -1;

    out = Vec3f({c1, c2, c3});
    return 0;
}