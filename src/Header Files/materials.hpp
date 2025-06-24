#ifndef MATERIALS_HPP
#define MATERIALS_HPP
#include <util/types.h>

// Local includes
#include <util/math.hpp>
#include <hitutil.hpp>

namespace material {

class Lambertian : public hitutil::Material {
public:
    Lambertian(math::Vec3 albedo);
    bool scatter(Ray rayIn, hitutil::HitPoint& hitPoint, math::Vec3& attenuation, Ray& scatteredRay) const override;
    math::Vec3 getAlbedo();

private:
    math::Vec3 albedo;
};
class Metal : public hitutil::Material {
public:
    Metal(math::Vec3 albedo, float32 fuzz);
    bool scatter(Ray rayIn, hitutil::HitPoint& hitPoint, math::Vec3& attenuation, Ray& scatteredRay) const override;
    math::Vec3 getAlbedo();
    float32 getFuzz();

private:
    math::Vec3 albedo;
    float32 fuzz;
};
class Dielectric : public hitutil::Material {
public:
    Dielectric(math::Vec3 albedo, float32 refractionIdx);
    bool scatter(Ray rayIn, hitutil::HitPoint& hitPoint, math::Vec3& attenuation, Ray& scatteredRay) const override;
    math::Vec3 getAlbedo();
    float32 getRefIdx();

private:
    math::Vec3 albedo;
    float32 refIdx;
};

}

#endif