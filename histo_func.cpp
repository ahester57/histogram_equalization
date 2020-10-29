// histo_func.hpp : Historgram unctions
// Austin Hester CS542o oct 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

#include "./include/histo_func.hpp"


// take an image, and array[256]. fill array with count of intensity levels
void
build_intensity_map(cv::Mat src, uint* intensity_counts)
{
    if (src.channels() != 1) {
        std::cerr << "Not a Grayscale Image" << std::endl;
        throw "Not a Grayscale Image";
    }
    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            intensity_counts[(uint)src.at<uchar>(r, c)]++;
        }
    }
}


// normalize an intensity level array, such as the one provided by build_intensity_map.
void
normalize_histogram(uint* intensity_counts, uint num_pixels, float* normalized_histogram)
{
    for (uint i = 0; i < 256; i++) {
        normalized_histogram[i] = (float) intensity_counts[i] / num_pixels;
    }
}

// normalize an intensity level array, such as the one provided by build_intensity_map.
void
cdf_from_normalized(float* normalized_histogram, float* cdf)
{
    cdf[0] = normalized_histogram[0];
    for (uint i = 1; i < 256; i++) {
        cdf[i] = normalized_histogram[i] + cdf[i-1];
    }
}