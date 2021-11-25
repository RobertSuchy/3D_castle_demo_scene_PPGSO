// Task 1 - Load a 512x512 image lena.raw
//        - Apply specified per-pixel transformation to each pixel
//        - Save as result.raw
#include <fstream>
#include <iostream>
#include <cmath>

// Size of the framebuffer
const unsigned int SIZE = 512;

// A simple RGB struct will represent a pixel in the framebuffer
struct Pixel {
    // TODO: Define correct data type for r, g, b channel
    uint8_t r, g, b;
};

int main() {
    // Initialize a framebuffer
    auto framebuffer = new Pixel[SIZE][SIZE];

    // TODO: Open file lena.raw (this is 512x512 RAW RGB format)
    std::fstream inputStream;
    inputStream.open("lena.raw", std::ios::binary | std::ios::in);

    // TODO: Read data to framebuffer and close the file
    inputStream.read((char *) framebuffer, SIZE * SIZE * 3);
    inputStream.close();

    // Traverse the framebuffer
    char colors[3][3] = {{'R', 'G', 'B'},
                         {'B', 'R', 'G'},
                         {'G', 'B', 'R'}};

    for (unsigned int y = 0; y < SIZE; y++) {
        for (unsigned int x = 0; x < SIZE; x++) {
            // TODO: Apply pixel operation
            if (colors[int(ceil(y / 171))][int(ceil(x / 171))] == 'R') {
                framebuffer[y][x].g = 0;
                framebuffer[y][x].b = 0;
            } else if (colors[int(ceil(y / 171))][int(ceil(x / 171))] == 'G') {
                framebuffer[y][x].r = 0;
                framebuffer[y][x].b = 0;
            } else if (colors[int(ceil(y / 171))][int(ceil(x / 171))] == 'B') {
                framebuffer[y][x].r = 0;
                framebuffer[y][x].g = 0;
            }
        }
    }

    // TODO: Open file result.raw
    std::cout << "Generating result.raw file ..." << std::endl;
    std::fstream outputStream;
    outputStream.open("result.raw", std::ios::binary | std::ios::out);

    // TODO: Write the framebuffer to the file and close it
    outputStream.write((char *) framebuffer, SIZE * SIZE * 3);
    outputStream.close();

    std::cout << "Done." << std::endl;
    delete[] framebuffer;
    return EXIT_SUCCESS;
}
