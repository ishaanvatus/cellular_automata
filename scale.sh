#!/bin/bash

for f in *.pbm
do 
        ffmpeg -i "$f" -vf "scale=1080x1080:flags=neighbor" "$(basename "$f" .pbm).png"
done
rm *.pbm
ffmpeg -f image2 -i %03d.png "life.gif"
rm *.png
