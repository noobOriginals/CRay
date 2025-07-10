#include <render.hpp>

// Std includes
#include <cstdlib>

Render::Render(math::Vec3 pos, math::Vec3 lookat, int32 width, int32 height, float32 hfov) {
    float32 aspectRatio = (float32)width / height;
    camera = (Camera*)malloc(sizeof(Camera));
    image = (img::Image*)malloc(sizeof(img::Image));
    *camera = Camera(pos, lookat, aspectRatio, hfov, width);
    *image = img::Image(width, height);
}
void Render::render() {
    for (int y = 0; y < image->getHeight(); y++) {
        for (int x = 0; x < image->getWidth(); x++) {
            math::Vec3 color(0.0f, 0.0f, 0.0f);
            Ray ray(camera->getPos(), camera->getPixelPos(x, y).sub(camera->getPos()).normalize());
            color = raycast(ray);
            image->set(x, y, img::Pixel(util::gammaCorrect(util::clamp(color, 0.0f, 1.0f))));
        }
    }
}
math::Vec3 Render::raycast(Ray ray) {
    math::Vec3 color;
    math::Vec3 dir = ray.getDir().normalize();
    float32 a = dir.y * 0.5f + 0.5f;
    color = math::Vec3(1.0f, 1.0f, 1.0f).mul(1.0f - a).add(math::Vec3(0.5f, 0.7f, 1.0f).mul(a));
    return color;
}
void Render::save(std::string filename) {
    image->save(filename);
}
Render::~Render() {
    free(camera);
    free(image);
}
