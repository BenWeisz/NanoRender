#include <iostream>
#include "pimage.h"

int main() 
{
    PImage *p = new PImage(100, 100);
    std::cout << "Hello World" << std::endl;

    delete p;
}