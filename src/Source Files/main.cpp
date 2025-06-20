#include <util/types.h>

// Std includes
#include <iostream>

// Local includes
#include <util/image.hpp>

int32 main() {
    img::Image image(800, 600);
    for (int32 y = 0; y < 600; y ++) {
        for (int32 x = 0; x < 800; x++) {
            image.set(x, y, img::Pixel(x, y, 0));
        }
    }
    image.save("../render.bmp");
    return 0;
}
