#ifndef DRAW_H
#define DRAW_H

#include <limits.h>

#include <algorithm>
#include <cmath>
#include <cstdio>

#include "geometry.h"
#include "timage.h"

void line(int x0, int y0, int x1, int y1, TImage &image, const TColour &colour);
void line2d(const Vec2f &v1, const Vec2f &v2, TImage &image, const TColour &colour);

void flat_triangle(Vec2f &v1, Vec2f &v2, Vec2f &v3, TImage &image, const TColour &colour);
void flat_triangle3(Vec3f &v1, Vec3f &v2, Vec3f &v3, TImage &image, const TColour &colour, int *zbuffer);

#endif  // DRAW_h
