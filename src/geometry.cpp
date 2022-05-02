#include "geometry.h"

int inverse_3d(const Mat33f &M, Mat33f &Minv) {
    const float d11 = (M.get(1, 1) * M.get(2, 2)) - (M.get(1, 2) * M.get(2, 1));
    const float d21 = (M.get(1, 2) * M.get(2, 0)) - (M.get(1, 0) * M.get(2, 2));
    const float d31 = (M.get(1, 0) * M.get(2, 1)) - (M.get(1, 1) * M.get(2, 0));

    const float det_A = (M.get(0, 0) * d11) + (M.get(0, 1) * d21) + (M.get(0, 2) * d31);
    if (det_A == 0)
        return -1;

    const float d12 = (M.get(0, 2) * M.get(2, 1)) - (M.get(0, 1) * M.get(2, 2));
    const float d22 = (M.get(0, 0) * M.get(2, 2)) - (M.get(0, 2) * M.get(2, 0));
    const float d32 = (M.get(0, 1) * M.get(2, 0)) - (M.get(0, 0) * M.get(2, 1));

    const float d13 = (M.get(0, 1) * M.get(1, 2)) - (M.get(0, 2) * M.get(1, 1));
    const float d23 = (M.get(0, 2) * M.get(1, 0)) - (M.get(0, 0) * M.get(1, 2));
    const float d33 = (M.get(0, 0) * M.get(1, 1)) - (M.get(0, 1) * M.get(1, 0));

    Minv.set(d11, 0, 0);
    Minv.set(d12, 0, 1);
    Minv.set(d13, 0, 2);
    Minv.set(d21, 1, 0);
    Minv.set(d22, 1, 1);
    Minv.set(d23, 1, 2);
    Minv.set(d31, 2, 0);
    Minv.set(d32, 2, 1);
    Minv.set(d33, 2, 2);

    Minv = Minv * (1.0 / det_A);
    return 0;
}

