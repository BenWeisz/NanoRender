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

Mat33f rotation_z(const float angle) {
    Mat33f r = identity<3>();
    float cos_v = cos(angle);
    float sin_v = sin(angle);
    r.set(cos_v, 0, 0);
    r.set(-sin_v, 0, 1);
    r.set(sin_v, 1, 0);
    r.set(cos_v, 1, 1);
    return r;
}

Mat33f rotation_x(const float angle) {
    Mat33f r = identity<3>();
    float cos_v = cos(angle);
    float sin_v = sin(angle);
    r.set(cos_v, 1, 1);
    r.set(-sin_v, 1, 2);
    r.set(sin_v, 2, 1);
    r.set(cos_v, 2, 2);
    return r;
}

Mat44f get_projection_mat(const float c) {
    Mat44f r = identity<4>();
    r.set(-1 / c, 3, 2);
    return r;
}

Mat44f get_viewport_mat(const int x, const int y, const int width, const int height, const int depth) {
    Mat44f r = identity<4>();
    r.set(width / 2.0, 0, 0);
    r.set(height / 2.0, 1, 1);
    r.set(depth / 2.0, 2, 2);
    r.set(depth / 2.0, 2, 3);
    r.set(x + (width / 2.0), 0, 3);
    r.set(y + (height / 2.0), 1, 3);

    return r;
}

Mat44f get_view_mat(const Vec3f eye, const Vec3f center, const Vec3f up) {
    Vec3f z = (eye - center).norm();
    Vec3f x = up.cross(z).norm();
    Vec3f y = z.cross(x).norm();

    Mat44f Minv = identity<4>();
    Mat44f tr = identity<4>();
    for (int i = 0; i < 3; i++) {
        Minv.set(x[i], 0, i);
        Minv.set(y[i], 1, i);
        Minv.set(z[i], 2, i);
        tr.set(-eye[i], i, 3);
    }

    return Minv.mul<4, 4>(tr);
}