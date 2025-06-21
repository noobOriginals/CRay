#include <util/utility.hpp>

// Std includes
#include <cmath>
#include <limits>
#include <random>
#include <thread>

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

thread_local std::mt19937 randGen(std::random_device{}());

float32 degToRad(float32 deg) {
    return deg * PI / 180.0;
}
float32 radToDeg(float32 rad) {
    return rad * 180.0 / PI;
}
float32 clamp(float32 value, float32 min, float32 max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}
math::Vec3 clamp(math::Vec3 v, float32 min, float32 max) {
    float x, y, z;
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
float32 randomFloat() {
    std::uniform_real_distribution<float32> distro(0.0f, 1.0f);
    return distro(randGen);
}
float32 randomFloat(float32 min, float32 max) {
    std::uniform_real_distribution<float32> distro(min, max);
    return distro(randGen);
}
float32 randomGaussian() {
    std::normal_distribution<float32> distro(0.0f, 1.0f);
    return distro(randGen);
}
float32 randomGaussian(float32 mean, float32 stddev) {
    std::normal_distribution<float32> distro(mean, stddev);
    return distro(randGen);
}
math::Vec3 randomVec3() {
    return math::Vec3(randomFloat(), randomFloat(), randomFloat());
}
math::Vec3 randomVec3(float32 min, float32 max) {
    return math::Vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}
math::Vec3 randomUnitVec3() {
    return math::Vec3(randomGaussian(), randomGaussian(), randomGaussian()).normalize();
}
math::Vec3 gammaCorrect(math::Vec3 color) {
    return math::Vec3(std::sqrt(color.x), std::sqrt(color.y), std::sqrt(color.z));
}
bool isNearZero(float32 f) {
    return std::fabs(f) < 1e-8f;
}
bool isNearZero(math::Vec3 v) {
    return isNearZero(v.x) && isNearZero(v.y) && isNearZero(v.z);
}
math::Vec3 reflect(math::Vec3 v, math::Vec3 normal) {
    return v.sub(normal.mul(2.0f * v.dot(normal)));
}
math::Vec3 refract(math::Vec3 uv, math::Vec3 normal, float32 ratio) {
    float32 cos = std::fmin(uv.neg().dot(normal), 1.0f);
    math::Vec3 perp = normal.mul(cos).add(uv).mul(ratio);
    math::Vec3 parl = normal.mul(-std::sqrt(std::fabs(1.0f - perp.lenSq())));
    return perp.add(parl);
}
float32 reflectance(float32 cosine, float32 refIdx) {
    float32 r0 = (1.0f - refIdx) / (1.0f + refIdx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * std::pow(1.0f - cosine, 5.0f);
}

}