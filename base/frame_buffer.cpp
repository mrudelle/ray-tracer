/*
 * Defines a frame buffer to store every color of an image and write them to a file
 */

#include <stdio.h>
#include "include/frame_buffer.h"
#include "include/colour.h"

FrameBuffer::FrameBuffer(int width, int height){
    this->width = width;
    this->height = height;
    this->buffer.resize(height, std::vector<Colour>(width));
}

void FrameBuffer::setValue(int x, int y, Colour &colour) {
    this->buffer[y][x].set(colour.red, colour.green, colour.blue, colour.alpha);
}

void FrameBuffer::clear(int x, int y) {
    this->buffer[y][x].clear();
}

void FrameBuffer::clear() {
    int x,y;

    for(y=0; y<this->height; y+=1)
    {
       for(x=0; x<this->width; x+=1)
       {
           this->buffer[y][x].clear();
       }
   }
}

Colour FrameBuffer::getValue(int x, int y) {
    return this->buffer[y][x];
}

void FrameBuffer::writePPM() {
    int x, y;
    float r, g, b;

    printf("P3\n%d %d\n255\n", this->width, this->height);

    for(y=this->height-1; y>=0; y-=1) 
    {
        for(x=0; x<this->width; x+=1) 
        {
            r = 255.0 * this->buffer[y][x].getRed();
            g = 255.0 * this->buffer[y][x].getGreen();
            b = 255.0 * this->buffer[y][x].getBlue();
            if (r > 255.0) r = 255.0;
            if (g > 255.0) g = 255.0;
            if (b > 255.0) b = 255.0;
            printf("%d %d %d\n",(int)r, (int)g, (int)b);
        }
    }
}

void FrameBuffer::writePAM() {
    // TODO: implement real method
    int x, y;
    float r, g, b;

    printf("P3\n%d %d\n255\n", this->width, this->height);

    for(y=this->height-1; y>=0; y-=1) 
    {
        for(x=0; x<this->width; x+=1) 
        {
            r = 255.0 * this->buffer[y][x].getRed();
            g = 255.0 * this->buffer[y][x].getGreen();
            b = 255.0 * this->buffer[y][x].getBlue();
            if (r > 255.0) r = 255.0;
            if (g > 255.0) g = 255.0;
            if (b > 255.0) b = 255.0;
            printf("%d %d %d\n",(int)r, (int)g, (int)b);
        }
    }
}
