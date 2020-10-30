// cla_parse.cpp : Parse given command line arguments.
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <iostream>

#include "./include/cla_parse.hpp"


// parse command line arguments
int
parse_arguments(
    int argc,
    const char** argv,
    std::string* input_image,
    std::string* histogram_file,
    uint* mode
) {
    cv::String keys =
        "{@imagefile      |<none>| input image}"             // input image is the first argument (positional)
        "{@histogram_file |<none>| file for histogram matching}"
        "{mode m          |1     | 1 = Histogram Equalization [default]\n\t\t2 = Histogram Matching an Image\n\t\t3 = Historgram Matching a File}"
        "{help h          |      | show help message}";           // optional

    cv::CommandLineParser parser(argc, argv, keys);

    if (parser.has("h")) {
        parser.printMessage();
        return 0;
    }

    if (!parser.check()) {
        parser.printErrors();
        parser.printMessage();
        return -1;
    }

    try {
        *input_image = (std::string) parser.get<std::string>(0).c_str();
    } catch (...) {
        std::cerr << "Failed to parse input image argument!:" << std::endl;
        return -1;
    }

    try {
        *histogram_file = (std::string) parser.get<std::string>(1).c_str();
    } catch (...) {
        std::cerr << "Failed to parse output histogram_file argument!:" << std::endl;
        return -1;
    }

    try {
        *mode = (uint) parser.get<uint>("m") ? parser.get<uint>("m") : 1;
        if (*mode < 1 || *mode > 3) {
            std::cerr << "Mode can only be from 1 to 3." << std::endl;
            return -1;
        }
    } catch (...) {
        std::cerr << "Failed to parse sampling_method argument." << std::endl;
        return -1;
    }

    return 1;
}
