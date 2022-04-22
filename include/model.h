#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "geometry.h"

class Face {
   public:
    Vec3f m_Data[3];
    int m_texture_id;
    Face(const Vec3f v1, const Vec3f v2, const Vec3f v3);
    Face(const Vec3f v1, const Vec3f v2, const Vec3f v3, int texture_id);
    Vec3f operator[](int i) const;
};

class TextureFace {
   public:
    Vec2f m_Data[3];
    TextureFace(const Vec2f v1, const Vec2f v2, const Vec2f v3e);
    Vec2f operator[](int i) const;
};

class Model {
   public:
    std::vector<Face> m_faces;
    std::vector<TextureFace> m_texture_faces;
    void loadModel(const std::string &file_name, const bool load_textures);
};

#endif  // MODEL_H