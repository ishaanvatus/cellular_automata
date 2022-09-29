#!/bin/bash

for f in *.pbm
do 
        ffmpeg -i "$f" -vf "scale=$1x$2:flags=neighbor" "$(basename "$f" .pbm).png"
done
rm *.pbm
ffmpeg -f image2 -i %05d.png -vf fps=24 "conways_game_of_life.gif"
rm *.png
