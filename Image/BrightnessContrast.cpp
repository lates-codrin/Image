#include "BrightnessContrast.h"
#include <algorithm>
#include "Clamp.h"
BrightnessContrast::BrightnessContrast(float alpha, int beta)
    : m_alpha(alpha), m_beta(beta) {
}

void BrightnessContrast::process(const Image& src, Image& dst) {
    dst = Image(src.width(), src.height());
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            int value = static_cast<int>(m_alpha * src.at(x, y) + m_beta);
            dst.at(x, y) = static_cast<unsigned char>(clamp(value, 0, 255));
        }
    }
}
