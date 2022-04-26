#ifndef GEO_H
#define GEO_H

#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <type_traits>

template <typename T, size_t N>
class Vec {
   public:
    T m_Data[N];
    Vec() { memset(m_Data, 0, sizeof(T) * N); };
    Vec(T (&data)[N]) {
        for (int i = 0; i < N; i++) m_Data[i] = data[i];
    }
    Vec(std::initializer_list<T> data) {
        assert(data.size() == N);
        std::copy(data.begin(), data.end(), m_Data);
    }
    T operator[](const int i) {
        return m_Data[i];
    }
    T operator[](const int i) const {
        return m_Data[i];
    }
    Vec operator+(const Vec &other) const {
        Vec r;
        for (int i = 0; i < N; i++) r.m_Data[i] = m_Data[i] + other.m_Data[i];
        return r;
    }
    Vec operator-(const Vec &other) const {
        Vec r;
        for (int i = 0; i < N; i++) r.m_Data[i] = m_Data[i] - other.m_Data[i];
        return r;
    }
    Vec operator*(T c) const {
        Vec r;
        for (int i = 0; i < N; i++) r.m_Data[i] = m_Data[i] * c;
        return r;
    }
    bool is_numeric() const {
        return std::is_same<T, float>::value || std::is_same<T, double>::value;
    }
    T magnitude() {
        assert(is_numeric());

        T squared_sum = 0.0;
        for (int i = 0; i < N; i++) squared_sum += m_Data[i] * m_Data[i];

        return std::sqrt(squared_sum);
    }
    Vec norm() {
        assert(is_numeric());

        T mag = magnitude();
        return (*this) * (1.0 / mag);
    }
    Vec cross(const Vec &other) const {
        assert(is_numeric());
        assert(N == 3);

        Vec r;
        r.m_Data[0] = m_Data[1] * other.m_Data[2] - other.m_Data[1] * m_Data[2];
        r.m_Data[1] = m_Data[2] * other.m_Data[0] - other.m_Data[2] * m_Data[0];
        r.m_Data[2] = m_Data[0] * other.m_Data[1] - other.m_Data[0] * m_Data[1];

        return r;
    }
    T dot(const Vec &other) {
        assert(is_numeric());
        T dot_product = 0.0;
        for (int i = 0; i < N; i++) dot_product += m_Data[i] * other.m_Data[i];

        return dot_product;
    }
    friend std::ostream &operator<<(std::ostream &os, const Vec &v) {
        os << "(";
        for (int i = 0; i < N; i++) {
            os << v[i];
            if (i < N - 1)
                os << ", ";
        }
        os << ")";
        return os;
    }
};

