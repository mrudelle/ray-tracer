
/* 
 * File:   tansformationStack.h
 * Author: Matt
 *
 * Created on 08 April 2014, 16:28
 */

#ifndef TANSFORMATIONSTACK_H
#define	TANSFORMATIONSTACK_H

#include "include/transformation.h"

class TransformationStack {
public:
    Transformation* stack_head;
    
    TransformationStack();
    Transformation* Pop();
    void Push(Transformation* t);
    int Size();
    Transformation CombineStack();
private:

};

#endif	/* TANSFORMATIONSTACK_H */

