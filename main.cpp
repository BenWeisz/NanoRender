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

        Vec2f mapped_v1({(v1[0] * hw) + hw, (v1[1] * hh) + hh});
        Vec2f mapped_v2({(v2[0] * hw) + hw, (v2[1] * hh) + hh});
        Vec2f mapped_v3({(v3[0] * hw) + hw, (v3[1] * hh) + hh});

        line(mapped_v1[0], mapped_v1[1], mapped_v2[0], mapped_v2[1], image, TColour(255, 255, 255));
        line(mapped_v2[0], mapped_v2[1], mapped_v3[0], mapped_v3[1], image, TColour(255, 255, 255));
        line(mapped_v3[0], mapped_v3[1], mapped_v1[0], mapped_v1[1], image, TColour(255, 255, 255));
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

        Vec2f mapped_v1({(v1[0] * hw) + hw, (v1[1] * hh) + hh});
        Vec2f mapped_v2({(v2[0] * hw) + hw, (v2[1] * hh) + hh});
        Vec2f mapped_v3({(v3[0] * hw) + hw, (v3[1] * hh) + hh});

        triangle(mapped_v1, mapped_v2, mapped_v3, image, TColour((int)((mapped_v1[1] / height) * 255), 0, 0));
    }

    image.write("./out/flat_red.tga");
}

/*
    Refactors to work on

    1) Consolidate Vec2f + Vec3f into templated system
    2) Rename triangle function to flat_triangle
    3) Rework model / add function to remap verticies to screen coords based on width / height
    4) Rework model so that it supports indexing for the verticies
*/

int main() {
    Model m;
    m.loadModel("./obj/african_head.obj");

    draw_red_flat_triangles(500, 500, m);
    draw_wireframe(500, 500, m);
}