#include <util/types.h>

// Std includes
#include <cstdlib>
#include <iostream>
#include <vector>

// Local includes
#include <util/math.hpp>
#include <util/utility.hpp>
#include <hitutil.hpp>
#include <objects.hpp>
#include <materials.hpp>
#include <world.hpp>
#include <render.hpp>

using namespace std;
using namespace math;
using namespace object;
using namespace hitutil;
using namespace material;

vector<Material*> mats;

Material* diffuse(float32 r, float32 g, float32 b) {
    Lambertian* l = (Lambertian*)calloc(1, sizeof(Lambertian));
    *l =  Lambertian(Vec3(r, g, b));
    mats.push_back(l);
    return l;
}
Material* metal(float32 r, float32 g, float32 b, float32 fuzz) {
    Metal* m = (Metal*)calloc(1, sizeof(Metal));
    *m =  Metal(Vec3(r, g, b), fuzz);
    mats.push_back(m);
    return m;
}
Material* dielectric(float32 r, float32 g, float32 b, float32 refractIdx) {
    Dielectric* d = (Dielectric*)calloc(1, sizeof(Dielectric));
    *d =  Dielectric(Vec3(r, g, b), refractIdx);
    mats.push_back(d);
    return d;
}

int32 main() {
    Render render(Vec3(-2.0f, 2.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f), 2000, 1500, 70.0f, 500, 100, 32);
    World world;
    Sphere s1 = Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f, diffuse(0.8f, 0.8f, 0.0f));
    Sphere s2 = Sphere(Vec3(0.0f, 0.0f, -1.2f), 0.5f, diffuse(0.1f, 0.2f, 0.5f));
    Sphere s3 = Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.4f, dielectric(0.9f, 0.9f, 0.9f, 1.0f / 1.5f));
    Sphere s4 = Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, dielectric(0.9f, 0.9f, 0.9f, 1.5f));
    Sphere s5 = Sphere(Vec3(1.0f, 0.0f, -1.0f), 0.5f, metal(0.8f, 0.4f, 0.4f, 0.08f));
    Sphere s6 = Sphere(Vec3(1.5f, -0.2f, -2.3f), 0.3f, metal(0.5f, 0.7f, 0.9f, 0.01f));
    world.add(&s1);
    world.add(&s2);
    world.add(&s3);
    world.add(&s4);
    world.add(&s5);
    world.add(&s6);
    render.render(world);
    render.waitToFinish();
    std::cout << "Saving render...\n";
    int64 startTime = util::getNanoTime();
    render.save("render.bmp");
    int64 elapsedTime = util::getNanoTime() - startTime;
    std::cout << "Saved render in " << elapsedTime / 1000000000.0f << " seconds.\n";
    for (int32 i = 0; i < mats.size(); i++) {
        free(mats.at(i));
    }
    std::cout << "Render complete.\n";
    return 0;
}

