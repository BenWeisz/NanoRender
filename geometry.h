#ifndef GEO_H
#define GEO_H

#include <cstring>
#include <cassert>
#include <iostream>

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
        T operator[](int i) {
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
};

typedef Vec<float, 2> Vec2f;
typedef Vec<float, 3> Vec3f;

bool point_is_in_triangle(Vec2f &v1, Vec2f &v2, Vec2f &v3, Vec2f &p);

bool point_is_on_right_side(Vec2f &v1, Vec2f &v2, Vec2f &p);

#endif // GEO_H