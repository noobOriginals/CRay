#include <materials.hpp>

// Std includes
#include <cmath>

// Local includes
#include <util/utility.hpp>

using namespace material;
using namespace util;

Lambertian::Lambertian(math::Vec3 albedo) {
    this->albedo = albedo;
}
bool Lambertian::scatter(Ray rayIn, hitutil::HitPoint& hitPoint, math::Vec3& attenuation, Ray& scatteredRay) const {
    math::Vec3 direction = hitPoint.getNormal().add(randomUnitVec3());
    if (isNearZero(direction)) {
        direction = hitPoint.getNormal();
    }
    scatteredRay.setOrigin(hitPoint.getPoint());
    scatteredRay.setDir(direction);
    attenuation.copy(albedo);
    return true;
}
math::Vec3 Lambertian::getAlbedo() {
    return albedo;
}

Metal::Metal(math::Vec3 albedo, float32 fuzz) {
    this->albedo = albedo;
    this->fuzz = fuzz;
}
bool Metal::scatter(Ray rayIn, hitutil::HitPoint& hitPoint, math::Vec3& attenuation, Ray& scatteredRay) const {
    math::Vec3 direction = reflect(rayIn.getDir(), hitPoint.getNormal());
    direction = direction.normalize().add(randomUnitVec3().mul(fuzz));
    scatteredRay.setOrigin(hitPoint.getPoint());
    scatteredRay.setDir(direction);
    attenuation.copy(albedo);
    return (direction.dot(hitPoint.getNormal()) > 0.0f);
}
math::Vec3 Metal::getAlbedo() {
    return albedo;
}
float32 Metal::getFuzz() {
    return fuzz;
}

Dielectric::Dielectric(math::Vec3 albedo, float32 refractionIdx) {
    this->albedo = albedo;
    refIdx = refractionIdx;
}
bool Dielectric::scatter(Ray rayIn, hitutil::HitPoint& hitPoint, math::Vec3& attenuation, Ray& scatteredRay) const {
    attenuation.copy(albedo);
    float32 ratio = hitPoint.getFrontFace() ? (1.0f / refIdx) : refIdx;

    math::Vec3 direction = rayIn.getDir().normalize();

    float cos = std::fmin(direction.neg().dot(hitPoint.getNormal()), 1.0f);
    float sin = std::sqrt(1.0f - cos * cos);

    bool cannotRefract = ratio * sin > 1.0f;

    if (cannotRefract || reflectance(cos, ratio) > randomFloat()) {
        direction = reflect(direction, hitPoint.getNormal());
    }
    else {
        direction = refract(direction, hitPoint.getNormal(), ratio);
    }

    scatteredRay.setOrigin(hitPoint.getPoint());
    scatteredRay.setDir(direction);
    return true;
}
math::Vec3 Dielectric::getAlbedo() {
    return albedo;
}
float32 Dielectric::getRefIdx() {
    return refIdx;
}