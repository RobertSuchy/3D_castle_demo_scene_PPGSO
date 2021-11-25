// Task 3 - Implement Bresenham drawing alg.
//        - Draw a star using lines
//        - Make use of std::vector to define the shape
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include <ppgso/ppgso.h>

// Size of the framebuffer
const unsigned int SIZE = 512;

struct Point {
    int x,y;
};

// Bresenham drawing algorithm
void drawLine(ppgso::Image& framebuffer, Point& from, Point& to) {
    // TODO: Implement Bresenham drawing algorithm
    int x = from.x;
    int y = from.y;
    if (from.x <= to.x && from.y <= to.y) // 4. kvadrant
    {
        if (abs(from.x - to.x) > abs(from.y - to.y)) { // hlavný pohyb v smere x
            int e = abs(to.x - from.x);
            while (x <= to.x) {
                framebuffer.setPixel(x, y, 255, 255, 255);
                x++;
                e += 2 * abs(to.y - from.y);
                if (e > 0) {
                    y++;
                    e -= 2 * abs(to.x - from.x);
                }
            }
        }
        else { // hlavný pohyb v smere y
            int e = abs(to.y - from.y);
            while (y <= to.y) {
                framebuffer.setPixel(x, y, 255, 255, 255);
                y++;
                e += 2 * abs(to.x - from.x);
                if (e > 0) {
                    x++;
                    e -= 2 * abs(to.y - from.y);
                }
            }
        }
    }
    else if (from.x <= to.x && from.y >= to.y) // 1. kvadrant
    {
        if (abs(from.x - to.x) > abs(from.y - to.y)) { // hlavný pohyb v smere x
            int e = abs(to.x - from.x);
            while (x <= to.x) {
                framebuffer.setPixel(x, y, 255, 255, 255);
                x++;
                e += 2 * abs(from.y - to.y);
                if (e > 0) {
                    y--;
                    e -= 2 * abs(to.x - from.x);
                }
            }
        }
        else { // hlavný pohyb v smere y
            int e = abs(to.y - from.y);
            while (y >= to.y) {
                framebuffer.setPixel(x, y, 255, 255, 255);
                y--;
                e += 2 * abs(from.x - to.x);
                if (e > 0) {
                    x++;
                    e -= 2 * abs(to.y - from.y);
                }
            }
        }
    }
    else if (from.x >= to.x && from.y <= to.y) // 3. kvadrant
    {
        if (abs(from.x - to.x) > abs(from.y - to.y)) { // hlavný pohyb v smere x
            int e = abs(to.x - from.x);
            while (x >= to.x) {
                framebuffer.setPixel(x, y, 255, 255, 255);
                x--;
                e += 2 * abs(to.y - from.y);
                if (e > 0) {
                    y++;
                    e -= 2 * abs(from.x - to.x);
                }
            }
        }
        else { // hlavný pohyb v smere y
            int e = abs(to.y - from.y);
            while (y <= to.y) {
                framebuffer.setPixel(x, y, 255, 255, 255);
                y++;
                e += 2 * abs(to.x - from.x);
                if (e > 0) {
                    x--;
                    e -= 2 * abs(from.y - to.y);
                }
            }
        }
    }
    else if (from.x >= to.x && from.y >= to.y) { // 2. kvadrant
        if (abs(from.x - to.x) > abs(from.y - to.y)) { // hlavný pohyb v smere x
            int e = abs(to.x - from.x);
            while (x >= to.x) {
                framebuffer.setPixel(x, y, 255, 255, 255);
                x--;
                e += 2 * abs(from.y - to.y);
                if (e > 0) {
                    y--;
                    e -= 2 * abs(from.x - to.x);
                }
            }
        }
        else { // hlavný pohyb v smere y
            int e = abs(to.y - from.y);
            while (y >= to.y) {
                framebuffer.setPixel(x, y, 255, 255, 255);
                y--;
                e += 2 * abs(from.x - to.x);
                if (e > 0) {
                    x--;
                    e -= 2 * abs(from.y - to.y);
                }
            }
        }
    }
}

int main() {
    // Use ppgso::Image as our framebuffer
    ppgso::Image framebuffer(SIZE, SIZE);

    // TODO: Generate star points
    std::vector<Point> points;
    points.push_back(Point { 256, 10 });
    points.push_back(Point { 442, 502 });
    points.push_back(Point { 10, 160 });
    points.push_back(Point { 502, 160 });
    points.push_back(Point { 60, 502 });
    points.push_back(Point { 256, 10 });

    // Draw lines
    for(unsigned int i = 0; i < points.size() - 1; i++)
    drawLine(framebuffer, points[i], points[i+1]);

    // Save the result
    std::cout << "Generating task2_bresenham.bmp file ..." << std::endl;
    ppgso::image::saveBMP(framebuffer, "task2_bresenham.bmp");

    std::cout << "Done." << std::endl;
    return EXIT_SUCCESS;
}

