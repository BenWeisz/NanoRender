#include <cstdlib>
#include "pimage.h"

PImage::PImage(const int &width, const int &height)
    : mW(width)
    , mH(height)
{
    mBuffer = (char**)malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++)
        mBuffer[i] = (char*)malloc(sizeof(char) * width * height);
}

PImage::~PImage()
{
    for (int i = 0; i < 3; i++)
        free(mBuffer[i]);
    free(mBuffer);    
}