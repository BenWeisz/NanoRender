#ifndef TIMAGE_H
#define TIMAGE_H

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#pragma pack(push, 1)
typedef struct TImageHeader {
    std::uint8_t id_length;
    std::uint8_t colour_map_type;
    std::uint8_t data_type;
    std::uint16_t colour_map_origin;
    std::uint16_t colour_map_length;
    std::uint8_t colour_map_depth;
    std::uint16_t x_origin, y_origin;
    std::uint16_t width, height;
    std::uint8_t bits_per_pixel;
    std::uint8_t image_descriptor;
} TImageHeader;
#pragma pack(pop)

class TColour {
   public:
    std::uint8_t m_r, m_g, m_b;
    TColour(const std::uint8_t &r, const std::uint8_t &g, const std::uint8_t &b);
};

class TImage {
   public:
    TImage(const std::uint16_t &width, const std::uint16_t &height);
    ~TImage();
    bool write(const std::string &fileName);
    void setPixel(const int &x, const int &y, const TColour &colour);
    void setColour(const TColour &colour);
    std::pair<uint16_t, uint16_t> get_dimensions();

   private:
    std::uint16_t m_width,
        m_height;
    std::uint8_t *m_buffer;
};

#endif  // TIMAGE_H