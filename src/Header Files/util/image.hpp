#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <util/types.h>

// Std includes
#include <string>

// Local includes
#include <util/math.hpp>

namespace img {

class Pixel {
public:
    int8 r, g, b;
    Pixel();
    Pixel(int8 r, int8 g, int8 b);
    Pixel(math::Vec3 v);
};

class Image {
public:
    Image(){}
    Image(int32 width, int32 height);
    ~Image();
    Pixel get(int32 x, int32 y);
    void set(int32 x, int32 y, Pixel p);
    void set(int32 i, Pixel p);
    void setPixels(int32 size, int32 offset, Pixel* pixels);
    void save(std::string filename);
    int32 getWidth();
    int32 getHeight();
    int32 getSize();
    Pixel* getPixles(int32* size);

private:
    Pixel* pixels;
    int32 width, height, size;
};

}

#endif