typedef Vec<float, 2> Vec2f;
typedef Vec<float, 3> Vec3f;
typedef Vec<float, 4> Vec4f;
template <typename T, size_t N, size_t M>
class Mat {
   public:
    T m_Data[M * N];
    Mat() { memset(m_Data, 0, sizeof(T) * M * N); };
    Mat(T (&data)[M * N]) {
        for (int i = 0; i < M * N; i++) m_Data[i] = data[i];
    }
    Mat(std::initializer_list<T> data) {
        assert(data.size() == M * N);
        std::copy(data.begin(), data.end(), m_Data);
    }
    T get(const int i, const int j) {
        assert(i < M && j < N);
        return m_Data[(i * N) + j];
    }
    T get(const int i, const int j) const {
        assert(i < M && j < N);
        return m_Data[(i * N) + j];
    }
    void set(const T v, const int i, const int j) {
        assert(i < M && j < N);
        m_Data[(i * N) + j] = v;
    }
    Mat operator+(const Mat &other) const {
        assert(is_numeric());
        assert(other.is_numeric());
        Mat r;
        for (int i = 0; i < M * N; i++) r.m_Data[i] = m_Data[i] + other.m_Data[i];
        return r;
    }
    Mat operator-(const Mat &other) const {
        assert(is_numeric());
        assert(other.is_numeric());
        Mat r;
        for (int i = 0; i < M * N; i++) r.m_Data[i] = m_Data[i] - other.m_Data[i];
        return r;
    }
    Mat operator*(const Mat &other) const {
        assert(is_numeric());
        assert(other.is_numeric());
        Mat r;
        for (int i = 0; i < M * N; i++) r.m_Data[i] = m_Data[i] * other.m_Data[i];
        return r;
    }
    Mat operator*(const T c) const {
        assert(is_numeric());
        Mat r;
        for (int i = 0; i < M * N; i++) r.m_Data[i] = m_Data[i] * c;
        return r;
    }
    template <size_t oM, size_t oN>
    Mat mul(const Mat &other) {
        assert(is_numeric());
        assert(other.is_numeric());
        Mat<T, M, oN> r;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < oN; j++) {
                T total = 0;
                for (int k = 0; k < N; k++) {
                    total += get(i, k) * other.get(k, j);
                }
                r.set(total, i, j);
            }
        }
        return r;
    }
    Vec<T, M> dot(const Vec<T, M> &v) {
        assert(is_numeric());
        assert(v.is_numeric());
        T vals[M];
        for (int i = 0; i < M; i++) {
            T total = 0.0;
            for (int j = 0; j < N; j++) {
                total += get(i, j) * v[j];
            }
            vals[i] = total;
        }

        Vec<T, M> r(vals);
        return r;
    }
    bool is_numeric() const {
        return std::is_same<T, float>::value || std::is_same<T, double>::value;
    }
    friend std::ostream &operator<<(std::ostream &os, const Mat &v) {
        std::streamsize old_precision = os.precision(3);
        os << std::fixed << std::showpoint;
        os << std::setprecision(3);

        for (int i = 0; i < M; i++) {
            os << "|";
            for (int j = 0; j < N; j++) {
                os << " " << v.get(i, j);
            }
            os << " |\n";
        }

        os << std::setprecision(old_precision);

        return os;
    }
};

typedef Mat<float, 3, 3> Mat33f;
typedef Mat<float, 4, 4> Mat44f;

template <class T>
bool point_is_in_triangle(const T &v1, const T &v2, const T &v3, const T &p) {
    // This code would be dependent on the rotational order of v1, v2, v3.
    // But as long as we define vec_1, vec_2, vec_3 to be vectors in a 3-cycle
    // the booleans only need be the same value.
    const bool v1_side = point_is_on_right_side(v1, v2, p);
    const bool v2_side = point_is_on_right_side(v2, v3, p);
    const bool v3_side = point_is_on_right_side(v3, v1, p);

    return v1_side == v2_side && v2_side == v3_side;
}

template <class T>
bool point_is_on_right_side(const T &v1, const T &v2, const T &p) {
    const T dir = v2 - v1;
    const T mapped_p = p - v1;

    if (dir[0] == 0)
        return (mapped_p[0] >= 0) ^ (dir[1] < 0);

    const float dir_dydx = dir[1] / dir[0];
    return ((dir_dydx * mapped_p[0]) > mapped_p[1]) ^ (dir[0] * -1 >= 0);
}

int barycentric_coords(Vec3f *const points, const Vec3f &query, Vec3f &out);

template <size_t N>
Mat<float, N, N> identity() {
    Mat<float, N, N> r;
    for (int i = 0; i < N; i++)
        r.set(1.0, i, i);

    return r;
}

template <size_t N>
Vec<float, N + 1> to_homogeneous(const Vec<float, N> &vec) {
    float vals[N + 1];
    vals[N] = 1.0;

    for (int i = 0; i < N; i++) {
        vals[i] = vec[i];
    }

    Vec<float, N + 1> homo_vec(vals);
    return homo_vec;
}

template <size_t N>
Mat<float, N + 1, N + 1> to_homogeneous(const Mat<float, N, N> &mat) {
    Mat<float, N + 1, N + 1> r = identity<N + 1>();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            r.set(mat.get(i, j), i, j);
        }
    }
    return r;
}

template <size_t N>
Vec<float, N - 1> to_cartesian(const Vec<float, N> &vec) {
    float vals[N - 1];
    for (int i = 0; i < N - 1; i++)
        vals[i] = vec[i];

    Vec<float, N - 1> cart_vec(vals);
    cart_vec = cart_vec * (1 / vec[N - 1]);
    return cart_vec;
}

Mat33f rotation_z(const float angle);
Mat33f rotation_x(const float angle);
Mat44f get_3d_camera_model(const float c);

#endif  // GEO_H