#! bin/sh

OUT="./out"
OUT_PPM="$OUT/img.pam"
OUT_PNG="$OUT/img.png"

mkdir -p $OUT

rm $OUT_PPM
rm $OUT_PNG

# Best for city
./bin/raytrace 0.0 -0.1 0.0 2.45 35 0 1 0 > $OUT_PPM
convert $OUT_PPM $OUT_PNG

#rm $OUT_PPM
open $OUT_PNG
