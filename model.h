#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "geometry.h"

class Face {
    public:
        Face(const Vec3f v1, const Vec3f v2, const Vec3f v3);
        Vec3f m_v1, m_v2, m_v3;
};

class Model {
    public:
        void loadModel(const std::string &file_name);
        std::vector<Face> m_faces;
};

#endif // MODEL_H