#include <iostream>

#include "draw.h"
#include "geometry.h"
#include "model.h"
#include "timage.h"

TColour red = {255, 0, 0};
TColour green = {0, 255, 0};
TColour white = {255, 255, 255};

void draw_wireframe(const int width, const int height, const Model &model) {
    TImage image(width, height);

    for (int i = 0; i < model.m_faces.size(); i++) {
        const Vec3f v1 = model.m_faces.at(i)[0];
        const Vec3f v2 = model.m_faces.at(i)[1];
        const Vec3f v3 = model.m_faces.at(i)[2];

        const int hw = width / 2;
        const int hh = height / 2;

        const Vec2f mapped_v1({(v1[0] * hw) + hw, (v1[1] * hh) + hh});
        const Vec2f mapped_v2({(v2[0] * hw) + hw, (v2[1] * hh) + hh});
        const Vec2f mapped_v3({(v3[0] * hw) + hw, (v3[1] * hh) + hh});

        const TColour white(255, 255, 255);

        line2d(mapped_v1, mapped_v2, image, white);
        line2d(mapped_v2, mapped_v3, image, white);
        line2d(mapped_v3, mapped_v1, image, white);
    }

    image.write("./out/wireframe.tga");
}

void draw_red_flat_triangles(const int width, const int height, const Model &model) {
    TImage image(width, height);

    for (int i = 0; i < model.m_faces.size(); i++) {
        const Vec3f v1 = model.m_faces.at(i)[0];
        const Vec3f v2 = model.m_faces.at(i)[1];
        const Vec3f v3 = model.m_faces.at(i)[2];

        const int hw = width / 2;
        const int hh = height / 2;

        const Vec2f mapped_v1({(v1[0] * hw) + hw, (v1[1] * hh) + hh});
        const Vec2f mapped_v2({(v2[0] * hw) + hw, (v2[1] * hh) + hh});
        const Vec2f mapped_v3({(v3[0] * hw) + hw, (v3[1] * hh) + hh});

        flat_triangle(mapped_v1, mapped_v2, mapped_v3, image, TColour((int)((mapped_v1[1] / height) * 255), 0, 0));
    }

    image.write("./out/flat_red.tga");
}

void draw_normal_inensity_mapped_triangles(const int width, const int height, Model &model) {
    TImage image(width, height);
    const TColour cream(240, 226, 182);
    image.setColour(cream);

    Vec3f lighting_dir({0.0, 0.0, 1.0});
    lighting_dir = lighting_dir.norm();

    int *const zbuffer = new int[width * height];
    for (int i = 0; i < width * height; i++)
        zbuffer[i] = INT_MAX;

    for (int i = 0; i < model.m_faces.size(); i++) {
        const Vec3f v1 = model.m_faces.at(i)[0];
        const Vec3f v2 = model.m_faces.at(i)[1];
        const Vec3f v3 = model.m_faces.at(i)[2];

        // Light Intensity Computations
        const Vec3f v1v2 = v2 - v1;
        const Vec3f v1v3 = v3 - v1;
        Vec3f normal = v1v2.cross(v1v3);
        normal = normal.norm();

        const float light_intensity = normal.dot(lighting_dir);

        if (light_intensity > 0) {
            const int light_level = (int)(light_intensity * 255);

            // Rendering
            const int hw = width / 2;
            const int hh = height / 2;

            const Vec3f mapped_v1({(v1[0] * hw) + hw, (v1[1] * hh) + hh, v1[2]});
            const Vec3f mapped_v2({(v2[0] * hw) + hw, (v2[1] * hh) + hh, v2[2]});
            const Vec3f mapped_v3({(v3[0] * hw) + hw, (v3[1] * hh) + hh, v3[2]});

            flat_triangle3(mapped_v1, mapped_v2, mapped_v3, image, TColour(light_level, light_level, light_level), zbuffer);
        }
    }

    free(zbuffer);
    image.write("./out/intensity_mapped.tga");
}

void draw_textured_model(const int width, const int height, Model &model) {
    TImage image(width, height);
    const TColour cream(240, 226, 182);
    image.setColour(cream);

    Vec3f lighting_dir({0.0, 0.0, 1.0});
    lighting_dir = lighting_dir.norm();

    int *zbuffer = new int[width * height];
    for (int i = 0; i < width * height; i++)
        zbuffer[i] = INT_MAX;

    for (int i = 0; i < model.m_faces.size(); i++) {
        const Face face = model.m_faces.at(i);
        const TextureFace t_face = model.m_texture_faces.at(face.m_texture_id);

        const Vec3f v1 = face[0];
        const Vec3f v2 = face[1];
        const Vec3f v3 = face[2];

        // Light Intensity Computations
        const Vec3f v1v2 = v2 - v1;
        const Vec3f v1v3 = v3 - v1;
        Vec3f normal = v1v2.cross(v1v3);
        normal = normal.norm();

        const float light_intensity = normal.dot(lighting_dir);

        if (light_intensity > 0) {
            // Rendering
            const int hw = width / 2;
            const int hh = height / 2;

            const Vec3f mapped_v1({(v1[0] * hw) + hw, (v1[1] * hh) + hh, v1[2]});
            const Vec3f mapped_v2({(v2[0] * hw) + hw, (v2[1] * hh) + hh, v2[2]});
            const Vec3f mapped_v3({(v3[0] * hw) + hw, (v3[1] * hh) + hh, v3[2]});

            textured_triangle(mapped_v1, mapped_v2, mapped_v3, light_intensity, image, zbuffer, t_face, model);
        }
    }

    free(zbuffer);
    image.write("./out/texture_mapped.tga");
}

int main() {
    Model m;
    m.loadModel("../models/african_head.obj", true);
    m.loadTextures("../models/african_head_diffuse.tga");

    draw_textured_model(500, 500, m);
    // draw_red_flat_triangles(500, 500, m);
    // draw_normal_inensity_mapped_triangles(500, 500, m);
    // draw_wireframe(500, 500, m);
}
