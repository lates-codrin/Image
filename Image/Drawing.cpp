#include "Drawing.h"
#include <cmath>
#include <algorithm>

Drawing::Drawing(Image& image) : img(image) {}


void DrawTextOnImage(const char* filepath, const char* text, int x, int y, unsigned char color)
{
    Image img;
    if (!img.load(filepath)) return;

    Drawing draw(img);
    draw.drawText(x, y, text, color);
    img.savePGM(filepath);
}
void Drawing::drawLine(int x0, int y0, int x1, int y1, unsigned char color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        img.at(x0, y0) = color;

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void Drawing::drawRectangle(int x, int y, int width, int height, unsigned char color, bool filled) {
    if (filled) {
        for (int i = y; i < y + height; ++i) {
            drawHorizontalLine(x, x + width, i, color);
        }
    }
    else {
        drawHorizontalLine(x, x + width, y, color);
        drawHorizontalLine(x, x + width, y + height - 1, color);
        drawVerticalLine(x, y, y + height, color);
        drawVerticalLine(x + width - 1, y, y + height, color);
    }
}

void Drawing::drawCircle(int cx, int cy, int radius, unsigned char color, bool filled) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    if (filled) {
        while (x <= y) {
            drawHorizontalLine(cx - x, cx + x, cy - y, color);
            drawHorizontalLine(cx - x, cx + x, cy + y, color);
            drawHorizontalLine(cx - y, cx + y, cy - x, color);
            drawHorizontalLine(cx - y, cx + y, cy + x, color);
            x++;
            if (d < 0)
                d += 4 * x + 6;
            else {
                y--;
                d += 4 * (x - y) + 10;
            }
        }
    }
    else {
        while (x <= y) {
            drawCirclePoints(cx, cy, x, y, color, false);
            drawCirclePoints(cx, cy, y, x, color, false);
            x++;
            if (d < 0)
                d += 4 * x + 6;
            else {
                y--;
                d += 4 * (x - y) + 10;
            }
        }
    }
}

void Drawing::drawHorizontalLine(int x0, int x1, int y, unsigned char color) {
    for (int x = x0; x <= x1; ++x) {
        img.at(x, y) = color;
    }
}

void Drawing::drawVerticalLine(int x, int y0, int y1, unsigned char color) {
    for (int y = y0; y <= y1; ++y) {
        img.at(x, y) = color;
    }
}

void Drawing::drawCirclePoints(int cx, int cy, int x, int y, unsigned char color, bool filled) {
    img.at(cx + x, cy + y) = color;
    img.at(cx - x, cy + y) = color;
    img.at(cx + x, cy - y) = color;
    img.at(cx - x, cy - y) = color;
    img.at(cx + y, cy + x) = color;
    img.at(cx - y, cy + x) = color;
    img.at(cx + y, cy - x) = color;
    img.at(cx - y, cy - x) = color;
}
void Drawing::drawPoint(int x, int y, unsigned char color) {
    if (x >= 0 && x < img.width() && y >= 0 && y < img.height()) {
        img.at(x, y) = color;
    }
}

