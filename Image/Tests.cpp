#include <cassert>
#include <iostream>
#include "Image.h"
#include "BrightnessContrast.h"
#include "Convolution.h"
#include "Drawing.h"
#include <sstream>
#include "Point.h"
#include "Rectangle.h"
#include "Size.h"
#include "GammaCorrection.h"

void testBrightnessContrast() {
    Image img(3, 3);
    for (unsigned int y = 0; y < 3; ++y)
        for (unsigned int x = 0; x < 3; ++x)
            img.at(x, y) = y * 3 + x;

    BrightnessContrast bc(1.0f, 10);
    Image result;
    bc.process(img, result);

    assert(result.at(0, 0) == 10);
    assert(result.at(2, 2) == 18);
    std::cout << "BrightnessContrast test passed.\n";
}



unsigned char scaleIdentity(float value) {
    return static_cast<unsigned char>(std::max(0.f, std::min(255.f, value)));
}

void testConvolutionIdentity() {
    Image img(3, 3);
    for (unsigned int y = 0; y < 3; ++y)
        for (unsigned int x = 0; x < 3; ++x)
            img.at(x, y) = y * 3 + x;

    std::vector<std::vector<int>> kernel = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    Convolution conv(kernel, scaleIdentity);
    Image out;
    conv.process(img, out);

    for (unsigned int y = 0; y < 3; ++y)
        for (unsigned int x = 0; x < 3; ++x)
            assert(out.at(x, y) == img.at(x, y));

    std::cout << "Convolution id kernel test passed.\n";
}


void testDrawRectangle() {
    Image img(5, 5);
    Drawing draw(img);
    draw.drawRectangle(1, 1, 3, 3, 200, false);

    assert(img.at(1, 1) == 200);
    assert(img.at(3, 1) == 200);
    assert(img.at(1, 3) == 200);
    assert(img.at(3, 3) == 200);

    std::cout << "Draw rectangle (unfilled) test passed.\n";
}


void testGammaCorrection() {
    Image img(3, 1);
    img.at(0, 0) = 0;
    img.at(1, 0) = 128;
    img.at(2, 0) = 255;

    GammaCorrection gamma(2.0f);
    Image corrected;
    gamma.process(img, corrected);

    assert(corrected.at(0, 0) == 0);
    assert(corrected.at(2, 0) == 255);

    float midIn = 128 / 255.0f;
    float expected = std::pow(midIn, 2.0f) * 255.0f;
    int correctedMid = corrected.at(1, 0);

    assert(std::abs(correctedMid - expected) <= 1);

    std::cout << "GammaCorrection test passed.\n";
}


void testPoint() {
    Point p1;
    assert(p1.x == 0 && p1.y == 0);

    Point p2(3, 4);
    assert(p2.x == 3 && p2.y == 4);

    std::stringstream ss;
    ss << p2;
    assert(ss.str() == "(3, 4)");

    Point p3;
    ss.str("10 20");
    ss >> p3;
    assert(p3.x == 10 && p3.y == 20);
}

void testRectangle() {
    Rectangle r1;
    assert(r1.x == 0 && r1.y == 0 && r1.width == 0 && r1.height == 0);

    Rectangle r2(1, 2, 3, 4);
    assert(r2.x == 1 && r2.y == 2 && r2.width == 3 && r2.height == 4);

    Point topLeft(1, 2), bottomRight(4, 6);
    Rectangle r3(topLeft, bottomRight);
    assert(r3.x == 1 && r3.y == 2 && r3.width == 3 && r3.height == 4);

    Rectangle r4 = r2 + Point(1, 1);
    assert(r4.x == 2 && r4.y == 3 && r4.width == 3 && r4.height == 4);

    Rectangle r5 = r4 - Point(1, 1);
    assert(r5.x == 1 && r5.y == 2 && r5.width == 3 && r5.height == 4);

    Rectangle a(0, 0, 4, 4);
    Rectangle b(2, 2, 4, 4);
    Rectangle inter = a & b;
    assert(inter.x == 2 && inter.y == 2 && inter.width == 2 && inter.height == 2);

    Rectangle unioned = a | b;
    assert(unioned.x == 0 && unioned.y == 0 && unioned.width == 6 && unioned.height == 6);

    Rectangle noOverlap(10, 10, 2, 2);
    Rectangle interEmpty = a & noOverlap;
    assert(interEmpty.width == 0 && interEmpty.height == 0);

    std::stringstream ss;
    ss << r2;
    assert(ss.str() == "Rectangle(1, 2, 3, 4)");

    Rectangle rParsed;
    ss.str("5 6 7 8");
    ss >> rParsed;
    assert(rParsed.x == 5 && rParsed.y == 6 && rParsed.width == 7 && rParsed.height == 8);
}

void testSize() {
    Size s1;
    assert(s1.width == 0 && s1.height == 0);

    Size s2(10, 20);
    assert(s2.width == 10 && s2.height == 20);
}



