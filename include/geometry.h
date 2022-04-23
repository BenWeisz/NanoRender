#ifndef GEO_H
#define GEO_H

#include <cassert>
#include <cmath>
#include <cstring>
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
    Vec operator*(float c) const {
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

#endif  // GEO_H