#include <objects.hpp>

using namespace object;

Sphere::Sphere(math::Vec3 center, float32 radius, hitutil::Material* material) {
    this->center = center;
    this->radius = radius;
    mat = material;
}
bool Sphere::hitRay(Ray ray, util::Interval rayT, hitutil::HitPoint& hitPoint) const {
    math::Vec3 center = this->center;
    math::Vec3 oc = center.sub(ray.getOrigin());
}
math::Vec3 Sphere::getCenter() {

}
float32 Sphere::getRadius() {

}