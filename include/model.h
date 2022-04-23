#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "geometry.h"
#include "timage.h"

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
    ~Model();
    void loadModel(const std::string &file_name, const bool load_textures);
    void loadTextures(const std::string &file_name);
    TColour getTextureColour(const Vec2f *uv_coords, const Vec3f &bary_coords);
    std::vector<Face> m_faces;
    std::vector<TextureFace> m_texture_faces;
    TImage *m_textures;
};

inline TColour Model::getTextureColour(const Vec2f *uv_coords, const Vec3f &bary_coords) {
    const Vec2f uv = uv_coords[0] * bary_coords[0] + uv_coords[1] * bary_coords[1] + uv_coords[2] * bary_coords[2];
    const std::pair<std::uint16_t, std::uint16_t> dimensions = m_textures->get_dimensions();

    const std::uint16_t u = (std::uint16_t)(uv[0] * dimensions.first);
    const std::uint16_t v = (std::uint16_t)(uv[1] * dimensions.second);

    return m_textures->getColour(u, v);
}

#endif  // MODEL_H