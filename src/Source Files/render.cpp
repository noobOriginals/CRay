#include <render.hpp>

// Std includes
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

Render::Render(math::Vec3 pos, math::Vec3 lookat, int32 width, int32 height, float32 hfov, int32 samplesPerPixel, int32 maxDepth, int32 nrThreads) {
    float32 aspectRatio = (float32)width / height;
    camera = Camera(pos, lookat, aspectRatio, hfov, width);
    image = img::Image(width, height);
    this->samplesPerPixel = samplesPerPixel;
    this->maxDepth = maxDepth;
    this->nrThreads = nrThreads;
    pixelSampleScale = 1.0f / samplesPerPixel;
    done = doneFull = false;
}
void Render::render(World world) {
    for (int32 i = 0; i < execs.size(); i++) {
        free(execs.at(i));
    }
    execs.clear();
    done = doneFull = false;
    startProgressIndication();
    startTime = util::getNanoTime();
    renderedPixels.store(0);
    for (int32 i = 0; i < nrThreads; i++) {
        dispatch(i, nrThreads, world);
    }
    while (true) {
        bool d = true;
        int rExecs = 0;
        for (int32 i = 0; i < execs.size(); i++) {
            if (execs.at(i)->isDone()) {
                d = false;
                rExecs++;
            }
        }
        if (d) {
            break;
        }
        runningExecs = rExecs;
        elapsedTime = util::getNanoTime() - startTime;
        std::this_thread::sleep_for(std::chrono::milliseconds((int64)(1000 / 30)));
    }
    done = true;
}
void Render::startProgressIndication() {
    if (done) {
        return;
    }
    ThreadedExecution().execute([&]() {
        std::cout << "Starting render...\n";
        while (!done) {
            percent = (int32)((float32)(renderedPixels.load()) / image.getSize() * 100.0f);
            std::cout << "Running threads: " << runningExecs << "/" << nrThreads << ", Rendered pixels: " << renderedPixels.load() << ", progress: " << percent << "%, time: " << elapsedTime / 1000000000.0f << "s           \r";
            std::this_thread::sleep_for(std::chrono::milliseconds((int64)(1000 / 30)));
        }
        std::cout << "Rendered " << image.getSize() << " pixels in: " << util::getNanoTime() - startTime / 1000000000.0f << " seconds.                                                 \n";
        doneFull = true;
    });
}
void Render::save(std::string filename) {
    image.save(filename);
}
Camera Render::getCamera() {
    return camera;
}
img::Image Render::getImage() {
    return image;
}
int32 Render::getWidth() {
    return image.getWidth();
}
int32 Render::getHeight() {
    return image.getHeight();
}
bool Render::isDone() {
    return doneFull;
}
void Render::waitToFinish() {
    while (!doneFull) {
        std::this_thread::sleep_for(std::chrono::milliseconds((int64)(1000 / 30)));
    }
}

math::Vec3 Render::raycast(Ray ray, int32 depth, World world) {
    if (depth <= 0) {
        return math::Vec3(0.0f);
    }
    hitutil::HitPoint hitPoint;
    math::Vec3 color;
    if (world.raycast(ray, util::Interval(0.001f, util::POSITIVE_INFINITY), hitPoint)) {
        Ray scatteredRay;
        math::Vec3 attenuation;
        if (hitPoint.getMaterial()->scatter(ray, hitPoint, attenuation, scatteredRay)) {
            return raycast(scatteredRay, depth - 1, world).mul(attenuation);
        } else {
            color = math::Vec3(0.0f);
        }
    }
    else {
        math::Vec3 dir = ray.getDir().normalize();
        float32 a = dir.y * 0.5f + 0.5f;
        color = math::Vec3(1.0f, 1.0f, 1.0f).mul(1.0f - a).add(math::Vec3(0.5f, 0.7f, 1.0f).mul(a));
    }
    return color;
}

void Render::dispatch(int32 idxOffset, int32 stride, World world) {
    ThreadedExecution* exec = (ThreadedExecution*)calloc(1, sizeof(ThreadedExecution));
    *exec = ThreadedExecution();
    execs.push_back(exec);
    exec->execute([&]() {
        for (int y = idxOffset; y < image.getHeight(); y += stride) {
            for (int x = 0; x < image.getWidth(); x++) {
                math::Vec3 color(0.0f, 0.0f, 0.0f);
                for (int s = 0; s < samplesPerPixel; s++) {
                    math::Vec3 offset(util::randomFloat(-0.5f, 0.5f), util::randomFloat(-0.5f, 0.5f), 0.0f);
                    math::Vec3 pixelPos = camera.getPixelPos(x, y).add(offset.mul(math::Vec3(camera.getPixelDeltaX().x, camera.getPixelDeltaY().y, 0.0f)));
                    Ray ray(camera.getPos(), pixelPos.sub(camera.getPos()).normalize());
                    color = add(color, raycast(ray, maxDepth, world));
                }
                image.set(x, y, img::Pixel(util::gammaCorrect(util::clamp(color.mul(pixelSampleScale), 0.0f, 1.0f))));
                renderedPixels.fetch_add(1);
            }
        }
    });
}