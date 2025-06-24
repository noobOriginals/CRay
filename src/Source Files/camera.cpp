#include <camera.hpp>

// Std includes
#include <cmath>

// Local includes
#include <util/utility.hpp>

using namespace math;

Camera::Camera(math::Vec3 pos, math::Vec3 lookat, float32 aspectRatio, float32 hfov, int32 pixelsX) {
    this->pos = pos;
    this->lookat = lookat;
    up = Vec3(0.0f, 1.0f, 0.0f);
    this->aspectRatio = aspectRatio;
    float32 width = std::tan(util::degToRad(hfov) / 2.0f);
    viewportWidth = width * 2.0f;
    focalLength = 1.0f;
    this->pixelsX = pixelsX;
    pixelsY = (int32)(pixelsX / aspectRatio);
    viewportHeight = viewportWidth * (float32)pixelsY / pixelsX;
    w = pos.sub(lookat).normalize();
    u = up.cross(w).normalize();
    v = w.cross(u);
    math::Vec3 viewportX = u.mul(viewportWidth);
    math::Vec3 viewportY = v.mul(viewportHeight);
    pixelDeltaX = viewportX.div(pixelsX);
    pixelDeltaY = viewportY.div(pixelsY);
    math::Vec3 viewportOrigin = pos.sub(w).sub(viewportX.div(2.0f)).sub(viewportY.div(2.0f));
    pixelOrigin = viewportOrigin.add(pixelDeltaX.add(pixelDeltaY).mul(0.5f));
}
math::Vec3 Camera::getPixelPos(int32 x, int32 y) {
    return pixelOrigin.add(pixelDeltaY.mul(y)).add(pixelDeltaX.mul(x));
}
math::Vec3 Camera::getPos() {
    return pos;
}
float32 Camera::getAspectRatio() {
    return aspectRatio;
}
float32 Camera::getFocalLength() {
    return focalLength;
}
float32 Camera::getViewportWidth() {
    return viewportWidth;
}
float32 Camera::getViewportHeight() {
    return viewportHeight;
}
math::Vec3 Camera::getPixelDeltaX() {
    return pixelDeltaX;
}
math::Vec3 Camera::getPixelDeltaY() {
    return pixelDeltaY;
}
math::Vec3 Camera::getPixelOrigin() {
    return pixelOrigin;
}
math::Vec3 Camera::getU() {
    return u;
}
math::Vec3 Camera::getV() {
    return v;
}
math::Vec3 Camera::getW() {
    return w;
}
math::Vec3 Camera::getLookat() {
    return lookat;
}
math::Vec3 Camera::getUp() {
    return up;
}
void Camera::setPos(math::Vec3 pos, math::Vec3 lookat) {
    this->pos = pos;
    this->lookat = lookat;
    w = pos.sub(lookat).normalize();
    u = up.cross(w).normalize();
    v = w.cross(u);
    math::Vec3 viewportX = u.mul(viewportWidth);
    math::Vec3 viewportY = v.mul(viewportHeight);
    pixelDeltaX = viewportX.div(pixelsX);
    pixelDeltaY = viewportY.div(pixelsY);
    math::Vec3 viewportOrigin = pos.sub(w).sub(viewportX.div(2.0f)).sub(viewportY.div(2.0f));
    pixelOrigin = viewportOrigin.add(pixelDeltaX.add(pixelDeltaY).mul(0.5f));
}