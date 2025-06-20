#include <util/math.hpp>

using namespace math;

Vec3::Vec3() {
    x = y = z = 0.0f;
}
Vec3::Vec3(float32 f) {
    x = y = z = f;
}
Vec3::Vec3(float32 x, float32 y, float32 z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
Vec3 Vec3::neg() {
    return Vec3(-x, -y, -z);
}
Vec3 Vec3::add(Vec3 v) {
    return Vec3(x + v.x, y + v.y, z + v.z);
}
Vec3 Vec3::sub(Vec3 v) {
    return Vec3(x - v.x, y - v.y, z - v.z);
}
Vec3 Vec3::mul(Vec3 v) {
    return Vec3(x * v.x, y * v.y, z * v.z);
}
Vec3 Vec3::div(Vec3 v) {
    return Vec3(x / v.x, y / v.y, z / v.z);
}
Vec3 Vec3::add(float32 f) {
    return Vec3(x + f, y + f, z + f);
}
Vec3 Vec3::sub(float32 f) {
    return Vec3(x - f, y - f, z - f);
}
Vec3 Vec3::mul(float32 f) {
    return Vec3(x * f, y * f, z * f);
}
Vec3 Vec3::div(float32 f) {
    return Vec3(x / f, y / f, z / f);
}
float32 Vec3::dot(Vec3 v) {
    return x * v.x + y * v.y + z * v.z;
}
Vec3 Vec3::cross(Vec3 v) {
    return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}
float32 Vec3::len() {
    return std::sqrt(x * x + y * y + z * z);
}
float32 Vec3::lenSq() {
    return x * x + y * y + z * z;
}
Vec3 Vec3::normalize() {
    float length = len();
    if (length == 0) {
        return Vec3(0.0f);
    }
    else {
        return Vec3(x / length, y / length, z / length);
    }
}
void Vec3::copy(Vec3 v) {
    x = v.x;
    y = v.y;
    z = v.z;
}
std::string Vec3::toString() {
    return std::to_string(x) + "\n" + std::to_string(y) + "\n" + std::to_string(z);
}

namespace math {

Vec3 neg(Vec3 v) {
    return Vec3(-v.x, -v.y, -v.z);
}
Vec3 add(Vec3 v0, Vec3 v1) {
    return Vec3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}
Vec3 sub(Vec3 v0, Vec3 v1) {
    return Vec3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}
Vec3 mul(Vec3 v0, Vec3 v1) {
    return Vec3(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}
Vec3 div(Vec3 v0, Vec3 v1) {
    return Vec3(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}
Vec3 add(Vec3 v, float32 f) {
    return Vec3(v.x + f, v.y + f, v.z + f);
}
Vec3 add(float32 f, Vec3 v) {
    return Vec3(f + v.x, f + v.y, f + v.z);
}
Vec3 sub(Vec3 v, float32 f) {
    return Vec3(v.x - f, v.y - f, v.z - f);
}
Vec3 sub(float32 f, Vec3 v) {
    return Vec3(f - v.x, f - v.y, f - v.z);
}
Vec3 mul(Vec3 v, float32 f) {
    return Vec3(v.x * f, v.y * f, v.z * f);
}
Vec3 mul(float32 f, Vec3 v) {
    return Vec3(f * v.x, f * v.y, f * v.z);
}
Vec3 div(Vec3 v, float32 f) {
    return Vec3(v.x / f, v.y / f, v.z / f);
}
Vec3 div(float32 f, Vec3 v) {
    return Vec3(f / v.x, f / v.y, f / v.z);
}
float32 dot(Vec3 v0, Vec3 v1) {
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}
Vec3 cross(Vec3 v0, Vec3 v1) {
    return Vec3(v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x);
}
float32 len(Vec3 v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
float32 lenSq(Vec3 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
Vec3 normalize(Vec3 v) {
    float length = len(v);
    if (length == 0) {
        return Vec3(0.0f);
    }
    else {
        return Vec3(v.x / length, v.y / length, v.z / length);
    }
}
std::string toString(Vec3 v) {
    return std::to_string(v.x) + "\n" + std::to_string(v.y) + "\n" + std::to_string(v.z);
}

}