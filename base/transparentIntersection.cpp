/* 
 * File:   TransparentIntersection.cpp
 * Author: Matt
 * 
 * Created on 15. avril 2014, 17:40
 */

#include "include/transparentIntersection.h"

TransparentIntersection::TransparentIntersection() {
    this->next_item = (TransparentIntersection *)0 ;
}

void TransparentIntersection::set(double ind, Object *obj)
{
    this->prev_index = ind;
    this->curr_object = obj;
}

void TransparentIntersection::link(TransparentIntersection *intersec)
{
    this->next_item = intersec;
}

TransparentIntersection *TransparentIntersection::next()
{
    return this->next_item;
}

// copy the list
TransparentIntersection *TransparentIntersection::copy()
{
    if (this == (TransparentIntersection*)0)
    {
	return this;
    }
    
    TransparentIntersection *ret = new TransparentIntersection();
    ret->curr_object = this->curr_object;
    ret->prev_index = this->prev_index;
    ret->next_item = this->next_item->copy();
    return ret;
}


