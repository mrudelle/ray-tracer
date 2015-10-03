set filename=render

del "%filename%.png"
raytrace.exe 0.0 0.0 0.0 6 10 0 1 0 > "%filename%.ppm"
mogrify -format png "%filename%.ppm"
del "%filename%.ppm"
"%filename%.png"
pause