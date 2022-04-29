#include "model.h"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "geometry.h"

Face::Face(const Vec3f v1, const Vec3f v2, const Vec3f v3) {
    m_Data[0] = v1;
    m_Data[1] = v2;
    m_Data[2] = v3;
    m_texture_face_id = -1;
    m_normal_face_id = -1;
}

Face::Face(const Vec3f v1, const Vec3f v2, const Vec3f v3, const int texture_face_id, const int normal_face_id) {
    m_Data[0] = v1;
    m_Data[1] = v2;
    m_Data[2] = v3;
    m_texture_face_id = texture_face_id;
    m_normal_face_id = normal_face_id;
}

Vec3f Face::operator[](int i) const {
    return m_Data[i];
}

TextureFace::TextureFace(const Vec2f v1, const Vec2f v2, const Vec2f v3) {
    m_Data[0] = v1;
    m_Data[1] = v2;
    m_Data[2] = v3;
}

Vec2f TextureFace::operator[](int i) const {
    return m_Data[i];
}

NormalFace::NormalFace(const Vec3f v1, const Vec3f v2, const Vec3f v3) {
    m_Data[0] = v1;
    m_Data[1] = v2;
    m_Data[2] = v3;
}

Vec3f NormalFace::operator[](int i) const {
    return m_Data[i];
}

Model::~Model() {
    delete m_textures;
}

void Model::loadModel(const std::string &file_name, const bool load_textures, const bool load_normals) {
    std::ifstream in_file;
    in_file.open(file_name);

    if (in_file.fail()) {
        in_file.close();
        return;
    }

    std::vector<Vec3f> verts;
    std::vector<Vec2f> uv_coords;
    std::vector<Vec3f> normals;

    std::string line;
    while (!in_file.eof()) {
        std::getline(in_file, line);
        std::istringstream iss(line.c_str());

        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;

            float d[3];
            iss >> d[0];
            iss >> d[1];
            iss >> d[2];
            Vec3f vert(d);
            verts.push_back(vert);
        } else if (load_textures && !line.compare(0, 2, "vt")) {
            iss >> trash >> trash;

            float u, v;
            iss >> u;
            iss >> v;
            Vec2f uv_coord({u, v});
            uv_coords.push_back(uv_coord);
        } else if (load_normals && !line.compare(0, 2, "vn")) {
            iss >> trash >> trash;

            float x, y, z;
            iss >> x;
            iss >> y;
            iss >> z;
            Vec3f normal_vec = {x, y, z};
            normals.push_back(normal_vec);
        } else if (!line.compare(0, 2, "f ")) {
            iss >> trash;
            int c, t, n, i = 0;
            Vec3f vs[3];
            Vec2f vt[3];
            Vec3f vn[3];

            while (iss >> c >> trash >> t >> trash >> n) {
                vs[i] = verts[--c];
                vt[i] = uv_coords[--t];
                vn[i] = normals[--n];
                i++;
            }

            int texture_face_id = -1;
            if (load_textures) {
                TextureFace t_face(vt[0], vt[1], vt[2]);
                texture_face_id = m_texture_faces.size();
                m_texture_faces.push_back(t_face);
            }
            int normal_face_id = -1;
            if (load_normals) {
                NormalFace n_face(vn[0], vn[1], vn[2]);
                normal_face_id = m_normal_faces.size();
                m_normal_faces.push_back(n_face);
            }

            Face face(vs[0], vs[1], vs[2], texture_face_id, normal_face_id);
            m_faces.push_back(face);
        }
    }
}

void Model::loadTextures(const std::string &file_name) {
    m_textures = new TImage(file_name);
}