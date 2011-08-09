#!/bin/bash

wd="`pwd | sed 's:.*/::'`"
numImages=`ls *.pgm | wc -l`

a=1

echo "Renumbering Images"

for x in *.pgm
	do echo -ne "\r$a/$numImages"
    mv $x `printf %04d $a`.pgm
    let a=$a+1
done

echo -e "\n\nCreating 30 fps video"

ffmpeg -r 30 -i %04d.pgm -b 1024k "../$wd.mpg" 1> /dev/null 2> /dev/null

mkdir real

for x in `seq -f %04g 1 20 $numImages`
    do cp $x.pgm real/
done

cd real

a=1

for x in *.pgm
    do mv $x `printf %04d $a`.pgm 2> /dev/null
    let a=$a+1
done

echo -e "\nCreating real time video\n\t(Assumes 500fps video)"

ffmpeg -r 30 -i %04d.pgm -b 1024k "../../$wd""_real.mpg" 1> /dev/null 2> /dev/null

