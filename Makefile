SOURCES = $(wildcard *.cpp base/*.cpp objects/*.cpp lights/*.cpp)
OBJS = $(SOURCES:.cpp=.o)
BIN=./bin/

raytrace: $(OBJS)
	mkdir -p $(BIN)
	g++ -g $(OBJS) -o $(BIN)/raytrace -lm

%.o: %.cpp
	g++ -g -c -I. -O $< -o $@ 

raytrace.o: include/scene.h include/sphere.h include/triangle.h include/plane.h include/directional_light.h include/spot_light.h include/transformation.h include/transformation_stack.h include/frame_buffer.h

base/scene.o: include/scene.h

base/vector.o: include/vector.h

base/vertex.o: include/vertex.h

base/transformation.o: include/transformation.h	

base/transformation_stack.o: include/transformation_stack.h

base/colour.o: include/colour.h

base/material.o: include/material.h

base/ray.o: include/ray.h

base/hit.o: include/hit.h 

base/camera.o: include/camera.h

base/frame_buffer.o: include/frame_buffer.h

objects/object.o: include/object.h

objects/sphere.o: include/sphere.h

objects/triangle.o: include/triangle.h

objects/plane.o: include/plane.h

lights/light.o: include/light.h

lights/directional_light.o: include/directional_light.h

include/scene.h: include/object.h include/light.h
	touch include/scene.h

include/material.h: include/colour.h
	touch include/material.h

include/ray.h: include/vector.h include/vertex.h
	touch include/ray.h

include/transformation.h: include/vector.h include/vertex.h include/hit.h include/ray.h
	touch include/transformation.h

include/transformation_stack.h: include/transformation.h
	touch include/transformation_stack.h

include/hit.h: include/vector.h include/vertex.h
	touch include/hit.h

include/camera.h: include/vector.h include/vertex.h
	touch include/camera.h

include/frame_buffer.h: include/colour.h
	touch include/frame_buffer.h

include/light.h: include/vector.h include/vertex.h include/ray.h include/colour.h
	touch include/light.h

include/directional_light.h: include/light.h
	touch include/directional_light.h

include/object.h: include/vector.h include/vertex.h include/ray.h include/colour.h include/material.h include/hit.h
	touch include/object.h

include/sphere.h: include/object.h include/vertex.h include/hit.h
	touch include/sphere.h

include/triangle.h: include/object.h
	touch include/triangle.h

include/plane.h: include/object.h
	touch include/plane.h

clean:
	rm -f $(OBJS)