/* 
 * File:   frame_buffer.h
 * Author: Matt
 *
 * Created on 27 February 2014, 12:15
 */

#ifndef FRAME_BUFFER_H
#define	FRAME_BUFFER_H

#include "include/colour.h"
#include <vector>

class FrameBuffer {
public:
    int width;
    int height;
    std::vector<std::vector<Colour> > buffer;
    //TODO: add base color here
    FrameBuffer(int width, int height);
    void setValue(int x, int y, Colour &colour);
    void clear(int x, int y);
    void clear();
    Colour getValue(int x, int y);

    void writePPM();
    void writePAM();
};

#endif	/* FRAME_BUFFER_H */
