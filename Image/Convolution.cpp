#include "Convolution.h"
#include "Image.h"
#include <algorithm>
#include <cmath>
#include "Clamp.h"

Convolution::Convolution(const std::vector<std::vector<int>>& kernel, ScaleFunction scaleFunc)
    : m_kernel(kernel), m_scaleFunc(scaleFunc) {
    m_kWidth = static_cast<int>(kernel[0].size());
    m_kHeight = static_cast<int>(kernel.size());
}

void Convolution::process(const Image& src, Image& dst) {
    unsigned int width = src.width();
    unsigned int height = src.height();
    dst = Image(width, height);

    int kCenterX = m_kWidth / 2;
    int kCenterY = m_kHeight / 2;

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int sum = 0;

            for (int ky = -kCenterY; ky <= kCenterY; ++ky) {
                for (int kx = -kCenterX; kx <= kCenterX; ++kx) {
                    int pixelX = clamp<int>(x + kx, 0, width - 1);
                    int pixelY = clamp<int>(y + ky, 0, height - 1);

                    int pixelValue = src.at(pixelX, pixelY);
                    int kernelValue = m_kernel[ky + kCenterY][kx + kCenterX];
                    sum += pixelValue * kernelValue;
                }
            }

            dst.at(x, y) = m_scaleFunc(static_cast<float>(sum));
        }
    }
}
