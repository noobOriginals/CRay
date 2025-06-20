#include <util/image.hpp>

// Std includes
#include <cstdlib>
#include <cstdio>

using namespace img;

Pixel::Pixel() {
    r = g = b = 0;
}
Pixel::Pixel(int8 r, int8 g, int8 b) {
    this->r = r;
    this->g = g;
    this->b = b;
}
Pixel::Pixel(math::Vec3 v) {
    r = v.x * 255.0f;
    g = v.y * 255.0f;
    b = v.z * 255.0f;
}

Image::Image(int32 width, int32 height) {
    this->width = width;
    this->height = height;
    size = width * height;
    pixels = (Pixel*)calloc(size, sizeof(Pixel));
}
Image::~Image() {
    free(pixels);
}
Pixel Image::get(int32 x, int32 y) {
    return pixels[y * width + x];
}
void Image::set(int32 x, int32 y, Pixel p) {
    pixels[y * width + x] = p;
}
void Image::set(int32 i, Pixel p) {
    pixels[i] = p;
}
void Image::setPixels(int32 size, int32 offset, Pixel* pixels) {
    for (int32 i = offset; i < size; i++) {
        this->pixels[i] = pixels[i];
    }
}
void Image::save(std::string filename) {
    int64* content = (int64*)calloc(16, sizeof(int64));
    content[0] = 0x4D42; // "BM" file header
    content[1] = 14 + 40 + size * 3; // File size in bytes (14 file header size + 40 DIB header size + nr. pixels * 3 bytes per pixel)
    content[2] = 0; // Ignored
    content[3] = 0; // Ignored
    content[4] = 14 + 40; // Pixel data offset in bytes (14 file header size + 40 DIB header size)
    content[5] = 40; // DIB header
    content[6] = width; // Image width in pixels
    content[7] = height; // Image height in pixels
    content[8] = 1; // Color planes, must be 1
    content[9] = 8 * 3; // Bits per pixel
    content[10] = 0; // Compression method, 0 for BI_RGB compression (no compression)
    content[11] = size * 3; // Size of the raw bitmap data
    content[12] = 0; // Ignored
    content[13] = 0; // Ignored
    content[14] = 0; // Ignored
    content[15] = 0; // Ignored
    uint8 padding = 0;
    FILE* file = fopen(filename.c_str(), "wb");
    fwrite(&content[0], sizeof(uint16), 1, file);
    fwrite(&content[1], sizeof(uint32), 1, file);
    fwrite(&content[2], sizeof(uint16), 2, file); // Ignored
    fwrite(&content[4], sizeof(uint32), 1, file);
    fwrite(&content[5], sizeof(uint32), 1, file);
    fwrite(&content[6], sizeof(int32), 1, file);
    fwrite(&content[7], sizeof(int32), 1, file);
    fwrite(&content[8], sizeof(uint16), 1, file);
    fwrite(&content[9], sizeof(uint16), 1, file);
    fwrite(&content[10], sizeof(uint32), 1, file);
    fwrite(&content[11], sizeof(uint32), 1, file);
    fwrite(&content[12], sizeof(int32), 4, file); // Ignored
    for (int32 i = 0; i < size; i++) {
        fwrite(&pixels[i].b, sizeof(uint8), 1, file);
        fwrite(&pixels[i].g, sizeof(uint8), 1, file);
        fwrite(&pixels[i].r, sizeof(uint8), 1, file);
    }
    fclose(file);
    free(content);
}
int32 Image::getWidth() {
    return width;
}
int32 Image::getHeight() {
    return height;
}
int32 Image::getSize() {
    return size;
}
Pixel* Image::getPixles(int32* size) {
    *size = this->size;
    return pixels;
}