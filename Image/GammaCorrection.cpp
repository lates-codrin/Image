#include "GammaCorrection.h"
#include "Image.h"
#include <cmath>
#include "Clamp.h"

GammaCorrection::GammaCorrection(float gamma)
    : m_gamma(gamma) {
}

void GammaCorrection::process(const Image& src, Image& dst) {
    unsigned int width = src.width();
    unsigned int height = src.height();
    dst = Image(width, height);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int pixelValue = src.at(x, y);
            float correctedValue = 255 * std::pow(pixelValue / 255.0f, m_gamma);
            dst.at(x, y) = static_cast<unsigned char>(clamp(correctedValue, 0.0f, 255.0f));
        }
    }
}
