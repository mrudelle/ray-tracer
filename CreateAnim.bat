del /r round
mkdir round
for /l %%x in (360, 5, 710) do (
   	echo %%x
	raytrace.exe 0 0 0 6 %%x 0 1 0 > round\image%%x.ppm
	mogrify -format png round\image%%x.ppm
	del round\image%%x.ppm
)
convert   -delay 5   -loop 0   round\image*.png   animate.gif
echo "----------- ANIMATION DONE -----------"
pause