#include "Image.h"
#include "BrightnessContrast.h"
#include "GammaCorrection.h"
#include "Convolution.h"
#include <iostream>
#include <vector>
int main() {

    Image inputImage;

    if (!inputImage.load("balloons.pgm")) {
        std::cerr << "Failed to load imagee." << std::endl;
        return 1;
    }

    Image outputImage(inputImage.width(), inputImage.height());

    BrightnessContrast brightnessContrast(1.2f, 20);
    brightnessContrast.process(inputImage, outputImage);

    Image gammaImage(inputImage.width(), inputImage.height());
    GammaCorrection gamma(0.8f);
    gamma.process(outputImage, gammaImage);

    std::vector<std::vector<int>> blurKernel = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    Convolution blur(blurKernel, [](float v) {
        return static_cast<unsigned char>(std::min(255.0f, std::max(0.0f, v / 9.0f)));
        });

    Image finalImage(inputImage.width(), inputImage.height());
 

    if (!outputImage.savePGM("output_filtered.pgm")) {
        std::cerr << "Failed to save output image." << std::endl;
        return 1;
    }

    std::cout << "Filter pipeline completed and image saved!" << std::endl;
    return 0;
}
