#ifndef RCVISUALIZER_CPP
#define RCVISUALIZER_CPP
#include "RC.cpp"
#include "RCVisualizer.hpp"
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"

// LOOP MACRO 
// #define RC_LOOP(num_of_iterations) for(int i = 0; i < num_of_ierations; i++)

//will initialize the graphics library
void RC_initialize(bool usingRC){
  CAR->SetRC(usingRC);

  if(CAR->GetRC())
  {
    //CAR->Initialize(obstaclesFileName);
  }
} 

void RC_finalize(){
  if(CAR->GetRC()){
    CAR->RCWorldImage().ShowUntilClosed("COMPLETE");
  }
  else
  {
    CAR->CreateCommandFile();
    CAR->SendFileToServer();
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