/**
 * @file drawingexports.h
 * @brief Contains the declarations for drawing and image manipulation functions.
 *
 * This file provides declarations for functions to manipulate images such as
 * drawing text, rectangles, circles, applying filters, and clearing the image.
 */

#pragma once
#include "Core.h"

extern "C" {
    /**
     * @brief Draws text on the specified image.
     *
     * This function allows drawing a string of text onto an image at a specified
     * position and color.
     *
     * @param filepath Path to the image file.
     * @param text The text to draw on the image.
     * @param x The x-coordinate for the text position.
     * @param y The y-coordinate for the text position.
     * @param color The color of the text (0–255).
     */
    IMAGECPP_API void DrawTextOnImage(const char* filepath, const char* text, int x, int y, unsigned char color);

    /**
     * @brief Draws a rectangle on the specified image.
     *
     * This function draws a rectangle at a given position with the specified width,
     * height, color, and whether it's filled or not.
     *
     * @param filepath Path to the image file.
     * @param x The x-coordinate for the top-left corner of the rectangle.
     * @param y The y-coordinate for the top-left corner of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @param color The color of the rectangle (0–255).
     * @param filled Boolean indicating if the rectangle should be filled or not.
     */
    IMAGECPP_API void DrawRectangleOnImage(const char* filepath, int x, int y, int width, int height, unsigned char color, bool filled);

    /**
     * @brief Draws a circle on the specified image.
     *
     * This function draws a circle at the specified center and radius with the given color.
     *
     * @param filepath Path to the image file.
     * @param cx The x-coordinate for the center of the circle.
     * @param cy The y-coordinate for the center of the circle.
     * @param radius The radius of the circle.
     * @param color The color of the circle (0–255).
     * @param filled Boolean indicating if the circle should be filled or not.
     */
    IMAGECPP_API void DrawCircleOnImage(const char* filepath, int cx, int cy, int radius, unsigned char color, bool filled);

    /**
     * @brief Applies brightness and contrast adjustments to an image.
     *
     * This function modifies the brightness and contrast of the input image and saves
     * the modified image to an output path.
     *
     * @param inputPath The path to the input image.
     * @param outputPath The path to save the modified image.
     * @param contrast The contrast factor to apply.
     * @param brightness The brightness adjustment value.
     */
    IMAGECPP_API void ApplyBrightnessContrast(const char* inputPath, const char* outputPath, float contrast, int brightness);

    /**
     * @brief Clears the image by resetting its contents.
     *
     * This function clears the image at the specified path, essentially resetting it
     * to a blank state.
     *
     * @param filepath The path to the image file.
     */
    IMAGECPP_API void ClearImage(const char* filepath);

    /**
     * @brief Runs a set of tests on the image manipulation functions.
     *
     * This function executes multiple test functions to verify the correctness
     * of image manipulation operations (e.g., drawing, applying filters, etc.).
     */
    IMAGECPP_API void runAllTests();

    /**
 * @brief Applies a convolution filter to a grayscale image.
 *
 * Applies a 3x3 convolution kernel to the image at the given path and saves the result.
 *
 * @param inputPath Path to the input image.
 * @param outputPath Path to save the filtered image.
 */

}
