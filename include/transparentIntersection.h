/* 
 * File:   TransparentIntersection.h
 * Author: Matt
 *
 * Created on 15. avril 2014, 17:40
 */

#ifndef TRANSPARENTINTERSECTION_H
#define	TRANSPARENTINTERSECTION_H

#include "include/object.h"


class TransparentIntersection {
public:
    double prev_index;
    Object *curr_object;
    TransparentIntersection *next_item;
    
    TransparentIntersection();
    void set(double ind, Object *obj);
    void link(TransparentIntersection *intersec);
    TransparentIntersection *next();
    TransparentIntersection *copy();
private:

};

#endif	/* TRANSPARENTINTERSECTION_H */

