#ifndef RCVISUALIZER_HPP
#define RCVISUALIZER_HPP
#include <iostream> 
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"

void RC_initialize(bool); //will initialize the graphics library
void RC_finalize(); //will stop animaion.
void RCTurnRight(); //will move he rc 90 degrees to right 
void RCTurnLeft(); //will move the rc 90 degress to left
void RCMoveForward(); //will move rc forward an N number of cells
void RCMoveBackward(); //will move rc backwards an N number of cells
void RCAccelerate(); //will increase animaion speed by 50 ms DONE. 
void RCDecelerate(); //will decrease animation speed b 50 ms DONE. 

#endif 
