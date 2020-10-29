// histo.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Austin Hester CS542o oct 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <vector>
#include <iostream>

#include "./include/cla_parse.hpp"
#include "./include/dir_func.hpp"
#include "./include/img_transform.hpp"
#include "./include/img_struct.hpp"


int
wait_key()
{
    char key_pressed = cv::waitKey(0) & 255;
    // 'q' or  <escape> quits out
    if (key_pressed == 27 || key_pressed == 'q') {
        cv::destroyAllWindows();
        return 0;
    }
    return 1;
}

int
run_histogram_function(
    cv::Mat original_image,
    std::string output_dir_path,
    std::string file_prefix,
    std::function<cv::Mat(cv::Mat)> histogram_function,
    std::string mode_string
)
{
    cv::Mat up_image;
    // run the downsample function
    original_image = histogram_function(original_image);
    std::cout << "Image size is:\t\t\t" << original_image.cols << "x" << original_image.rows << std::endl;

    std::string down_file_name = file_prefix + "_down_" + mode_string + ".png";
    write_img_to_file(original_image, output_dir_path, down_file_name);

    cv::imshow(down_file_name, original_image);
    return 1;
}

int
main(int argc, const char** argv)
{
    // CLA variables
    uint mode;

    std::string input_image;
    std::string output_dir_path;
    std::string histogram_file;

    // parse and save command line args
    int parse_result = parse_arguments(
        argc, argv,
        &input_image,
        &output_dir_path,
        &histogram_file,
        &mode
    );
    if (parse_result != 1) return parse_result;

    // open image
    img_struct_t* og_image = open_image(input_image.c_str(), true);
    
    if (og_image == NULL) {
        std::cerr << "Could not open image :(" << std::endl;
        return -1;
    }

    cv::Mat original_image = og_image->image;

    std::function<cv::Mat(cv::Mat)> histogram_function;
    std::string mode_string;

    switch (mode) {
        case 1:
            // do deletions/replications
            std::cout << "Histogram equalization." << std::endl;
            histogram_function = downsample_delete;
            mode_string = "equalization";
            break;
        case 2:
            // do the averaging/interpolation
            std::cout << "Histogram matching an image." << std::endl;
            histogram_function = downsample_average;
            mode_string = "matching_an_image";
            break;
        case 3:
            // do the pyraminds
            std::cout << "Historgram matching a file." << std::endl;
            histogram_function = downsample_pyramid;
            mode_string = "matching_a_file";
            break;
        default:
            // no
            std::cerr << "You can't do that!" << std::endl;
            return -1;
    }

    // display the original image
    cv::imshow("original", original_image);
    cv::waitKey(0);

    uint intensity_counts[256] = { 0 };    // map for intensity counts
    build_intensity_map(original_image, intensity_counts);
    uint16_t count = 0;
    for (uint i = 0; i < 256; i++) {
        ++count;
        std::cout << i << ": " << intensity_counts[i] << std::endl;
    }
    std::cout << count;
    // compute histogram of original image

    // TODO equalize the histogram

    // TODO apply the equalization

    return 0;
}
