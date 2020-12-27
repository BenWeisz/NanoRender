#ifndef DRAW_H
#define DRAW_H

#include "timage.h"
#include "geometry.h"

void line(int x0, int y0, int x1, int y1, TImage &image, const TColour &color);

void triangle(Vec2f &v1, Vec2f &v2, Vec2f &v3, TImage &image, const TColour &color);

#endif // DRAW_h
