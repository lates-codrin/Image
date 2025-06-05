#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include "Size.h"
#include "Point.h"
#include "Rectangle.h"

class Image {
public:
    Image();
    Image(unsigned int width, unsigned int height);
    Image(const Image& other);
    ~Image();

    Image& operator=(const Image& other);
    Image operator+(const Image& i);
    Image operator-(const Image& i);
    Image operator+(int value);
    Image operator-(int value);
    Image operator*(int value);
    bool getROI(Image& roiImg, Rectangle roiRect);
    bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    bool isEmpty() const;
    Size size() const;
    unsigned int width() const;
    unsigned int height() const;

    unsigned char& at(unsigned int x, unsigned int y);
    unsigned char at(unsigned int x, unsigned int y) const;
    

    //unsigned char& at(Point pt);
    unsigned char* row(int y);
    bool load(const std::string& imagePath);
    bool save(std::string imagePath);
    bool savePGM(const std::string& filename);
    void release();
    static Image zeros(unsigned int width, unsigned int height);

    friend std::ostream& operator<<(std::ostream& os, const Image& img);

private:
    unsigned int m_width;
    unsigned int m_height;
    unsigned char** m_data;

    void allocateData();
    void copyData(const Image& other);
};
