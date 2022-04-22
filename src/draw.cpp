#include "draw.h"

#include "geometry.h"
#include "timage.h"

void line(int x0, int y0, int x1, int y1, TImage &image, const TColour &colour) {
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
            image.setPixel(y, x, colour);
            err += delta_err;
            if (err >= 0.5) {
                y += (y0 > y1 ? -1 : 1);
                err -= 1;
            }
        }
    } else {
        for (int x = x0; x <= x1; x++) {
            image.setPixel(x, y, colour);
            err += delta_err;
            if (err >= 0.5) {
                y += (y0 > y1 ? -1 : 1);
                err -= 1;
            }
        }
    }
}

void line2d(const Vec2f &v1, const Vec2f &v2, TImage &image, const TColour &colour) {
    line(v1[0], v1[1], v2[0], v2[1], image, colour);
}

void flat_triangle(Vec2f &v1, Vec2f &v2, Vec2f &v3, TImage &image, const TColour &colour) {
    float max_x = std::max(v1[0], std::max(v2[0], v3[0]));
    float max_y = std::max(v1[1], std::max(v2[1], v3[1]));

    float min_x = std::min(v1[0], std::min(v2[0], v3[0]));
    float min_y = std::min(v1[1], std::min(v2[1], v3[1]));

    for (int y = (int)min_y; y <= (int)max_y; y++) {
        for (int x = (int)min_x; x <= (int)max_x; x++) {
            Vec2f p({(float)x, (float)y});

            if (point_is_in_triangle<Vec2f>(v1, v2, v3, p)) {
                image.setPixel(p[0], p[1], colour);
            }
        }
    }
}

void flat_triangle3(Vec3f &v1, Vec3f &v2, Vec3f &v3, TImage &image, const TColour &colour, int *zbuffer) {
    float max_x = std::max(v1[0], std::max(v2[0], v3[0]));
    float max_y = std::max(v1[1], std::max(v2[1], v3[1]));

    float min_x = std::min(v1[0], std::min(v2[0], v3[0]));
    float min_y = std::min(v1[1], std::min(v2[1], v3[1]));

    std::pair<uint16_t, uint16_t> dimensions = image.get_dimensions();

    for (int y = (int)min_y; y <= (int)max_y; y++) {
        for (int x = (int)min_x; x <= (int)max_x; x++) {
            Vec3f p({(float)x, (float)y, 1});

            if (point_is_in_triangle<Vec3f>(v1, v2, v3, p)) {
                Vec3f points[3] = {v1, v2, v3};
                Vec3f bary_coords;
                int r = barycentric_coords(points, p, bary_coords);
                if (r != 0)  // Can't get valid barycentric coordinates
                    continue;

                float z = v1[2] * bary_coords[0] + v2[2] * bary_coords[1] + v3[2] * bary_coords[2];
                int zbuffer_offset = dimensions.first * y + x;
                if (zbuffer[zbuffer_offset] > z) {
                    image.setPixel(p[0], p[1], colour);
                    zbuffer[zbuffer_offset] = z;
                }
            }
        }
    }
}