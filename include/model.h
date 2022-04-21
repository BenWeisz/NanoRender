#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "geometry.h"

class Face {
    public:
        Vec3f m_Data[3];
        Face(const Vec3f v1, const Vec3f v2, const Vec3f v3);
        Vec3f operator[](int i) const;
};

class Model {
    public:
        void loadModel(const std::string &file_name);
        std::vector<Face> m_faces;
};

#endif // MODEL_H