#include "Image.h"
#include <fstream>
#include <cstring>
#include <algorithm>
#include "Clamp.h"
#include <sstream>

Image::Image() : m_data(nullptr), m_width(0), m_height(0) {}

Image::Image(unsigned int w, unsigned int h) : m_width(w), m_height(h) {
    allocateData();
}

Image::Image(const Image& other) : m_width(other.m_width), m_height(other.m_height) {
    copyData(other);
}

Image::~Image() {
    release();
}

void Image::allocateData() {
    m_data = new unsigned char* [m_height];
    for (unsigned int i = 0; i < m_height; ++i)
        m_data[i] = new unsigned char[m_width]();
}

void Image::copyData(const Image& other) {
    allocateData();
    for (unsigned int i = 0; i < m_height; ++i)
        std::memcpy(m_data[i], other.m_data[i], m_width);
}

Image& Image::operator=(const Image& other) {
    if (this != &other) {
        release();
        m_width = other.m_width;
        m_height = other.m_height;
        copyData(other);
    }
    return *this;
}

Image Image::operator+(const Image& i) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y)
        for (unsigned int x = 0; x < m_width; ++x)
            result.at(x, y) = std::min(255, at(x, y) + i.at(x, y));
    return result;
}

Image Image::operator-(const Image& i) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y)
        for (unsigned int x = 0; x < m_width; ++x)
            result.at(x, y) = std::max(0, at(x, y) - i.at(x, y));
    return result;
}

Image Image::operator+(int value) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y)
        for (unsigned int x = 0; x < m_width; ++x)
            result.at(x, y) = clamp(at(x, y) + value, 0, 255);
    return result;
}

Image Image::operator-(int value) {
    return *this + (-value);
}

Image Image::operator*(int value) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y)
        for (unsigned int x = 0; x < m_width; ++x)
            result.at(x, y) = clamp(at(x, y) * value, 0, 255);
    return result;
}

bool Image::getROI(Image& roiImg, Rectangle roiRect) {
    return getROI(roiImg, roiRect.x, roiRect.y, roiRect.width, roiRect.height);
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    if (x + width > m_width || y + height > m_height) return false;
    roiImg = Image(width, height);
    for (unsigned int j = 0; j < height; ++j)
        for (unsigned int i = 0; i < width; ++i)
            roiImg.at(i, j) = at(x + i, y + j);
    return true;
}

bool Image::isEmpty() const {
    return m_data == nullptr || m_width == 0 || m_height == 0;
}

Size Image::size() const {
    return Size(m_width, m_height);
}

unsigned int Image::width() const {
    return m_width;
}

unsigned int Image::height() const {
    return m_height;
}

unsigned char& Image::at(unsigned int x, unsigned int y) {
    return m_data[y][x];
}
unsigned char Image::at(unsigned int x, unsigned int y) const {
    return m_data[y][x];
}



unsigned char* Image::row(int y) {
    return m_data[y];
}


#include <iostream>
#include <string>

bool Image::load(const std::string& imagePath) {
    std::ifstream file(imagePath);
    if (!file.is_open()) {
        std::cerr << "Error!: Cannot open file " << imagePath << std::endl;
        return false;
    }

    std::string line;

    std::getline(file, line);
    if (line != "P2") {
        std::cerr << "Bad format (expecting P2)." << std::endl;
        return false;
    }

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        else break;
    }

    std::istringstream dimStream(line);
    if (!(dimStream >> m_width >> m_height)) {
        std::cerr << "Bad image dimensions." << std::endl;
        return false;
    }

    int maxVal;
    file >> maxVal;
    if (maxVal <= 0 || maxVal > 255) {
        std::cerr << "Bad grayscale range: " << maxVal << std::endl;
        return false;
    }

    m_data = new unsigned char* [m_height];
    for (unsigned int y = 0; y < m_height; ++y)
        m_data[y] = new unsigned char[m_width];

    int pixel;
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            if (!(file >> pixel)) {
                std::cerr << "Bad end of pixel data." << std::endl;
                return false;
            }
            m_data[y][x] = static_cast<unsigned char>(clamp(pixel, 0, 255));
        }
    }

    return true;
}


bool Image::save(std::string imagePath) {
    std::ofstream file(imagePath, std::ios::binary);
    if (!file) return false;
    file.write(reinterpret_cast<const char*>(&m_width), sizeof(m_width));
    file.write(reinterpret_cast<const char*>(&m_height), sizeof(m_height));
    for (unsigned int y = 0; y < m_height; ++y)
        file.write(reinterpret_cast<const char*>(m_data[y]), m_width);
    return true;
}



bool Image::savePGM(const std::string& filename) {
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "ERR Failed to open file for saving!" << std::endl;
        return false;
    }


    file << "P2\n";
    file << m_width << " " << m_height << "\n";
    file << "255\n";

    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            file << static_cast<int>(m_data[y][x]) << " ";
        }
        file << "\n";
    }

    file.close();
    return true;
}


void Image::release() {
    if (m_data) {
        for (unsigned int i = 0; i < m_height; ++i)
            delete[] m_data[i];
        delete[] m_data;
        m_data = nullptr;
    }
    m_width = m_height = 0;
}

Image Image::zeros(unsigned int width, unsigned int height) {
    return Image(width, height);
}

std::ostream& operator<<(std::ostream& os, const Image& img) {
    for (unsigned int y = 0; y < img.m_height; ++y) {
        for (unsigned int x = 0; x < img.m_width; ++x)
            os << static_cast<int>(img.m_data[y][x]) << " ";
        os << "\n";
    }
    return os;
}
