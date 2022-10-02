#!/bin/bash

./conways_game_of_life $(($1 / $3)) $(($2 / $3)) $4

ffmpeg -f image2 -i %05d.pbm -vf "scale=$1x$2:flags=neighbor,fps=24" -c:v libx264 -tune animation -preset medium "conways_game_of_life.mkv" 
ffmpeg -hide_banner -loglevel error -i "heatmap.pgm" -vf "scale=$1x$2:flags=neighbor" "heatmap.png"
rm "heatmap.pgm"
rm *.pbm
