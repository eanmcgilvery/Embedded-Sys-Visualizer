#ifndef RCVISUALIZER_CPP
#define RCVISUALIZER_CPP
#include "RC.cpp"
#include "RCVisualizer.hpp"
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"

//LOOP MACRO 
#define RC_LOOP(num_of_iterations) for(int i = 0; i < num_of_ierations; i++)

//will initialize the graphics library
void RC_initialize(std::string fileName, bool usingRC){
  CAR->SetFileName(fileName);
  CAR->SetRC(usingRC);

  if(CAR->GetRC() == true){
    CAR->RCWorldImage().Initialize(CAR->YDim(), CAR->XDim());
  }
    
} 

void RC_finalize(){
  CAR->RCWorldImage().ShowUntilClosed();
}

void RC_accelerate(){
  const int accelerateSpeed = 50; //ms
  CAR->SetSpeed(CAR->Speed()+accelerateSpeed);
}

void RC_decelerate(){
  const int decelerateSpeed = 50; //ms
  CAR->SetSpeed(CAR->Speed()+decelerateSpeed);
}

void CreateWorld(){
  CAR->PopulateBoard();
}

void DrawRC(){
  CAR->DrawRCCar(CAR->positions().x_*CAR->pxPerCell()+CAR->pxPerCell()/2,
                 CAR->positions().y_*CAR->pxPerCell()+CAR->pxPerCell()/2);
}

void RCMoveForward(){
  CAR->MoveForward();
}


#endif