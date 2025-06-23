#ifndef RAY_HPP
#define RAY_HPP
#include <util/types.h>

// Local includes
#include <util/math.hpp>

class Ray {
public:
    Ray();
    Ray(math::Vec3 origin, math::Vec3 direction);
    math::Vec3 at(float32 t);
    void setOrigin(math::Vec3 origin);
    void setDirection(math::Vec3 direction);
    void copy(Ray other);
    math::Vec3 getOrigin();
    math::Vec3 getDir();

private:
    math::Vec3 origin, dir;
};

#endif