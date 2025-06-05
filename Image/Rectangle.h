#pragma once
#include "Point.h"
#include <iostream>

class Rectangle {
public:
    unsigned int x, y, width, height;

    Rectangle();
    Rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    Rectangle(const Point& topLeft, const Point& bottomRight);

    Rectangle operator+(const Point& offset) const;
    Rectangle operator-(const Point& offset) const;
    Rectangle operator&(const Rectangle& other) const;
    Rectangle operator|(const Rectangle& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);
    friend std::istream& operator>>(std::istream& is, Rectangle& rect);
};
