#!/bin/bash

# as framerate choose TimeStep of the simulation you are going to run

ffmpeg -framerate 100 -start_number 0 -i %04d.sgi -vcodec libx264 -profile:v high444 -threads 4 "dings.mp4"

# -f image2 - tells ffmpeg to select a group of images
# -vcodec libx264 - tells ffmpeg to output to a H.264 compliant file
# -profile:v high444 - tells libx264 to use the High 4:4:4 Predictive Lossless profile, allowing lossless encoding
# -refs 16 - tells libx264 to have 16 images stored in a buffer, so that they may be referenced by other images in the video
# -crf 0 - tells libx264 to perform a lossless encode
# -preset ultrafast - tells libx264 to prioritise encoding speed over output file size