#ifndef HITUTIL_HPP
#define HITUTIL_HPP
#include <util/types.h>

// Local includes
#include <util/math.hpp>
#include <util/utility.hpp>
#include <ray.hpp>

namespace hitutil {

class Material;
class HitPoint;
class Hittable;

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(Ray rayIn, HitPoint& hitPoint, math::Vec3& attenuation, Ray& scatteredRay) = 0;
};
class HitPoint {
public:
    HitPoint();
    void setFaceNormal(Ray ray, math::Vec3 outwardNormal);
    void setPoint(math::Vec3 point);
    void setNormal(math::Vec3 normal);
    void setMaterial(Material* material);
    void setT(float32 t);
    void setFrontFace(bool frontFace);
    math::Vec3 getPoint();
    math::Vec3 getNormal();
    Material* getMaterial();
    float32 getT();
    bool getFrontFace();
    void copy(HitPoint other);

private:
    math::Vec3 point, norm;
    Material* mat;
    float32 t;
    bool frontFace;
};
class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool hitRay(Ray ray, util::Interval rayT, HitPoint& hitPoint) = 0;
};

}

#endif