/*MIT License

Copyright (c) 2021 Ean McGilvery, Janeen Yamak

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/*************************************************************************************************
* File: RC.hpp
* Description:
*       This file contains the creation of the RC object and all of the prototypes
*       Requires C++ 14 or later (Smart Pointers)
*
**************************************************************************************************/

#ifndef RCVISUALIZER_CPP
#define RCVISUALIZER_CPP
#include "RC.cpp"
#include "RCVisualizer.hpp"
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"

/********************************************************************************************************** 
 * Function: RC_initialize
 * Description:
 *      User will enable the RCGraphical Library or the RC Hardware Compenent
 *      And the obstacles file passed to be read and than populated
 * Parameters:
 *      bool usingRC :              'true'  enables the user to work with the Graphical Interface
 *                                  'false' enables the user to work with the Hardware Component 
 *      string obstaclesFileName:   empty string is not specified in the main file, otherwise
 *                                  a obsticles file will prepopulate the board with "rocks" and "roads"
 * Return:
 *      None 
*********************************************************************************************************/
void RC_initialize(bool usingRC,std::string obstaclesFileName){
  CAR->SetRC(usingRC);

  if(CAR->UsingGraphics())
  {
    CAR->Initialize(obstaclesFileName);
  }
} 


//EAN TODO
void RC_finalize(){
  if(CAR->UsingGraphics()){
    CAR->RCWorldImage().ShowUntilClosed("COMPLETE");
  }
  else
  {
    CAR->CreateCommandFile();
    CAR->SendFileToServer();
  }
}

/********************************************************************************************************** 
 * Function: RCAccelerate
 * Description:
 *      Increases the Speed of the RC Car by 50ms
 * Parameters:
 *      None
 * Return:
 *      None 
*********************************************************************************************************/
void RCAccelerate(){
  const int accelerateSpeed = 50; //ms
  CAR->SetSpeed(CAR->Speed()+accelerateSpeed);
}

/********************************************************************************************************** 
 * Function: RC_initialize
 * Description:
 *      Decreases the Speed of the RC Car by 50ms
 * Parameters:
 *      None
 * Return:
 *      None 
*********************************************************************************************************/
void RCDecelerate(){
  const int decelerateSpeed = 50; //ms
  CAR->SetSpeed(CAR->Speed()+decelerateSpeed);
}

/********************************************************************************************************** 
 * Function: RCMoveForward
 * Description:
 *    Moves the RC one cell Forward (in that same direction)
 * Parameters:
 *      None
 * Return:
 *      None 
*********************************************************************************************************/
void RCMoveForward(){
  CAR->MoveForward();
}

/********************************************************************************************************** 
 * Function: RCMoveBackward
 * Description:
 *    Moves the RC one cell backward (in that opposite direction)
 * Parameters:
 *      None
 * Return:
 *      None 
*********************************************************************************************************/
void RCMoveBackward(){
  CAR->MoveBack();
}

/********************************************************************************************************** 
 * Function: RCTurnLeft
 * Description:
 *    The RC Car will rotate Left of their current orientation
 * Parameters:
 *      None
 * Return:
 *      None 
*********************************************************************************************************/
void RCTurnLeft(){
  CAR->TurnLeft();
}

/********************************************************************************************************** 
 * Function: RCTurnLeft
 * Description:
 *    The RC Car will rotate to the Right of their current orientation
 * Parameters:
 *      None
 * Return:
 *      None 
*********************************************************************************************************/
void RCTurnRight(){
  CAR->TurnRight();
}


#endif