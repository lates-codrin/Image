#pragma once

#ifdef _IMAGE_BUILD_DLL
#define IMAGECPP_API __declspec(dllexport)
#else
#define IMAGECPP_API __declspec(dllimport)
#endif

extern "C" IMAGECPP_API void DrawTextOnImage(const char* filepath, const char* text, int x, int y, unsigned char color);
extern "C" IMAGECPP_API void DrawRectangleOnImage(const char* filepath, int x, int y, int width, int height, unsigned char color, bool filled);
extern "C" IMAGECPP_API void DrawCircleOnImage(const char* filepath, int cx, int cy, int radius, unsigned char color, bool filled);
extern "C" IMAGECPP_API void ApplyBrightnessContrast(const char* inputPath, const char* outputPath, float contrast, int brightness);
extern "C" IMAGECPP_API void ClearImage(const char* filepath);
extern "C" IMAGECPP_API void runAllTests();


