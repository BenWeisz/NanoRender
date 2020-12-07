#ifndef PIMAGE_H
#define PIMAGE_H

class PImage {
    public:
        int    mW;
        int    mH;
        char** mBuffer;

        PImage(const int &width, const int &height);
        PImage(const char* fileName);
        ~PImage();
};

#endif