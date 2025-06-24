#ifndef CAMREA_HPP
#define CAMREA_HPP
#include <util/types.h>

// Local includes
#include <util/math.hpp>

class Camera {
public:
    Camera(math::Vec3 pos, math::Vec3 lookat, float32 aspectRatio, float32 hfov, int32 pixelsX);
    math::Vec3 getPixelPos(int32 x, int32 y);
    math::Vec3 getPos();
    float32 getAspectRatio();
    float32 getFocalLength();
    float32 getViewportWidth();
    float32 getViewportHeight();
    math::Vec3 getPixelDeltaX();
    math::Vec3 getPixelDeltaY();
    math::Vec3 getPixelOrigin();
    math::Vec3 getU();
    math::Vec3 getV();
    math::Vec3 getW();
    math::Vec3 getLookat();
    math::Vec3 getUp();
    void setPos(math::Vec3 pos, math::Vec3 lookat);

private:
    float32 aspectRatio, focalLength, viewportWidth, viewportHeight;
    math::Vec3 pixelDeltaX, pixelDeltaY, pixelOrigin, pos, lookat, up, u, v, w;
    int32 pixelsX, pixelsY;
};

#endif