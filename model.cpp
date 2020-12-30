#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "geometry.h"
#include "model.h"

Face::Face(const Vec3f v1, const Vec3f v2, const Vec3f v3) {
    m_v1 = v1;
    m_v2 = v2;
    m_v3 = v3;
}

void Model::loadModel(const std::string &file_name) {
    std::ifstream in_file;
    in_file.open(file_name);

    if (in_file.fail()) {
        std::cout << "Failed to read the file: " << file_name << std::endl;
        in_file.close();
        return;
    }

    std::vector<Vec3f> verts;

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
        }
        else if (!line.compare(0, 2, "f ")) {
            iss >> trash;
            int c, t, n, i = 0;
            Vec3f vs[3];

            while (iss >> c >> trash >> t >> trash >> n) {
                vs[i++] = verts[--c];
            }

            Face face(vs[0], vs[1], vs[2]);
            m_faces.push_back(face);
        }
    }
}