int inverse_4d(const Mat44f &M, Mat44f &Minv) {
    float
        det_A =
            (M.get(0, 3) * M.get(1, 2) * M.get(2, 1) * M.get(3, 0)) - (M.get(0, 2) * M.get(1, 3) * M.get(2, 1) * M.get(3, 0)) - (M.get(0, 3) * M.get(1, 1) * M.get(2, 2) * M.get(3, 0)) + (M.get(0, 1) * M.get(1, 3) * M.get(2, 2) * M.get(3, 0)) +
            (M.get(0, 2) * M.get(1, 1) * M.get(2, 3) * M.get(3, 0)) - (M.get(0, 1) * M.get(1, 2) * M.get(2, 3) * M.get(3, 0)) - (M.get(0, 3) * M.get(1, 2) * M.get(2, 0) * M.get(3, 1)) + (M.get(0, 2) * M.get(1, 3) * M.get(2, 0) * M.get(3, 1)) +
            (M.get(0, 3) * M.get(1, 0) * M.get(2, 2) * M.get(3, 1)) - (M.get(0, 0) * M.get(1, 3) * M.get(2, 2) * M.get(3, 1)) - (M.get(0, 2) * M.get(1, 0) * M.get(2, 3) * M.get(3, 1)) + (M.get(0, 0) * M.get(1, 2) * M.get(2, 3) * M.get(3, 1)) +
            (M.get(0, 3) * M.get(1, 1) * M.get(2, 0) * M.get(3, 2)) - (M.get(0, 1) * M.get(1, 3) * M.get(2, 0) * M.get(3, 2)) - (M.get(0, 3) * M.get(1, 0) * M.get(2, 1) * M.get(3, 2)) + (M.get(0, 0) * M.get(1, 3) * M.get(2, 1) * M.get(3, 2)) +
            (M.get(0, 1) * M.get(1, 0) * M.get(2, 3) * M.get(3, 2)) - (M.get(0, 0) * M.get(1, 1) * M.get(2, 3) * M.get(3, 2)) - (M.get(0, 2) * M.get(1, 1) * M.get(2, 0) * M.get(3, 3)) + (M.get(0, 1) * M.get(1, 2) * M.get(2, 0) * M.get(3, 3)) +
            (M.get(0, 2) * M.get(1, 0) * M.get(2, 1) * M.get(3, 3)) - (M.get(0, 0) * M.get(1, 2) * M.get(2, 1) * M.get(3, 3)) - (M.get(0, 1) * M.get(1, 0) * M.get(2, 2) * M.get(3, 3)) + (M.get(0, 0) * M.get(1, 1) * M.get(2, 2) * M.get(3, 3));

    if (det_A == 0)
        return -1;

    Minv.set((M.get(1, 2) * M.get(2, 3) * M.get(3, 1)) - (M.get(1, 3) * M.get(2, 2) * M.get(3, 1)) + (M.get(1, 3) * M.get(2, 1) * M.get(3, 2)) - (M.get(1, 1) * M.get(2, 3) * M.get(3, 2)) - (M.get(1, 2) * M.get(2, 1) * M.get(3, 3)) + (M.get(1, 1) * M.get(2, 2) * M.get(3, 3)), 0, 0);
    Minv.set((M.get(0, 3) * M.get(2, 2) * M.get(3, 1)) - (M.get(0, 2) * M.get(2, 3) * M.get(3, 1)) - (M.get(0, 3) * M.get(2, 1) * M.get(3, 2)) + (M.get(0, 1) * M.get(2, 3) * M.get(3, 2)) + (M.get(0, 2) * M.get(2, 1) * M.get(3, 3)) - (M.get(0, 1) * M.get(2, 2) * M.get(3, 3)), 0, 1);
    Minv.set((M.get(0, 2) * M.get(1, 3) * M.get(3, 1)) - (M.get(0, 3) * M.get(1, 2) * M.get(3, 1)) + (M.get(0, 3) * M.get(1, 1) * M.get(3, 2)) - (M.get(0, 1) * M.get(1, 3) * M.get(3, 2)) - (M.get(0, 2) * M.get(1, 1) * M.get(3, 3)) + (M.get(0, 1) * M.get(1, 2) * M.get(3, 3)), 0, 2);
    Minv.set((M.get(0, 3) * M.get(1, 2) * M.get(2, 1)) - (M.get(0, 2) * M.get(1, 3) * M.get(2, 1)) - (M.get(0, 3) * M.get(1, 1) * M.get(2, 2)) + (M.get(0, 1) * M.get(1, 3) * M.get(2, 2)) + (M.get(0, 2) * M.get(1, 1) * M.get(2, 3)) - (M.get(0, 1) * M.get(1, 2) * M.get(2, 3)), 0, 3);
    Minv.set((M.get(1, 3) * M.get(2, 2) * M.get(3, 0)) - (M.get(1, 2) * M.get(2, 3) * M.get(3, 0)) - (M.get(1, 3) * M.get(2, 0) * M.get(3, 2)) + (M.get(1, 0) * M.get(2, 3) * M.get(3, 2)) + (M.get(1, 2) * M.get(2, 0) * M.get(3, 3)) - (M.get(1, 0) * M.get(2, 2) * M.get(3, 3)), 1, 0);
    Minv.set((M.get(0, 2) * M.get(2, 3) * M.get(3, 0)) - (M.get(0, 3) * M.get(2, 2) * M.get(3, 0)) + (M.get(0, 3) * M.get(2, 0) * M.get(3, 2)) - (M.get(0, 0) * M.get(2, 3) * M.get(3, 2)) - (M.get(0, 2) * M.get(2, 0) * M.get(3, 3)) + (M.get(0, 0) * M.get(2, 2) * M.get(3, 3)), 1, 1);
    Minv.set((M.get(0, 3) * M.get(1, 2) * M.get(3, 0)) - (M.get(0, 2) * M.get(1, 3) * M.get(3, 0)) - (M.get(0, 3) * M.get(1, 0) * M.get(3, 2)) + (M.get(0, 0) * M.get(1, 3) * M.get(3, 2)) + (M.get(0, 2) * M.get(1, 0) * M.get(3, 3)) - (M.get(0, 0) * M.get(1, 2) * M.get(3, 3)), 1, 2);
    Minv.set((M.get(0, 2) * M.get(1, 3) * M.get(2, 0)) - (M.get(0, 3) * M.get(1, 2) * M.get(2, 0)) + (M.get(0, 3) * M.get(1, 0) * M.get(2, 2)) - (M.get(0, 0) * M.get(1, 3) * M.get(2, 2)) - (M.get(0, 2) * M.get(1, 0) * M.get(2, 3)) + (M.get(0, 0) * M.get(1, 2) * M.get(2, 3)), 1, 3);
    Minv.set((M.get(1, 1) * M.get(2, 3) * M.get(3, 0)) - (M.get(1, 3) * M.get(2, 1) * M.get(3, 0)) + (M.get(1, 3) * M.get(2, 0) * M.get(3, 1)) - (M.get(1, 0) * M.get(2, 3) * M.get(3, 1)) - (M.get(1, 1) * M.get(2, 0) * M.get(3, 3)) + (M.get(1, 0) * M.get(2, 1) * M.get(3, 3)), 2, 0);
    Minv.set((M.get(0, 3) * M.get(2, 1) * M.get(3, 0)) - (M.get(0, 1) * M.get(2, 3) * M.get(3, 0)) - (M.get(0, 3) * M.get(2, 0) * M.get(3, 1)) + (M.get(0, 0) * M.get(2, 3) * M.get(3, 1)) + (M.get(0, 1) * M.get(2, 0) * M.get(3, 3)) - (M.get(0, 0) * M.get(2, 1) * M.get(3, 3)), 2, 1);
    Minv.set((M.get(0, 1) * M.get(1, 3) * M.get(3, 0)) - (M.get(0, 3) * M.get(1, 1) * M.get(3, 0)) + (M.get(0, 3) * M.get(1, 0) * M.get(3, 1)) - (M.get(0, 0) * M.get(1, 3) * M.get(3, 1)) - (M.get(0, 1) * M.get(1, 0) * M.get(3, 3)) + (M.get(0, 0) * M.get(1, 1) * M.get(3, 3)), 2, 2);
    Minv.set((M.get(0, 3) * M.get(1, 1) * M.get(2, 0)) - (M.get(0, 1) * M.get(1, 3) * M.get(2, 0)) - (M.get(0, 3) * M.get(1, 0) * M.get(2, 1)) + (M.get(0, 0) * M.get(1, 3) * M.get(2, 1)) + (M.get(0, 1) * M.get(1, 0) * M.get(2, 3)) - (M.get(0, 0) * M.get(1, 1) * M.get(2, 3)), 2, 3);
    Minv.set((M.get(1, 2) * M.get(2, 1) * M.get(3, 0)) - (M.get(1, 1) * M.get(2, 2) * M.get(3, 0)) - (M.get(1, 2) * M.get(2, 0) * M.get(3, 1)) + (M.get(1, 0) * M.get(2, 2) * M.get(3, 1)) + (M.get(1, 1) * M.get(2, 0) * M.get(3, 2)) - (M.get(1, 0) * M.get(2, 1) * M.get(3, 2)), 3, 0);
    Minv.set((M.get(0, 1) * M.get(2, 2) * M.get(3, 0)) - (M.get(0, 2) * M.get(2, 1) * M.get(3, 0)) + (M.get(0, 2) * M.get(2, 0) * M.get(3, 1)) - (M.get(0, 0) * M.get(2, 2) * M.get(3, 1)) - (M.get(0, 1) * M.get(2, 0) * M.get(3, 2)) + (M.get(0, 0) * M.get(2, 1) * M.get(3, 2)), 3, 1);
    Minv.set((M.get(0, 2) * M.get(1, 1) * M.get(3, 0)) - (M.get(0, 1) * M.get(1, 2) * M.get(3, 0)) - (M.get(0, 2) * M.get(1, 0) * M.get(3, 1)) + (M.get(0, 0) * M.get(1, 2) * M.get(3, 1)) + (M.get(0, 1) * M.get(1, 0) * M.get(3, 2)) - (M.get(0, 0) * M.get(1, 1) * M.get(3, 2)), 3, 2);
    Minv.set((M.get(0, 1) * M.get(1, 2) * M.get(2, 0)) - (M.get(0, 2) * M.get(1, 1) * M.get(2, 0)) + (M.get(0, 2) * M.get(1, 0) * M.get(2, 1)) - (M.get(0, 0) * M.get(1, 2) * M.get(2, 1)) - (M.get(0, 1) * M.get(1, 0) * M.get(2, 2)) + (M.get(0, 0) * M.get(1, 1) * M.get(2, 2)), 3, 3);

    Minv = Minv * (1 / det_A);

    return 0;
}

int barycentric_coords(Vec3f *points, const Vec3f &query, Vec3f &out) {
    Mat33f M;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            M.set(points[j][i], i, j);
        }
    }
    for (int j = 0; j < 3; j++) {
        M.set(1, 2, j);
    }

    Mat33f Minv;
    int r = inverse_3d(M, Minv);
    if (r != 0)
        return -1;

    out = Minv.dot(query);
    if (out[0] < 0 || out[1] < 0 || out[2] < 0) return -1;

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