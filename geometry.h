#ifndef GEO_H
#define GEO_H

class Vec3f {
    public:
        float m_v1, m_v2, m_v3;
        Vec3f(const float &v1, const float &v2, const float &v3);
        Vec3f() : m_v1(.0f), m_v2(.0f), m_v3(.0f) {};
};

class Vec2f {
    public:
        float m_v1, m_v2;
        Vec2f(const float &v1, const float &v2);
        Vec2f() : m_v1(.0f), m_v2(.0f) {};
        Vec2f operator-(const Vec2f &o);
        float dydx();
};

bool point_is_in_triangle(Vec2f &v1, Vec2f &v2, Vec2f &v3, Vec2f &p);

bool point_is_on_right_side(Vec2f &v1, Vec2f &v2, Vec2f &p);

#endif // GEO_H