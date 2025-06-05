#include "Point.h"

Point::Point() : x(0), y(0) {}
Point::Point(unsigned int x, unsigned int y) : x(x), y(y) {}

std::ostream& operator<<(std::ostream& os, const Point& pt) {
    os << "(" << pt.x << ", " << pt.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& pt) {
    is >> pt.x >> pt.y;
    return is;
}
