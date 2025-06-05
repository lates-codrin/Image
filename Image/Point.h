#pragma once
#include <iostream>

class Point {
public:
    unsigned int x, y;

    Point();
    Point(unsigned int x, unsigned int y);

    friend std::ostream& operator<<(std::ostream& os, const Point& pt);
    friend std::istream& operator>>(std::istream& is, Point& pt);
};
