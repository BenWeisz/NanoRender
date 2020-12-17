#include <iostream>

#include "timage.h"
#include "draw.h"
#include "model.h"
#include "geometry.h"

int main() {
    int width = 500, height = 500;
    TImage image(width, height);

    //TColour red(255, 0, 0);
    TColour white(255, 255, 255);

    //line(50, 50, 50, 100, image, red);

    Model m;
    m.loadModel("./obj/african_head.obj");

    for (int i = 0; i < m.m_faces.size(); i++) {
        Vec3f v1 = m.m_faces.at(i).m_v1;
        Vec3f v2 = m.m_faces.at(i).m_v2;
        Vec3f v3 = m.m_faces.at(i).m_v3;    

        int hw = width / 2;
        int hh = height / 2;

        line((int)((v1.m_v1 * hw) + hw), (int)((v1.m_v2 * hh) + hh), (int)((v2.m_v1 * hw) + hw), (int)((v2.m_v2 * hh) + hh), image, white);
        line((int)((v2.m_v1 * hw) + hw), (int)((v2.m_v2 * hh) + hh), (int)((v3.m_v1 * hw) + hw), (int)((v3.m_v2 * hh) + hh), image, white);
        line((int)((v3.m_v1 * hw) + hw), (int)((v3.m_v2 * hh) + hh), (int)((v1.m_v1 * hw) + hw), (int)((v1.m_v2 * hh) + hh), image, white);
    }

    image.write("./out/test.tga");
}