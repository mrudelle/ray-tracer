#!/bin/bash

OUT="./out/animate"
rm -r $OUT
mkdir -p $OUT

# for i in `seq -w 0 5 360`;
# do
# 	FRAME_PPM="${OUT}/frame${i}.ppm"
# 	FRAME_PNG="${OUT}/frame${i}.png"

# 	echo "$i $FRAME_PPM $FRAME_PNG"
# 	./bin/raytrace 0 0 0 1 "$i" 0 1 0 > "$FRAME_PPM"
# 	convert "$FRAME_PPM" "$FRAME_PNG"
# 	rm "$FRAME_PPM"
# done

for i in `seq -w 0 5 360`;
do
	FRAME_PPM="${OUT}/frame${i}.ppm"
	FRAME_PNG="${OUT}/frame${i}.png"

	echo "$i $FRAME_PPM $FRAME_PNG"
	./bin/raytrace 0 0 0 1 "$i" 0 1 0 > "$FRAME_PPM" &
done

wait

for i in `seq -w 0 5 360`;
do
	FRAME_PPM="${OUT}/frame${i}.ppm"
	FRAME_PNG="${OUT}/frame${i}.png"

	convert "$FRAME_PPM" "$FRAME_PNG"
	rm "$FRAME_PPM"
done

convert -delay 5 -loop 0 "${OUT}/frame*.png" "${OUT}/animate.gif"