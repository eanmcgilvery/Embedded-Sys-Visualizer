#ifndef RC_CPP
#define RC_CPP
#include "RC.hpp"
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include <memory>

//Setters
void RC::SetFileName(std::string fileName){ FileName_ = fileName; }

void RC::SetRC(bool usingRCGraphics){ UsingRCGraphics_ = usingRCGraphics; }

void RC::SetSpeed(int speed){ Speed_ = speed; }


//Getters
graphics::Image& RC::RCWorldImage(){ return RCWorldImage_; }

int RC::XDim(){ return XDim_; }

int RC::YDim(){ return YDim_; }

bool RC::GetRC(){ return UsingRCGraphics_; }

int RC::Speed(){ return Speed_; }

DirectionAndOrientation RC::positions(){ return position_; }

int RC::pxPerCell(){ return pxPerCell_; }


void RC::PopulateBoard(){
  
  //color constants
  const graphics::Color kWallColor(50, 50, 50);

  //Horizontal Lines
  for(int i = 0; i <YDim_/pxPerCell_;i++){
    int x = pxPerCell_*NumOfHorizontalLines_-1;
    int y = i*pxPerCell_;
    RCWorldImage().DrawLine(0,y,x,y,kWallColor,wallThickness_);
  }
  //Verticle Lines
  for(int i = 0; i < XDim_/pxPerCell_;i++){
    int x = i*pxPerCell_;
    int y = pxPerCell_*NumOfVerticalLines_-1;
    RCWorldImage().DrawLine(x,0,x,y,kWallColor,wallThickness_);
  }
}

void RC::DrawRCCar(int x_pixel, int y_pixel){

  switch(position_.orientation_){
    case Direction::North:{
      graphics::Color red (255,0,0);
      RCWorldImage().DrawCircle(x_pixel,y_pixel,12,red);
      break; 
    }
      
    case Direction::East:{
        graphics::Color orange (0,255,0);
      RCWorldImage().DrawCircle(x_pixel,y_pixel,12,orange);
      break; 
    }
    case Direction::West:{
      graphics::Color blue (0,0,128);
      RCWorldImage().DrawCircle(x_pixel,y_pixel,12,blue);
      break;
    }
    case Direction::South:{
      graphics::Color purple (128,0,128);
      RCWorldImage().DrawCircle(x_pixel,y_pixel,12,purple);
      break;
    }
  }
}

void RC::MoveForward(){

  switch(position_.orientation_){

    case Direction::North:{
      if(position_.x_==0){
        std::cout << "ERROR cannot move north\n"; //x will be out of bounds
      }
      else{
        position_.x_-=1;//Decrease x axis by 1
        //DO ANIMATION
      }
      break;
    }

    case Direction::East:{
      if(position_.y_==YDim_-1){
        std::cout << "ERROR cannot move east\n"; //y will be out of bounds
      }
      else{
        position_.y_+=1; //increase y axis by 1
        //DO ANIMATION
      }
      break;
    }

    case Direction::South:{
      if(position_.x_==XDim_-1){
        std::cout << "ERROR: cannot move south"; //x will be out of bounds
      }
      else{
        position_.x_+=1; //increase x by 1
        //DO ANIMATION
      }
      break;
    }

    case Direction::West:{
      if(position_.y_==0){
        std::cout << "ERROR: cannot move west"; //y will be out of bounds
      }
      else{
        position_.y_-=1; //Decrease y by 1
        //DO ANIMATION
      }
      break;
    }
  }
}

// void RC::TurnLeft(){

//   switch(position_.orientation_){
//     case Direction::North:{
//       position_.orientation_=Direction::East;
//       break;
//     }
//     case Direction::East:{

//       break;
//     }
//     case Direction::South:{

//       break;
//     }
//     case Direction::West:{

//       break;
//     }
//   }
// }
#endif