#include "geometry.h"

int barycentric_coords(Vec3f *points, const Vec3f &query, Vec3f &out) {
    const float d11 = points[1][1] - points[2][1];
    const float d21 = points[2][1] - points[0][1];
    const float d31 = points[0][1] - points[1][1];

    const float det_A = (points[0][0] * d11) + (points[1][0] * d21) + (points[2][0] * d31);
    if (det_A == 0)
        return -1;

    const float d12 = points[2][0] - points[1][0];
    const float d22 = points[0][0] - points[2][0];
    const float d32 = points[1][0] - points[0][0];

    const float d13 = (points[1][0] * points[2][1]) - (points[2][0] * points[1][1]);
    const float d23 = (points[2][0] * points[0][1]) - (points[0][0] * points[2][1]);
    const float d33 = (points[0][0] * points[1][1]) - (points[1][0] * points[0][1]);

    const float c1 = ((d11 * query[0]) + (d12 * query[1]) + d13) / det_A;
    const float c2 = ((d21 * query[0]) + (d22 * query[1]) + d23) / det_A;
    const float c3 = ((d31 * query[0]) + (d32 * query[1]) + d33) / det_A;
    if (c1 < 0 || c2 < 0 || c3 < 0)
        return -1;

    out = Vec3f({c1, c2, c3});
    return 0;
}

Mat<float, 3, 3> rotation_z(float angle) {
    Mat<float, 3, 3> r = identity<3>();
    float cos_v = cos(angle);
    float sin_v = sin(angle);
    r.set(cos_v, 0, 0);
    r.set(-sin_v, 0, 1);
    r.set(sin_v, 1, 0);
    r.set(cos_v, 1, 1);
    return r;
}

Mat<float, 3, 3> rotation_x(float angle) {
    Mat<float, 3, 3> r = identity<3>();
    float cos_v = cos(angle);
    float sin_v = sin(angle);
    r.set(cos_v, 1, 1);
    r.set(-sin_v, 1, 2);
    r.set(sin_v, 2, 1);
    r.set(cos_v, 2, 2);
    return r;
}

Mat<float, 4, 4> get_3d_camera_model(float c) {
    Mat<float, 4, 4> r = identity<4>();
    r.set(-1 / c, 3, 2);
    return r;
}
