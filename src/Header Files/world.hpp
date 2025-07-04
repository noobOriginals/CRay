#ifndef WORLD_HPP
#define WORLD_HPP
#include <util/types.h>

// Std includes
#include <vector>

// Local includes
#include <util/utility.hpp>
#include <ray.hpp>
#include <hitutil.hpp>

class World {
public:
    World();
    World(std::vector<hitutil::Hittable*> objects);
    void add(hitutil::Hittable* object);
    void remove(int32 idx);
    void clear();
    bool raycast(Ray ray, util::Interval rayT, hitutil::HitPoint& point);
    int32 getObjectCount();
    hitutil::Hittable* getObject(int32 idx);
    std::vector<hitutil::Hittable*> getObjcts();

private:
    std::vector<hitutil::Hittable*> objects;
};

#endif