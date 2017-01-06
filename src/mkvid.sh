#!/bin/bash

tmp=0

for f in *png
do
	mv $f $(printf %03d $tmp).png
	tmp=$[tmp + 1]
done

ffmpeg -framerate 2 %03d.png vid.mp4
