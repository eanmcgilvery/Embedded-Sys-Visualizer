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
  const graphics::Color backGroundColor(245,245,245);

  CAR->RCWorldImage().DrawRectangle(0,0,XDim_-1,YDim_-1,backGroundColor);
  //Horizontal Lines
  for(int i = 0; i <YDim_/pxPerCell_;i++){
    int x = pxPerCell_*NumOfHorizontalLines_-1;
    int y = i*pxPerCell_;
    CAR->RCWorldImage().DrawLine(0,y,x,y,kWallColor,wallThickness_);
  }
  //Verticle Lines
  for(int i = 0; i < XDim_/pxPerCell_;i++){
    int x = i*pxPerCell_;
    int y = pxPerCell_*NumOfVerticalLines_-1;
    CAR->RCWorldImage().DrawLine(x,0,x,y,kWallColor,wallThickness_);
  }
}

void RC::DrawRCCar(){
  DrawRCCar(position_.x_ * pxPerCell_ + pxPerCell_ / 2,
            position_.y_* pxPerCell_ + pxPerCell_ / 2);
}

void RC::DrawRCCar(int x_pixel, int y_pixel){

  switch(position_.orientation_){
    case Direction::North:{
      graphics::Color red (255,0,0);
      CAR->RCWorldImage().DrawCircle(x_pixel,y_pixel,12,red);
      
      break; 
    }
      
    case Direction::East:{
      graphics::Color green (0,255,0);
      CAR->RCWorldImage().DrawCircle(x_pixel,y_pixel,12,green);
      break; 
    }
    case Direction::West:{
      graphics::Color blue (0,0,128);
      CAR->RCWorldImage().DrawCircle(x_pixel,y_pixel,12,blue);
      break;
    }
    case Direction::South:{
      graphics::Color purple (128,0,128);
      CAR->RCWorldImage().DrawCircle(x_pixel,y_pixel,12,purple);
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
        position_.y_-=1;//Decrease x axis by 1
        // std::cout << "postion x " << position_.x_ <<" postion y" << position_.y_ << "\n";
      }
      break;
    }

    case Direction::East:{
      if(position_.x_==YDim_-1){
        std::cout << "ERROR cannot move east\n"; //y will be out of bounds
      }
      else{
        position_.x_+=1; //increase y axis by 1
        // std::cout << "postion x: " << position_.x_ <<" postion y: " << position_.y_ << "\n";
      }
      break;
    }

    case Direction::South:{
      if(position_.y_==XDim_-1){
        std::cout << "ERROR: cannot move south"; //x will be out of bounds
      }
      else{
        position_.y_+=1; //increase x by 1
        // std::cout << "postion x: " << position_.x_ <<" postion y: " << position_.y_ << "\n";
      }
      break;
    }

    case Direction::West:{
      if(position_.y_==0){
        std::cout << "ERROR: cannot move west"; //y will be out of bounds
      }
      else{
        position_.x_-=1; //Decrease y by 1
        // std::cout << "postion x: " << position_.x_ <<" postion y: " << position_.y_ << "\n";
      }
      break;
    }
  }
  PopulateBoard();
  DrawRCCar();
  Show();
}

void RC::MoveBack(){

  switch(position_.orientation_){

    case Direction::North:{
      if(position_.x_==0){
        std::cout << "ERROR cannot move north\n"; //x will be out of bounds
      }
      else{
        position_.y_+=1;//Increase y axis by 1
      }
      break;
    }

    case Direction::East:{
      if(position_.y_==YDim_-1){
        std::cout << "ERROR cannot move east\n"; //y will be out of bounds
      }
      else{
        position_.x_-=1; //decrease x axis by 1
      }
      break;
    }

    case Direction::South:{
      if(position_.x_==XDim_-1){
        std::cout << "ERROR: cannot move south"; //x will be out of bounds
      }
      else{
        position_.y_-=1; //Decrease y by 1
      }
      break;
    }

    case Direction::West:{
      if(position_.y_==0){
        std::cout << "ERROR: cannot move west"; //y will be out of bounds
      }
      else{
        position_.x_+=1; //Increase x by 1
      }
      break;
    }
  }
  PopulateBoard();
  DrawRCCar();
  Show();
}

void RC::TurnLeft(){

  switch(position_.orientation_){
    case Direction::North:{
      position_.orientation_=Direction::West;
      break;
    }
    case Direction::East:{
      position_.orientation_=Direction::North;
      break;
    }
    case Direction::South:{
      position_.orientation_=Direction::East;
      break;
    }
    case Direction::West:{
      position_.orientation_=Direction::South;
      break;
    }
  }
  PopulateBoard();
  DrawRCCar();
  Show();
}

void RC::TurnRight(){

  switch(position_.orientation_){
    case Direction::North:{
      position_.orientation_=Direction::East;
      
      break;
    }
    case Direction::East:{
      position_.orientation_=Direction::South;
      break;
    }
    case Direction::South:{
      position_.orientation_=Direction::West;
      break;
    }
    case Direction::West:{
      position_.orientation_=Direction::North;
      break;
    }
  }
  PopulateBoard();
  DrawRCCar();
  Show();
}

void RC::Show(){
  CAR->RCWorldImage().ShowForMs(3000,"RC World");
}
#endif