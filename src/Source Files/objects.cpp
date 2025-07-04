#include <objects.hpp>

// Std includes
#include <cmath>

using namespace object;

Sphere::Sphere(math::Vec3 center, float32 radius, hitutil::Material* material) {
    this->center = center;
    this->radius = radius;
    mat = material;
}
bool Sphere::hitRay(Ray ray, util::Interval rayT, hitutil::HitPoint& hitPoint) {
    math::Vec3 oc = center.sub(ray.getOrigin());
    float32 a = ray.getDir().lenSq();
    float32 h = ray.getDir().dot(oc);
    float32 c = oc.lenSq() - radius * radius;
    float32 delta = h * h - a * c;
    if (delta < 0.0f) {
        return false;
    }

    delta = std::sqrt(delta);
    float32 root = (h - delta) / a;
    if (!rayT.surrounds(root)) {
        root = (h + delta) / a;
        if (!rayT.surrounds(root)) {
            return false;
        }
    }

    hitPoint.setT(root);
    hitPoint.setPoint(ray.at(hitPoint.getT()));
    math::Vec3 normal = hitPoint.getPoint().sub(center).normalize();
    hitPoint.setFaceNormal(ray, normal);
    hitPoint.setMaterial(mat);

    return true;
}
math::Vec3 Sphere::getCenter() {
    return center;
}
float32 Sphere::getRadius() {
    return radius;
}