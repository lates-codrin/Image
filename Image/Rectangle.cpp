#include "Rectangle.h"
#include <algorithm>

Rectangle::Rectangle() : x(0), y(0), width(0), height(0) {}

Rectangle::Rectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
    : x(x), y(y), width(w), height(h) {
}

Rectangle::Rectangle(const Point& topLeft, const Point& bottomRight)
    : x(topLeft.x), y(topLeft.y),
    width(bottomRight.x > topLeft.x ? bottomRight.x - topLeft.x : 0),
    height(bottomRight.y > topLeft.y ? bottomRight.y - topLeft.y : 0) {
}

Rectangle Rectangle::operator+(const Point& offset) const {
    return Rectangle(x + offset.x, y + offset.y, width, height);
}

Rectangle Rectangle::operator-(const Point& offset) const {
    return Rectangle(x - offset.x, y - offset.y, width, height);
}

Rectangle Rectangle::operator&(const Rectangle& other) const {
    int x1 = std::max(x, other.x);
    int y1 = std::max(y, other.y);
    int x2 = std::min(x + width, other.x + other.width);
    int y2 = std::min(y + height, other.y + other.height);

    if (x2 <= x1 || y2 <= y1) return Rectangle(0, 0, 0, 0);
    return Rectangle(x1, y1, x2 - x1, y2 - y1);
}

Rectangle Rectangle::operator|(const Rectangle& other) const {
    int x1 = std::min(x, other.x);
    int y1 = std::min(y, other.y);
    int x2 = std::max(x + width, other.x + other.width);
    int y2 = std::max(y + height, other.y + other.height);

    return Rectangle(x1, y1, x2 - x1, y2 - y1);
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
    os << "Rectangle(" << rect.x << ", " << rect.y << ", " << rect.width << ", " << rect.height << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& rect) {
    is >> rect.x >> rect.y >> rect.width >> rect.height;
    return is;
}
