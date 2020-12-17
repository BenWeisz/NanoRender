#ifndef GEO_H
#define GEO_H

class Vec3f {
    public:
        float m_v1, m_v2, m_v3;
        Vec3f(const float &v1, const float &v2, const float &v3);
        Vec3f() : m_v1(.0f), m_v2(.0f), m_v3(.0f) {};
};

#endif // GEO_H