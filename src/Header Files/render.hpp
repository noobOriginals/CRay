#ifndef RENDER_HPP
#define RENDER_HPP
#include <util/types.h>

// Std includes
#include <string>

// Local includes
#include <util/math.hpp>
#include <util/image.hpp>
#include <ray.hpp>
#include <camera.hpp>

class Render {
public:
    Render(math::Vec3 pos, math::Vec3 lookat, int32 width, int32 height, float32 hfov);
    ~Render();
    void render();
    math::Vec3 raycast(Ray ray);
    void save(std::string filename);

private:
    Camera* camera;
    img::Image* image;
};

#endif