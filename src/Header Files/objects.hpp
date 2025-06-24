#ifndef OBJECTS_HPP
#define OBJECTS_HPP
#include <util/types.h>

// Local includes
#include <util/math.hpp>
#include <ray.hpp>
#include <hitutil.hpp>

namespace object {

class Sphere : public hitutil::Hittable {
public:
    Sphere(math::Vec3 center, float32 radius, hitutil::Material* material);
    bool hitRay(Ray ray, util::Interval rayT, hitutil::HitPoint& hitPoint) const override;
    math::Vec3 getCenter();
    float32 getRadius();

private:
    math::Vec3 center;
    float32 radius;
    hitutil::Material* mat;
};

}

#endif