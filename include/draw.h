#ifndef DRAW_H
#define DRAW_H

#include <limits.h>

#include <algorithm>
#include <cmath>
#include <cstdio>

#include "geometry.h"
#include "model.h"
#include "timage.h"

void line(int x0, int y0, int x1, int y1, TImage &image, const TColour &colour);
void line2d(const Vec2f &v1, const Vec2f &v2, TImage &image, const TColour &colour);

void flat_triangle(const Vec2f &v1, const Vec2f &v2, const Vec2f &v3, TImage &image, const TColour &colour);
void flat_triangle3(const Vec3f &v1, const Vec3f &v2, const Vec3f &v3, TImage &image, const TColour &colour, float *zbuffer);

void textured_triangle(const Vec3f &v1, const Vec3f &v2, const Vec3f &v3, const float light_intensity, TImage &image, float *const zbuffer, const TextureFace &texture, Model &model);

void int_normal_triangle(const Vec3f &v1, const Vec3f &v2, const Vec3f &v3, const Mat33f &normals, const Vec3f &lighting_dir, TImage &image, float *const zbuffer, const TextureFace &texture, Model &model);

#endif  // DRAW_h
