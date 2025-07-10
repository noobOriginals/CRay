#include <util/types.h>

#include <util/math.hpp>
#include <render.hpp>

using namespace math;
using namespace img;

int32 main() {
    Render render(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), 800, 600, 90.0f);
    render.render();
    render.save("render.bmp");
    return 0;
}