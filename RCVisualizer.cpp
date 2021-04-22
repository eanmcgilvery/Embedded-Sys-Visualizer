#ifndef RCVISUALIZER_CPP
#define RCVISUALIZER_CPP
#include "RC.cpp"
#include "RCVisualizer.hpp"
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"

// LOOP MACRO 
// #define RC_LOOP(num_of_iterations) for(int i = 0; i < num_of_ierations; i++)

//will initialize the graphics library
void RC_initialize(std::string fileName, std::string obstaclesFileName, bool usingRCGraphics){
  CAR->SetFileName(fileName);
  CAR->SetRC(usingRCGraphics);

  if(CAR->GetRC() == true){
    CAR->Initialize(obstaclesFileName);
  }
} 

void RC_finalize(){
  if(CAR->GetRC() == true){
    CAR->RCWorldImage().ShowUntilClosed("COMPLETE");
  }
}

void RC_accelerate(){
  const int accelerateSpeed = 50; //ms
  CAR->SetSpeed(CAR->Speed()+accelerateSpeed);
}

void RC_decelerate(){
  const int decelerateSpeed = 50; //ms
  CAR->SetSpeed(CAR->Speed()+decelerateSpeed);
}

void RCMoveForward(){
  CAR->MoveForward();
}

void RCMoveBackward(){
  CAR->MoveBack();
}
void RCTurnLeft(){
  CAR->TurnLeft();
}

void RCTurnRight(){
  CAR->TurnRight();
}


#endif