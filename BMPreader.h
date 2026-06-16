#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


// Force 2-byte alignment to prevent compiler padding
#pragma pack(push, 2)
struct BmpFileHeader {
    uint16_t fileType{ 0 };       // Magic identifier: Always 0x4D42 ("BM")
    uint32_t fileSize{ 0 };       // Total file size in bytes
    uint16_t reserved1{ 0 };      // Always 0
    uint16_t reserved2{ 0 };      // Always 0
    uint32_t offsetData{ 0 };     // Start position of row/Pixel data
};

struct BmpInfoHeader {
    uint32_t size{ 0 };           // Size of this header (usually 40)
    int32_t  width{ 0 };          // Image width in pixels
    int32_t  height{ 0 };         // Image height in pixels
    uint16_t planes{ 1 };         // Number of color planes (must be 1)
    uint16_t bitCount{ 0 };       // Bits per Pixel (1, 4, 8, 16, 24, 32)
    uint32_t compression{ 0 };    // Compression type (0 = uncompressed)
    uint32_t sizeImage{ 0 };      // Image size in bytes
    int32_t  xPixelsPerMeter{ 0 };
    int32_t  yPixelsPerMeter{ 0 };
    uint32_t colorsUsed{ 0 };     // Number of colors used
    uint32_t colorsImportant{ 0 };
};

struct Pixelbmp {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
};
void print(Pixelbmp a) {
    std::cout << static_cast<unsigned int>(a.r) << ' ' << static_cast<unsigned int>(a.g) << ' ' << static_cast<unsigned int>(a.b) << ' ' << static_cast<unsigned int>(a.a) << "   ";
    return;
}
void print(vector<vector<Pixelbmp>> a) {
    for (vector<Pixelbmp> g : a) {
        for (Pixelbmp k : g) {
            print(k);
        }
        std::cout << '\n';
    }
    return;
}
template<typename T>
void reverce(vector<T>& a) {
    for (int i = 0; i < a.size() / 2; i++) {
        swap(a[i], a[a.size() - 1-i]);
    }
}

#pragma pack(pop)

class BmpReader {
public:
    BmpFileHeader fileHeader;
    BmpInfoHeader infoHeader;
    std::vector < std::vector<Pixelbmp>> arr;
    bool readHeader(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return false;
        }

        // Read File Header (14 bytes)
        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
        if (!file) return false;

        // Verify "BM" magic signature
        if (fileHeader.fileType != 0x4D42) {
            std::cerr << "Error: Invalid BMP file signature." << std::endl;
            return false;
        }

        // Read Info Header (40 bytes)
        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
        
        file.seekg(fileHeader.offsetData);
        for (int i = 0; i < infoHeader.height; i++) {
            arr.push_back({});
            for (int j = 0; j < infoHeader.width; j++) {
                arr[i].push_back({});
                file.read(reinterpret_cast<char*>(&arr[i][j]), sizeof(Pixelbmp));
            }
            //file.seekg(1, std::fstream::cur);
        }
        reverce(arr);
        return static_cast<bool>(file);
    }
};
