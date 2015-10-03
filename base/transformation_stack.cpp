/* 
 * File:   tansformationStack.cpp
 * Author: Matt
 * 
 * Created on 08 April 2014, 16:28
 */

#include "include/transformation_stack.h"
#include "include/transformation.h"

TransformationStack::TransformationStack() 
{
    stack_head = (Transformation*)0;
}

Transformation* TransformationStack::Pop()
{
    Transformation* ret = stack_head;
    if (ret != (Transformation*)0) {
        stack_head = stack_head->next();
    }
    return ret;
}

void TransformationStack::Push(Transformation* t)
{
    t->link(stack_head);
    stack_head = t;
}

int TransformationStack::Size()
{
    Transformation* pointer = stack_head;
    int size = 0;
    while (pointer != (Transformation*)0 ) {
        size++;
        pointer = pointer->next();
    }
    return size;
}

Transformation TransformationStack::CombineStack()
{
    Transformation* pointer = stack_head;
    Transformation final;
    final.identity();
    while (pointer != (Transformation*)0 ) {
        final = pointer->composeWith(final);
        pointer = pointer->next();
    }
    return final;
}
