#include "DrawingExports.h"
#include "Drawing.h"
#include "Image.h"
#include "BrightnessContrast.h"
#include "Tests.h"
IMAGECPP_API void DrawTextOnImage(const char* filepath, const char* text, int x, int y, unsigned char color) {
    Image img;
    if (!img.load(filepath)) return;

    Drawing draw(img);
    draw.drawText(x, y, text, color);
    img.savePGM(filepath);
}

IMAGECPP_API void DrawRectangleOnImage(const char* filepath, int x, int y, int width, int height, unsigned char color, bool filled) {
    Image img;
    if (!img.load(filepath)) return;

    Drawing draw(img);
    draw.drawRectangle(x, y, width, height, color, filled);
    img.savePGM(filepath);
}

IMAGECPP_API void DrawCircleOnImage(const char* filepath, int cx, int cy, int radius, unsigned char color, bool filled) {
    Image img;
    if (!img.load(filepath)) return;

    Drawing draw(img);
    draw.drawCircle(cx, cy, radius, color, filled);
    img.savePGM(filepath);
}

IMAGECPP_API void ApplyBrightnessContrast(const char* inputPath, const char* outputPath, float contrast, int brightness) {
    Image input, output;
    if (!input.load(inputPath)) return;

    BrightnessContrast bc(contrast, brightness);
    bc.process(input, output);
    output.savePGM(outputPath);
}

IMAGECPP_API void ClearImage(const char* filepath) {
    Image img;
    if (!img.load(filepath)) return;

    for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
            img.at(x, y) = 255;
        }
    }

    img.savePGM(filepath);
}

IMAGECPP_API void RunAllTests() {
    RunAllTests();
}