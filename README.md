# Image Sampling
## Austin Hester
### CS 5420 - Computer Vision
### UMSL FS2020, Prof. Sanjiv Bhatia

----
### Purpose

The goal of this assignment is to learn some techniques to improve the visual quality of a given image.  

You are given an image of size M × N pixels, with k bits used for the intensity resolution.  

The image may be very dark or very bright and can be 
improved if we can redistribute the intensities to span a wider range of intensities than are being used.  

----
### Usage

```
Usage: histo.exe [params] imagefile outdir histogram_file

        -h, --help (value:true)
                show help message
        -m, --mode (value:1)
                1 = Histogram Equalization [default]
                2 = Histogram Matching an Image
                3 = Historgram matching a file

        imagefile (value:<none>)
                input image
        outdir (value:./out)
                output directory
        histogram_file (value:<none>)
                file for histogram matching

```
