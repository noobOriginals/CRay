#ifndef RENDER_HPP
#define RENDER_HPP
#include <util/types.h>

// Std includes
#include <string>
#include <atomic>
#include <vector>

// Local includes
#include <util/math.hpp>
#include <util/image.hpp>
#include <threadedExec.hpp>
#include <camera.hpp>
#include <world.hpp>

class Render {
public:
    Render(math::Vec3 pos, math::Vec3 lookat, int32 width, int32 height, float32 hfov, int32 samplesPerPixel, int32 maxDepth, int32 nrThreads);
    void render(World world);
    void startProgressIndication();
    void save(std::string filename);
    Camera getCamera();
    img::Image getImage();
    int32 getWidth();
    int32 getHeight();
    bool isDone();
    void waitToFinish();

    static math::Vec3 raycast(Ray ray, int32 depth, World world);

private:
    Camera camera;
    img::Image image;
    int32 samplesPerPixel, maxDepth, nrThreads;
    float32 pixelSampleScale;

    volatile bool done, doneFull;
    volatile int64 startTime, elapsedTime;
    volatile int32 percent, runningExecs;
    std::atomic<int32> renderedPixels;
    std::vector<ThreadedExecution*> execs;

    void dispatch(int32 idxOffset, int32 stride, World world);
};

#endif