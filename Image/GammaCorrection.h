#pragma once
#include "ImageProcessing.h"

class GammaCorrection : public ImageProcessing {
public:
    GammaCorrection(float gamma = 1.0f);
    void process(const Image& src, Image& dst) override;

private:
    float m_gamma;
};
