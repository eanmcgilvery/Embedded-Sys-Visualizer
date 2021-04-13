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

//Populate RCGraphics Board
void RC::PopulateBoard(){
  if(UsingRCGraphics_){
    //color constants
    const graphics::Color kWallColor(50, 50, 50);
    const graphics::Color backGroundColor(245,245,245);
    const graphics::Color green1(143,202,92);
    const graphics::Color green2(112,178,55);

    // std::cout << XDim_-1 <<" "<< YDim_ -1 << "\n";
    CAR->RCWorldImage().DrawRectangle(0,0,XDim_*pxPerCell_-1,YDim_*pxPerCell_-1,backGroundColor);
    //Horizontal Lines
    // std::cout << "xDim " << XDim_*pxPerCell_-1 << " yDim " << YDim_*pxPerCell_-1 << "\n";
    for (int i = 0; i <= YDim_; i++) {
      // Draw horizontal lines and indexes.
      int x = pxPerCell_ * XDim_;
      int y = i * pxPerCell_;
      // std::cout << "x " << x << " y " << y << "\n";
      CAR->RCWorldImage().DrawLine(0, y, x, y, kWallColor, wallThickness_);
      if(y%100== 0)
        CAR->RCWorldImage().DrawRectangle(0,y,x,pxPerCell_,green1);
      else
        CAR->RCWorldImage().DrawRectangle(0,y,x,pxPerCell_,green2);
    
    }
    for (int i = 0; i <= XDim_; i++) {
      // Draw vertical lines and indexes.
      int x = i * pxPerCell_;
      int y = pxPerCell_ * YDim_;
      CAR->RCWorldImage().DrawLine(x, 0, x, y, kWallColor, wallThickness_);
      
    }
  }
  
}

//Helper Function for DrawRCCar (for graphics)
void RC::DrawRCCar(){
  if(UsingRCGraphics_){
    DrawRCCar(position_.x_ * pxPerCell_ + pxPerCell_ / 2,
              position_.y_* pxPerCell_ + pxPerCell_ / 2);
  }
}

//DrawRCCar on graphics board
void RC::DrawRCCar(int x_pixel, int y_pixel){

  //depending on the direction the car is facing print out a certain pixel image to the board
  switch(position_.orientation_){
    case Direction::North:{
      
      //Offset consts to make sure the color is set in the center of the square
      const int widthOffset = 30;
      const int heightOffset = 32;

      graphics::Image upCarImage;
      upCarImage.Load("./resources/up.bmp");

      graphics::Color black(0,0,0);

      int temp = y_pixel;
      for(int i = 0; i < upCarImage.GetWidth(); i++ ){
        for(int j = 0; j < upCarImage.GetHeight(); j++){
            graphics::Color color = upCarImage.GetColor(i,j);
            if(color != black){
              CAR->RCWorldImage().SetColor(x_pixel-widthOffset,y_pixel-heightOffset,color);
            }
            y_pixel++;
            
        }
        y_pixel = temp;
        x_pixel++;
      }
      break; 
    }
      
    case Direction::East:{
      
      //Offset consts to make sure the color is set in the center of the square
      const int widthOffset = 32;
      const int heightOffset = 30;

      graphics::Image rightCarImage;
      rightCarImage.Load("./resources/right.bmp");

      graphics::Color black(0,0,0);

      int temp = y_pixel;
      for(int i = 0; i < rightCarImage.GetWidth(); i++ ){
        for(int j = 0; j < rightCarImage.GetHeight(); j++){
            graphics::Color color = rightCarImage.GetColor(i,j);
            if(color != black){
              CAR->RCWorldImage().SetColor(x_pixel-widthOffset,y_pixel-heightOffset,color);
            }
            y_pixel++;
        }
        y_pixel = temp;
        x_pixel++;
      }
      break; 
    }
    case Direction::West:{

      //Offset consts to make sure the color is set in the center of the square
      const int widthOffset = 30;
      const int heightOffset = 30;
      
      graphics::Image leftCarImage;
      leftCarImage.Load("./resources/left.bmp");

      graphics::Color black(0,0,0);

      int temp = y_pixel;
      for(int i = 0; i < leftCarImage.GetWidth(); i++ ){
        for(int j = 0; j < leftCarImage.GetHeight(); j++){
            graphics::Color color = leftCarImage.GetColor(i,j);
            if(color != black){
              CAR->RCWorldImage().SetColor(x_pixel-widthOffset,y_pixel-heightOffset,color);
            }
            y_pixel++;
        }
        y_pixel = temp;
        x_pixel++;
      }
      break;
    }
    case Direction::South:{
      
      //Offset consts to make sure the color is set in the center of the square
      const int widthOffset = 32;
      const int heightOffset = 30;

      graphics::Image downCarImage;
      downCarImage.Load("./resources/down.bmp");

      graphics::Color black(0,0,0);

      int temp = y_pixel;
      for(int i = 0; i < downCarImage.GetWidth(); i++ ){
        for(int j = 0; j < downCarImage.GetHeight(); j++){
            graphics::Color color = downCarImage.GetColor(i,j);
            if(color != black){
              CAR->RCWorldImage().SetColor(x_pixel-widthOffset,y_pixel-heightOffset,color);
            }
            y_pixel++;
        }
        y_pixel = temp;
        x_pixel++;
      }
      break;
    }
  }
  Show();
}

//Move Car Forward one space
void RC::MoveForward(){
  if(UsingRCGraphics_){
    switch(position_.orientation_){
        case Direction::North:{
          if(position_.y_==-1){
            std::cout << "ERROR cannot move north\n"; //x will be out of bounds
          }
          else{
            position_.y_-=1;//Decrease x axis by 1
          }
          break;
        }

        case Direction::East:{
          if(position_.x_==YDim_-1){
            std::cout << "ERROR cannot move east\n"; //y will be out of bounds
          }
          else{
            position_.x_+=1; //increase y axis by 1
          }
          break;
        }

        case Direction::South:{
          if(position_.y_==XDim_-1){
            std::cout << "ERROR: cannot move south"; //x will be out of bounds
          }
          else{
            position_.y_+=1; //increase x by 1
          }
          break;
        }

        case Direction::West:{
          if(position_.x_==-1){
            std::cout << "ERROR: cannot move west"; //y will be out of bounds
          }
          else{
            position_.x_-=1; //Decrease y by 1
          }
          break;
        }
      }
      PopulateBoard();
      DrawRCCar();
  }
}

//Move Car backward one space
void RC::MoveBack(){
  if(UsingRCGraphics_){
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
  }
}

//Turn Car Left
void RC::TurnLeft(){
  if(UsingRCGraphics_){
    //given what the current direction of the car, the car will change the direction appropriatly 
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
  }
}

//Changing the direction of the car to turn right
void RC::TurnRight(){
  if(UsingRCGraphics_){
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
  }
}

//displays the Car on the board for a certain ms
void RC::Show(){
  if(UsingRCGraphics_){
    CAR->RCWorldImage().ShowForMs(Speed_,"RC World");
  }
}
#endif