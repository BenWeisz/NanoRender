#include <iostream>

#include "timage.h"
#include "draw.h"
#include "model.h"
#include "geometry.h"

void draw_wireframe(const int width, const int height, const Model &model) {
    TImage image(width, height);
    
    for (int i = 0; i < model.m_faces.size(); i++) {
        Vec3f v1 = model.m_faces.at(i).m_v1;
        Vec3f v2 = model.m_faces.at(i).m_v2;
        Vec3f v3 = model.m_faces.at(i).m_v3;    

        int hw = width / 2;
        int hh = height / 2;

        Vec2f mapped_v1((int)((v1.m_v1 * hw) + hw), (int)((v1.m_v2 * hh) + hh));
        Vec2f mapped_v2((int)((v2.m_v1 * hw) + hw), (int)((v2.m_v2 * hh) + hh));
        Vec2f mapped_v3((int)((v3.m_v1 * hw) + hw), (int)((v3.m_v2 * hh) + hh));

        line(mapped_v1.m_v1, mapped_v1.m_v2, mapped_v2.m_v1, mapped_v2.m_v2, image, TColour(255, 255, 255));
        line(mapped_v2.m_v1, mapped_v2.m_v2, mapped_v3.m_v1, mapped_v3.m_v2, image, TColour(255, 255, 255));
        line(mapped_v3.m_v1, mapped_v3.m_v2, mapped_v1.m_v1, mapped_v1.m_v2, image, TColour(255, 255, 255));
    }

    image.write("./out/wireframe.tga");
}

void draw_red_flat_triangles(const int width, const int height, const Model &model) {
    TImage image(width, height);
    
    for (int i = 0; i < model.m_faces.size(); i++) {
        Vec3f v1 = model.m_faces.at(i).m_v1;
        Vec3f v2 = model.m_faces.at(i).m_v2;
        Vec3f v3 = model.m_faces.at(i).m_v3;    

        int hw = width / 2;
        int hh = height / 2;

        Vec2f mapped_v1((int)((v1.m_v1 * hw) + hw), (int)((v1.m_v2 * hh) + hh));
        Vec2f mapped_v2((int)((v2.m_v1 * hw) + hw), (int)((v2.m_v2 * hh) + hh));
        Vec2f mapped_v3((int)((v3.m_v1 * hw) + hw), (int)((v3.m_v2 * hh) + hh));

        triangle(mapped_v1, mapped_v2, mapped_v3, image, TColour((int)((mapped_v1.m_v2 / height) * 255), 0, 0));
    }

    image.write("./out/flat_red.tga");
}

int main() {
    Model m;
    m.loadModel("./obj/african_head.obj");

    draw_red_flat_triangles(500, 500, m);
    draw_wireframe(500, 500, m);
}