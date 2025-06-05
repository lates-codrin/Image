#pragma once
#include <iostream>

void testGammaCorrection();
void testBrightnessContrast();
void testConvolutionIdentity();
void testPoint();
void testRectangle();
void testSize();

inline void runAllTests() {
    
        testGammaCorrection();
        testBrightnessContrast();
        testConvolutionIdentity();
        testPoint();
        testRectangle();
        testSize();
        std::cout << "All tests passed.\n";
    

}
