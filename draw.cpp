#include <cmath>
#include <cstdio>

#include "draw.h"
#include "timage.h"

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