#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <util/types.h>

// Std includes
#include <limits>

// Local includes
#include <util/math.hpp>

namespace util {

const float64 PI = 3.14159265358979323846;
const float32 POSITIVE_INFINITY = std::numeric_limits<float32>::infinity();
const float32 NEGATIVE_INFINITY = -std::numeric_limits<float32>::infinity();

class Interval {
public:
    Interval();
    Interval(float32 min, float32 max);
    float32 getSize();
    bool contains(float32 value);
    bool surrounds(float32 value);
    float32 clamp(float32 value);
    math::Vec3 clamp(math::Vec3 v);
    float32 getMin();
    float32 getMax();

private:
    float32 min, max;
};

const Interval empty = Interval();
const Interval universe = Interval(NEGATIVE_INFINITY, POSITIVE_INFINITY);

float32 degToRad(float32 deg);
float32 radToDeg(float32 rad);
float32 clamp(float32 value, float32 min, float32 max);
math::Vec3 clamp(math::Vec3 v, float32 min, float32 max);
float32 randomFloat();
float32 randomFloat(float32 min, float32 max);
float32 randomGaussian();
float32 randomGaussian(float32 mean, float32 stddev);
math::Vec3 randomVec3();
math::Vec3 randomVec3(float32 min, float32 max);
math::Vec3 randomUnitVec3();
math::Vec3 gammaCorrect(math::Vec3 color);
bool isNearZero(float32 f);
bool isNearZero(math::Vec3 v);
math::Vec3 reflect(math::Vec3 v, math::Vec3 normal);
math::Vec3 refract(math::Vec3 uv, math::Vec3 normal, float32 ratio);
float32 reflectance(float32 cosine, float32 refIdx);

}

#endif
