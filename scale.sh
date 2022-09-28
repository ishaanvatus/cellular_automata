#!/bin/bash

for f in *.pbm
do 
        ffmpeg -i "$f" -vf "scale=1080x1080:flags=neighbor" "../png/$(basename "$f" .pbm).png"
done
