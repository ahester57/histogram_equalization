// histo.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Austin Hester CS542o oct 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <vector>
#include <iostream>

#include "./include/cla_parse.hpp"
#include "./include/dir_func.hpp"
#include "./include/img_transform.hpp"
#include "./include/img_struct.hpp"
#include "./include/histo_func.hpp"


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

    // display the original image
    cv::imshow("original", og_image->image);
    wait_key();

    std::string mode_string;
    cv::Mat matched_image;
    switch (mode) {
        case 1:
            // do deletions/replications
            std::cout << "Histogram equalization." << std::endl;
            mode_string = "equalization";
            matched_image = run_equalization(og_image->image);
            break;
        case 2:
            // do the averaging/interpolation
            std::cout << "Histogram matching an image." << std::endl;
            mode_string = "matching_an_image";
            break;
        case 3:
            // do the pyraminds
            std::cout << "Historgram matching a file." << std::endl;
            mode_string = "matching_a_file";
            break;
        default:
            // no
            std::cerr << "You can't do that!" << std::endl;
            return -1;
    }

    // display the equalized image
    cv::imshow(mode_string, matched_image);
    wait_key();
    // TODO use run_histogram_function() for each mode

    return 0;
}
