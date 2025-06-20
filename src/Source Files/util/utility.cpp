#include <util/utility.hpp>

// Std includes
#include <limits>

using namespace util;

Interval::Interval() {
    min = POSITIVE_INFINITY;
    max = NEGATIVE_INFINITY;
}
Interval::Interval(float32 min, float32 max) {
    this->min = min;
    this->max = max;
}
float32 Interval::getSize() {
    return max - min;
}
bool Interval::contains(float32 value) {
    return value >= min && value <= max;
}
bool Interval::surrounds(float32 value) {
    return value > min && value < max;
}
float32 Interval::clamp(float32 value) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}
math::Vec3 Interval::clamp(math::Vec3 v) {
    float32 x, y, z;
    x = v.x;
    y = v.y;
    z = v.z;
    if (v.x < min) {
        x = min;
    }
    if (v.x > max) {
        x = max;
    }
    if (v.y < min) {
        y = min;
    }
    if (v.y > max) {
        y = max;
    }
    if (v.z < min) {
        z = min;
    }
    if (v.z > max) {
        z = max;
    }
    return math::Vec3(x, y, z);
}
float32 Interval::getMin() {
    return min;
}
float32 Interval::getMax() {
    return max;
}

namespace util {


float32 degToRad(float32 deg) {

}
float32 radToDeg(float32 rad) {

}
float32 clamp(float32 value, float32 min, float32 max) {

}
math::Vec3 clamp(math::Vec3 v, float32 min, float32 max) {

}
float32 randomFLoat() {

}
float32 randomFloat(float32 min, float32 max) {

}
float32 randomGaussian() {

}
float32 randomGaussian(float32 mean, float32 stddev) {

}
math::Vec3 randomVec3() {

}
math::Vec3 randomVec3(float32 min, float32 max) {

}
math::Vec3 randomUnitVec3() {

}
math::Vec3 gammaCorrect(math::Vec3 color) {

}
bool isNearZero(float32 f) {

}
bool isNearZeor(math::Vec3 v) {

}
math::Vec3 reflect(math::Vec3 v, math::Vec3 normal) {

}
math::Vec3 refract(math::Vec3 uv, math::Vec3 normal, float32 ratio) {

}
float32 reflectance(float32 cosine, float32 refIdx) {

}

}