#include <util/types.h>

// Std includes
#include <iostream>

// Local includes
#include <util/image.hpp>
#include <util/math.hpp>
#include <ray.hpp>

using namespace math;

int32 main() {
    img::Image image(800, 600);
    for (int32 y = 0; y < 600; y ++) {
        for (int32 x = 0; x < 800; x++) {
            image.set(x, y, img::Pixel(x, y, 0));
        }
    }
    image.save("../render.bmp");

    Ray ray(Vec3(0.0f), Vec3(1.0f));
    Ray r2;
    r2.copy(ray);
    std::cout << "Orig:\n" << r2.getOrigin().toString() << "\nDir:\n" << r2.getDir().toString() << "\n";
    return 0;
}
