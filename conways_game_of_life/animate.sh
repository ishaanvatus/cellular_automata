#!/bin/bash

./conways_game_of_life $(($1 / $3)) $(($2 / $3)) $4

ffmpeg -hide_banner -loglevel error -f image2 -i %05d.pbm -vf fps=24 -vf "scale=$1x$2:flags=neighbor" "conways_game_of_life.mkv" 
ffmpeg -hide_banner -loglevel error -i "heatmap.pgm" -vf "scale=$1x$2:flags=neighbor" "heatmap.png"
rm "heatmap.pgm"
rm *.pbm
