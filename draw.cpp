#include <cmath>
#include <cstdio>
#include <algorithm>

#include "draw.h"
#include "timage.h"
#include "geometry.h"

void line(int x0, int y0, int x1, int y1, TImage &image, const TColour &color) {
    bool steep = false;

    if (std::abs(x1 - x0) < std::abs(y1 - y0)) {
        steep = true;
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    float dx = x1 - x0;
    float dy = y1 - y0;
    float delta_err = std::abs(dy / dx);

    float err = 0.0;
    int y = y0;

    if (steep) {
        for (int x = x0; x <= x1; x++) {
            image.setPixel(y, x, color);
            err += delta_err;
            if (err >= 0.5) {
                y += (y0 > y1 ? -1 : 1);
                err -= 1;
            }
        }
    }
    else {
        for (int x = x0; x <= x1; x++) {
            image.setPixel(x, y, color);
            err += delta_err;
            if (err >= 0.5) {
                y += (y0 > y1 ? -1 : 1);
                err -= 1;
            }
        }
    }
}

void line2d(const Vec2f &v1, const Vec2f &v2, TImage &image, const TColour &color) {
    line(v1[0], v1[1], v2[0], v2[1], image, color);
}

void flat_triangle(Vec2f &v1, Vec2f &v2, Vec2f &v3, TImage &image, const TColour &color) {
    float max_x = std::max(v1[0], std::max(v2[0], v3[0]));
    float max_y = std::max(v1[1], std::max(v2[1], v3[1]));

    float min_x = std::min(v1[0], std::min(v2[0], v3[0]));
    float min_y = std::min(v1[1], std::min(v2[1], v3[1]));

    for (int y = (int)min_y; y <= (int)max_y; y++) {
        for (int x = (int)min_x; x <= (int)max_x; x++) {
            Vec2f p({(float)x, (float)y});

            if (point_is_in_triangle(v1, v2, v3, p)) {
                image.setPixel(p[0], p[1], color);
            }
        }
    }
}
