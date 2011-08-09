#!/bin/bash

# 1: Working Directory 2: Frame Increment 3: Frame rate

if [[ $# -ne 3 ]]; then
    echo "videos.sh: invalid number of arguments"
    echo "Usage: videos.sh working_directory frame_increment frame_rate"
    exit
fi 

cd $1

wd="`pwd | sed 's:.*/::'`"      #last folder in working directory
numImages=`ls *.pgm | wc -l`    #index of last image in directory
let numImages=$numImages-1      

mkdir tmp

for x in `seq -f %05g 0 $2 $numImages`  #skip frames to match desired
    do ln $x.pgm tmp/                   #frame rate of movie
done

cd tmp

a=0                                     #rename images sequentially
for x in *.pgm
    do mv $x `printf %05d $a`.pgm 2> /dev/null
    let a=$a+1
done

#output video
ffmpeg -r $3 -i %05d.pgm -b 1024k "../../$wd.mpg" 1> /dev/null 2> /dev/null

