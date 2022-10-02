#!/bin/bash


./conways_game_of_life $(($1 / $3)) $(($2 / $3)) $4
for f in *.pbm
do 
        ffmpeg -hide_banner -loglevel error -i "$f" -vf "scale=$1x$2:flags=neighbor" "$(basename "$f" .pbm).png"
done
rm *.pbm
ffmpeg -hide_banner -loglevel error -f image2 -i %05d.png -vf fps=24 "conways_game_of_life.gif" 
rm *.png
ffmpeg -hide_banner -loglevel error -i "heatmap.pgm" -vf "scale=$1x$2:flags=neighbor" "heatmap.png"
rm "heatmap.pgm"


