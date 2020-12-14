#include "timage.h"
#include "draw.h"

int main() {
    TImage image(100, 100);

    TColour red(255, 0, 0);
    TColour white(255, 255, 255);

    line(50, 50, 50, 100, image, red);
    line(50, 50, 100, 50, image, red);
    line(50, 50, 50, 0, image, red);
    line(50, 50, 0, 50, image, red);

    line(50, 50, 100, 100, image, white);
    line(50, 50, 100, 0, image, white);
    line(50, 50, 0, 0, image, white);
    line(50, 50, 0, 100, image, white);
    
    image.write("test.tga");
}