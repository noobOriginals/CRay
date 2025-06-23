#include <hitutil.hpp>

using namespace hitutil;
using namespace math;

HitPoint::HitPoint() {
    point = Vec3();
    norm = Vec3();
    t = 0.0f;
    frontFace = false;
}
void HitPoint::setFaceNormal(Ray ray, math::Vec3 outwardNormal) {
    frontFace = ray.getDir().dot(outwardNormal) < 0.0f;
    norm = frontFace ? outwardNormal : outwardNormal.neg();
}
void HitPoint::setPoint(math::Vec3 point) {
    this->point = point;
}
void HitPoint::setNormal(math::Vec3 normal) {
    norm = normal;
}
void HitPoint::setMaterial(Material material) {
    mat = material;
}
void HitPoint::setT(float32 t) {
    this->t = t;
}
void HitPoint::setFrontFace(bool frontFace) {
    this->frontFace = frontFace;
}
math::Vec3 HitPoint::getPoint() {
    return point;
}
math::Vec3 HitPoint::getNormal() {
    return norm;
}
Material HitPoint::getMaterial() {
    return mat;
}
float32 HitPoint::getT() {
    return t;
}
bool HitPoint::getFrontFace() {
    return frontFace;
}
void HitPoint::copy(HitPoint other) {
    point = other.getPoint();
    norm = other.getNormal();
    mat = other.getMaterial();
    t = other.getT();
    frontFace = other.getFrontFace();
}