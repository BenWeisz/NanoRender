#include <iostream>

#include "timage.h"
#include "draw.h"
#include "model.h"
#include "geometry.h"

void draw_wireframe(const int width, const int height, const Model &model) {
    TImage image(width, height);
    
    for (int i = 0; i < model.m_faces.size(); i++) {
        Vec3f v1 = model.m_faces.at(i)[0];
        Vec3f v2 = model.m_faces.at(i)[1];
        Vec3f v3 = model.m_faces.at(i)[2];    

        int hw = width / 2;
        int hh = height / 2;

        Vec2f mapped_v1({(v1[0] * hw) + hw, (v1[1] * hh) + hh});
        Vec2f mapped_v2({(v2[0] * hw) + hw, (v2[1] * hh) + hh});
        Vec2f mapped_v3({(v3[0] * hw) + hw, (v3[1] * hh) + hh});

        TColour white(255, 255, 255);

        line2d(mapped_v1, mapped_v2, image, white);
        line2d(mapped_v2, mapped_v3, image, white);
        line2d(mapped_v3, mapped_v1, image, white);
    }

    image.write("./out/wireframe.tga");
}

void draw_red_flat_triangles(const int width, const int height, const Model &model) {
    TImage image(width, height);
    
    for (int i = 0; i < model.m_faces.size(); i++) {
        Vec3f v1 = model.m_faces.at(i)[0];
        Vec3f v2 = model.m_faces.at(i)[1];
        Vec3f v3 = model.m_faces.at(i)[2];    

        int hw = width / 2;
        int hh = height / 2;

        Vec2f mapped_v1({(v1[0] * hw) + hw, (v1[1] * hh) + hh});
        Vec2f mapped_v2({(v2[0] * hw) + hw, (v2[1] * hh) + hh});
        Vec2f mapped_v3({(v3[0] * hw) + hw, (v3[1] * hh) + hh});

        flat_triangle(mapped_v1, mapped_v2, mapped_v3, image, TColour((int)((mapped_v1[1] / height) * 255), 0, 0));
    }

    image.write("./out/flat_red.tga");
}

void draw_normal_inensity_mapped_triangles(const int width, const int height, const Model &model) {
    TImage image(width, height);
    
    Vec3f lighting_dir({0.0, 0.0, 1.0});
    lighting_dir = lighting_dir.norm();

    for (int i = 0; i < model.m_faces.size(); i++) {
        Vec3f v1 = model.m_faces.at(i)[0];
        Vec3f v2 = model.m_faces.at(i)[1];
        Vec3f v3 = model.m_faces.at(i)[2];    

        // Light Intensity Computations
        Vec3f v1v2 = v2 - v1;
        Vec3f v1v3 = v3 - v1;
        Vec3f normal = v1v2.cross(v1v3);
        normal = normal.norm();

        float light_intensity = normal.dot(lighting_dir);

        if (light_intensity > 0) {
            int light_level = (int)(light_intensity * 255);

            // Rendering
            int hw = width / 2;
            int hh = height / 2;

            Vec2f mapped_v1({(v1[0] * hw) + hw, (v1[1] * hh) + hh});
            Vec2f mapped_v2({(v2[0] * hw) + hw, (v2[1] * hh) + hh});
            Vec2f mapped_v3({(v3[0] * hw) + hw, (v3[1] * hh) + hh});

            flat_triangle(mapped_v1, mapped_v2, mapped_v3, image, TColour(light_level, light_level, light_level));
        }
    }

    image.write("./out/intensity_mapped.tga");
}

int main() {
    Model m;
    m.loadModel("./obj/african_head.obj");

    draw_red_flat_triangles(500, 500, m);
    draw_normal_inensity_mapped_triangles(1000, 1000, m);
    draw_wireframe(500, 500, m);
}
