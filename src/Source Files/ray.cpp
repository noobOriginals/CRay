#include <ray.hpp>

Ray::Ray() {
    origin = dir = math::Vec3();
}
Ray::Ray(math::Vec3 origin, math::Vec3 direction) {
    this->origin = origin;
    dir = direction;
}
math::Vec3 Ray::at(float32 t) {
    return origin.add(dir.mul(t));
}
void Ray::setOrigin(math::Vec3 origin) {
    this->origin = origin;
}
void Ray::setDir(math::Vec3 direction) {
    dir = direction;
}
void Ray::copy(Ray other) {
    origin = other.getOrigin();
    dir = other.getDir();
}
math::Vec3 Ray::getOrigin() {
    return origin;
}
math::Vec3 Ray::getDir() {
    return dir;
}