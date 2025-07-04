#include <world.hpp>

World::World(){}
World::World(std::vector<hitutil::Hittable*> objects) {
    this->objects = objects;
}
void World::add(hitutil::Hittable* object) {
    if (object != nullptr) {
        objects.push_back(object);
    }
}
void World::remove(int32 idx) {
    if (idx >= 0 && idx < objects.size()) {
        objects.erase(objects.begin() + idx);
    }
}
void World::clear() {
    objects.clear();
}
bool World::raycast(Ray ray, util::Interval rayT, hitutil::HitPoint& point) {
    if (objects.empty()) {
        return false;
    }

    hitutil::HitPoint tempHit;
    bool hit = false;
    float32 closestT = rayT.getMax();

    for (hitutil::Hittable* obj : objects) {
        if (obj->hitRay(ray, util::Interval(rayT.getMin(), closestT), tempHit)) {
            hit = true;
            closestT = tempHit.getT();
            point.copy(tempHit);
        }
    }

    return hit;
}
int32 World::getObjectCount() {
    return objects.size();
}
hitutil::Hittable* World::getObject(int32 idx) {
    return objects.at(idx);
}
std::vector<hitutil::Hittable*> World::getObjcts() {
    return objects;
}