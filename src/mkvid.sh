#!/bin/bash

#tmp=0

#for f in *png
#do
#	mv $f $(printf %04d $tmp).png
#	tmp=$[tmp + 1]
#done

ffmpeg -framerate 30 -start_number 0 -i "%04d.ppm" -threads 4 "dings.mp4"
