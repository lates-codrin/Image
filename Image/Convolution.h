#pragma once
#include "ImageProcessing.h"
#include <vector>
#include <functional>

class Convolution : public ImageProcessing {
public:
    using ScaleFunction = std::function<unsigned char(float)>;

    Convolution(const std::vector<std::vector<int>>& kernel, ScaleFunction scaleFunc);
    void process(const Image& src, Image& dst) override;

private:
    std::vector<std::vector<int>> m_kernel;
    ScaleFunction m_scaleFunc;
    int m_kWidth;
    int m_kHeight;
};
