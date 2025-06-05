#pragma once
#include "ImageProcessing.h"

class BrightnessContrast : public ImageProcessing {
public:
    BrightnessContrast(float alpha = 1.0f, int beta = 0);
    void process(const Image& src, Image& dst) override;

private:
    float m_alpha;
    int m_beta;
};
