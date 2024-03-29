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
* File: RC.cpp
* Description:
*       This file contains all the major compenents of the RC Graphicial Library and the RC Hardware Component
*       Requires C++ 14 or later (Smart Pointers)
*
**************************************************************************************************/

#ifndef RC_CPP
#define RC_CPP
#include "RC.hpp"
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "orientation.h"
#include <memory>
#include <fstream> //std::ofstream
#include <curl/curl.h>
#include <sys/stat.h>
#include <math.h>


/*====================================================================================================================*/
/* MUTATORS                                                                                                           */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: SetRC
 * Description:
 *      This function shall decide whether the user would like to use the Graphical Interface or the Hardware Component  
 * Parameters:
 *      bool usingRCGraphics : 'true'  enables the user to work with the Graphical Interface
 *                             'false' enables the user to work with the Hardware Component 
 * Return:
 *      None 
***************************************************************************/
void RC::SetRC(bool usingRCGraphics){ UsingRCGraphics_ = usingRCGraphics; }

/*************************************************************************** 
 * Function: SetSpeed
 * Description:
 *      This Function sets the speed of the RC Car for the Graphical Interface  
 * Parameters:
 *      int speed : the speed of the car in ms
 * Return:
 *      None 
***************************************************************************/
void RC::SetSpeed(int speed){ Speed_ = speed; }

/*====================================================================================================================*/
/* END OF MUTATORS                                                                                                           */
/*====================================================================================================================*/


/*====================================================================================================================*/
/* ACCESSORS                                                                                                           */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: RCWorldImage
 * Description:
 *      Returns the underlying image object  
 * Parameters:
 *      None
 * Return:
 *      Image:  the underlying image object 
***************************************************************************/
graphics::Image& RC::RCWorldImage(){ return RCWorldImage_; }

/*************************************************************************** 
 * Function: XDim
 * Description:
 *      Returns the X Dimention of the graphical interface  
 * Parameters:
 *      None
 * Return:
 *      int: The X Dimention of the graphical interface  
***************************************************************************/
int RC::XDim(){ return XDim_; }

/*************************************************************************** 
 * Function: YDim
 * Description:
 *      Returns the Y Dimention of the graphical interface  
 * Parameters:
 *      None
 * Return:
 *      int: The Y Dimention of the graphical interface  
***************************************************************************/
int RC::YDim(){ return YDim_; }

/*************************************************************************** 
 * Function: UsingGraphics
 * Description:
 *      Returns true/false depending on whether the use of the graphical interface has been enabled or not
 * Parameters:
 *      None
 * Return:
 *      bool:  'true': the graphical interface is enabled
 *             'false': the RC Hardware compenent is enabled 
***************************************************************************/
bool RC::UsingGraphics(){ return UsingRCGraphics_; }

/*************************************************************************** 
 * Function: Speed
 * Description:
 *      Returns the speed in ms
 * Parameters:
 *      None
 * Return:
 *      int: the speed in ms 
***************************************************************************/
int RC::Speed(){ return Speed_; }

/*************************************************************************** 
 * Function: positions
 * Description:
 *      Returns the current x and y value of the car
 * Parameters:
 *      None
 * Return:
 *      DirectionAndOrientation: is an object that contains the x and y value of the RC car's position
***************************************************************************/
DirectionAndOrientation RC::positions(){ return position_; }

/*************************************************************************** 
 * Function: pxPerCell
 * Description:
 *      Returns the number of pixels per cell
 * Parameters:
 *      None
 * Return:
 *      int: the number of pixels per cell
***************************************************************************/
int RC::pxPerCell(){ return pxPerCell_; }
/*====================================================================================================================*/
/* END OF ACCESSORS                                                                                                           */
/*====================================================================================================================*/


/*====================================================================================================================*/
/* HELPER FUNCTIONS (NOT TO BE EXPLICITLY CALLED)                                                                     */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: DrawRCCar
 * Description:
 *      Passes the X and Y px position that represent the middle of a cell
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
void RC::DrawRCCar(){
  if(UsingRCGraphics_){
    DrawRCCar(position_.x_ * pxPerCell_ + pxPerCell_ / 2,
              position_.y_* pxPerCell_ + pxPerCell_ / 2);
  }
}

/*************************************************************************** 
 * Function: ParseWorldFileError
 * Description:
 *      This Function will display an error if the syntax of the file is not correct
 * Parameters:
 *      error_text: is a description of what caused this function to be prompted
 *      line_number: specifies which line number caused the syntax error in the 'file' object
 * Return:
 *      None
***************************************************************************/
void RC::ParseWorldFileError(std::string error_text, int line_number) {
  if (line_number > 0) {
    error_text += " (line " + std::to_string(line_number) + ")";
  }
  std::cout << error_text << std::endl << std::flush;
  throw error_text;
}

/*************************************************************************** 
 * Function: ParsePosition
 * Description:
 *      Grabs the X and Y position of an object
 * Parameters:
 *      fstream file: is a file object that is being read
 *      int line_number: specifies which line you are currently reading
 * Return:
 *      DirectionAndOrientation: returns the coordinates of the object you read from the file
***************************************************************************/
DirectionAndOrientation RC::ParsePosition(std::fstream& file,int line_number)  {
  char open_paren, comma, closed_paren;
  int x, y;
  if (!(file >> open_paren >> x >> comma >> y >> closed_paren)) {
    ParseWorldFileError("Error reading position", line_number);
  }
  CheckParsePosition(open_paren, comma, closed_paren, line_number);
  DirectionAndOrientation result;
  // Convert y in the file to y on-screen. In the file, (1, 1) is the
  // bottom left corner.
  // In car coordinates, that's (0, YDim_ - 1).
  result.y_ = YDim_ - y;
  result.x_ = x - 1;
  return result;
}

/*************************************************************************** 
 * Function: ParsePositionAndOrientation
 * Description:
 *      Reads the Direction the RC Car
 * Parameters:
 *      fstream file: is a file object that is being read
 *      int line_number: specifies which line you are currently reading
 * Return:
 *      DirectionAndOrientation: returns the orientation of the RC Car
***************************************************************************/
DirectionAndOrientation RC::ParsePositionAndOrientation(std::fstream& file, int line_number) {
  DirectionAndOrientation result = ParsePosition(file, line_number);
  std::string direction;
  if (!(file >> direction)) {
    ParseWorldFileError("Error reading orientation", line_number);
  }
  // Ensure the first character is lower cased.
  direction[0] = tolower(direction[0]);
  if (direction == "north") {
    result.orientation_ = Direction::North;
  } else if (direction == "east") {
    result.orientation_ = Direction::East;
  } else if (direction == "south") {
    result.orientation_ = Direction::South;
  } else if (direction == "west") {
    result.orientation_ = Direction::West;
  } else {
    ParseWorldFileError("Unknown orientation " + direction, line_number);
  }
  return result;
}

/*************************************************************************** 
 * Function: CheckParsePosition
 * Description:
 *      Checks to see if the following Syntax "(,)" is valid in the file
 * Parameters:
 *      char open_paren: '('
 *      char comm: ','
 *      char closed_paren: ')'
 *      int line_number: is the line number the pareser is currently at
 * Return:
 *      None
***************************************************************************/
void RC::CheckParsePosition(char open_paren, char comma, char closed_paren,int line_number) {
  if (open_paren != '(') {
    ParseWorldFileError("Invalid syntax: expected open parenthesis but found " +
                            std::string(1, open_paren),
                        line_number);
  }
  if (comma != ',') {
    ParseWorldFileError(
        "Invalid syntax: expected a comma but found " + std::string(1, comma),
        line_number);
  }
  if (closed_paren != ')') {
    ParseWorldFileError(
        "Invalid syntax: expected closed parenthesis but found " +
            std::string(1, closed_paren),
        line_number);
  }
}
/*====================================================================================================================*/
/* END OF HELPER FUNCTIONS                                                                   */
/*====================================================================================================================*/


/*====================================================================================================================*/
/* OTHER FUNCTIONS USED TO MANIPULATE THE IMAGE                                                                     */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: PopulateBoard
 * Description:
 *      Creates the graphical interface a user may be interacting with. It may contain rocks, roads if it was initialized.
 *      By Default the grpahical interface will contain a blank grid with the RC Car image starting at the Top Left of the grid.
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
void RC::PopulateBoard(){
  if(UsingRCGraphics_){
    //color constants
    const graphics::Color kWallColor(50, 50, 50);
    const graphics::Color backGroundColor(245,245,245);
    const graphics::Color green1(143,202,92);
    const graphics::Color green2(112,178,55);
    const graphics::Color grey(128, 126, 120);
    const graphics::Color yellow (247,181,0);
    const int lineThickness = 4;   
    const int wallThickness_ = 3;
    const int fontsize = 16;
    const int margin = 32;
    

    RCWorldImage_.DrawRectangle(0,0,XDim_*pxPerCell_-1,YDim_*pxPerCell_-1,backGroundColor);
    //Horizontal Lines
    for (int i = 0; i <= YDim_; i++) {
      // Draw horizontal lines and indexes.
      int x = pxPerCell_ * XDim_;
      int y = i * pxPerCell_;
      RCWorldImage_.DrawLine(0, y, x, y, kWallColor, wallThickness_);
      
      //Adding Green Horizonal lines that look like grass
      if(y < YDim_*pxPerCell_){
        if(y%100==0)
          RCWorldImage_.DrawRectangle(0,y,x,pxPerCell_,green1);
        else
          RCWorldImage_.DrawRectangle(0,y,x,pxPerCell_,green2);
      }
      //Add the index to the cell 
      if (i < YDim_) {
        RCWorldImage_.DrawText(x + fontsize / 2, y + (pxPerCell_ - fontsize) / 2,
                        std::to_string(YDim_ - i), fontsize, kWallColor);
      }

    }

    //Verticle Lines
    for (int i = 0; i <= XDim_; i++) {
      // Draw vertical lines and indexes.
      int x = i * pxPerCell_;
      int y = pxPerCell_ * YDim_;
      RCWorldImage_.DrawLine(x, 0, x, y, kWallColor, wallThickness_);
      //adding the text of the index of the specified cell
      if (i < XDim_) {
        RCWorldImage_.DrawText(x + (pxPerCell_ - fontsize) / 2, y + fontsize / 2,
                       std::to_string(i + 1), fontsize, kWallColor);
      }
    }

    // Adding Roads and Rocks at to the Grids
    for(int i = 0; i < XDim_; i++){
      for(int j = 0; j < YDim_; j++){
        int x_center = i * pxPerCell_ + pxPerCell_ / 2;
        int y_center = j * pxPerCell_ + pxPerCell_ / 2;
        Cell& cell = world_[i][j];
        int rockCount = cell.GetNumOfRocks();

        //Draw the Roads
        if(cell.containsRoadNorth()){
          //Set the positions for the upper left corner for the rectangle drawing
          int x =i * pxPerCell_ + pxPerCell_/2;
          int y = j * pxPerCell_;
        
          //Set the height of the rectangle 
          int height = (YDim_-1) - j;

          //Draw the road and a Yellow Line in the middle of the road
          RCWorldImage_.DrawRectangle(i*pxPerCell_, 0, 1*pxPerCell_+1,(j+1)*pxPerCell_,grey);
          RCWorldImage_.DrawLine(x,(j+1)*pxPerCell_,x,0, yellow,lineThickness);
        }

        if(cell.containsRoadEast()){
          //Set the positions for the upper left corner for the rectangle drawing
          int x = i * pxPerCell_;
          int y = j * pxPerCell_+pxPerCell_/2;
          
          //Set the width of the Rectangle
          int width = XDim_ -i;
          
          //Draw the road and a Yellow Line in the middle of the road
          RCWorldImage_.DrawRectangle(i*pxPerCell_, j*pxPerCell_, width*pxPerCell_-1,1*pxPerCell_-1,grey);
          RCWorldImage_.DrawLine(x,y,XDim_*pxPerCell_-1,y  , yellow,4);
        }

        if(cell.containsRoadSouth()){
          //Set the positions for the upper left corner for the rectangle drawing
          int x =i * pxPerCell_ + pxPerCell_/2;
          int y = j * pxPerCell_;

          //Set the height of the rectangle 
          int height = YDim_ - j;

          //Draw the road and a Yellow Line in the middle of the road
          RCWorldImage_.DrawRectangle(i*pxPerCell_, j*pxPerCell_, 1*pxPerCell_+1,height*pxPerCell_,grey);
          RCWorldImage_.DrawLine(x,y,x, YDim_*pxPerCell_-1 , yellow,4);
        }

        if(cell.containsRoadWest()){
          //Set the positions for the upper left corner for the rectangle drawing
          int x = i * pxPerCell_;
          int y = j * pxPerCell_+pxPerCell_/2;

          //Draw the road and a Yellow Line in the middle of the road
          RCWorldImage_.DrawRectangle(0, j*pxPerCell_, (i+1)*pxPerCell_,1*pxPerCell_,grey);
          RCWorldImage_.DrawLine((i+1)*pxPerCell_,y,0,y , yellow,4);
        }

        //Draw Rocks and Number of Rocks
        if(rockCount > 0){
          //Draw the rocks. Rocks are stacked so you cant tell if theres 
          //more than one in a stack

          //Offset consts to make sure the color is set in the center of the square
          const int widthOffset = 15;
          const int heightOffset = 15;

          graphics::Image rockImage;
          rockImage.Load("./resources/rock.bmp");

          graphics::Color black(0,0,0);

          //Iterate throught the rock image and print it on the World
          int temp = y_center;
          for(int i = 0; i < rockImage.GetWidth(); i++ ){
            for(int j = 0; j < rockImage.GetHeight(); j++){
                graphics::Color color = rockImage.GetColor(i,j);
                
                //Get rid of the black pixels that boarders the image
                if(color != black){
                  RCWorldImage_.SetColor(x_center-widthOffset,y_center-heightOffset,color);
                }
                y_center++;
            }
            y_center = temp;
            x_center++;
          }
          
          if (rockCount > 1) {
          // Draw the rock count in the cell if it's biger than 1.
          RCWorldImage_.DrawText(x_center-widthOffset- fontsize / 4, y_center - heightOffset - fontsize / 2,
                                      std::to_string(rockCount), fontsize, kWallColor);
          }
        }
      }
    }
  }
}

/*************************************************************************** 
 * Function: Initialize
 * Description:
 *      parces through a file and stores the "roads", "rocks", "RC", 
 *      in the associated index of a 2D vector 
 * Parameters:
 *     string filename: is the filename that the user can pass so we can 
 *                       prepopulate the board with "rocks" and "roads"
 * Return:
 *      None
***************************************************************************/
void RC::Initialize(std::string filename){
  if(UsingRCGraphics_){
    
    if (!filename.size()) {
      // No file. Default 10x10 blank world with no roads or rocks.
      for (int i = 0; i < XDim_; i++) {
        world_.push_back(std::vector<Cell>());
        for (int j = 0; j < YDim_; j++) {
          world_[i].push_back(Cell());
        }
    }
      position_.orientation_ = East;
    }
    else { //If file exists, read the file
      std::fstream world_file;
      try {
        world_file.open(filename);
      } catch (std::ifstream::failure e) {
        ParseWorldFileError("Error opening file " + filename, -1);
      }
      if (!world_file.is_open()) {
        ParseWorldFileError("Error opening file " + filename, -1);
      }
      std::string line;
      int line_number = 1;

      //File keywords
      const std::string dimension_prefix = "Dimension:";
      const std::string rock_prefix = "Rock:";
      const std::string road_prefix = "Road:";
      const std::string rccar_prefix = "RCCar:";

      //Checks if "Dimensions" exists within the file
      std::string line_prefix;
      char open_paren, comma, closed_paren;
      if (!(world_file >> line_prefix >> open_paren >> XDim_ >> comma >>
            YDim_ >> closed_paren)) {
        ParseWorldFileError(
            "Could not parse world dimensions from the first line", line_number);
      }
      if (line_prefix != dimension_prefix) {
        ParseWorldFileError("Could not find \"Dimension:\" in first line",
                            line_number);
      }
      CheckParsePosition(open_paren, comma, closed_paren, line_number);

      //throws an error if the "Dimentions " is less then 1 cell wide or tall
      if (XDim_ < 1 || YDim_ < 1) {
        ParseWorldFileError(
            "Cannot load a world less than 1 cell wide or less than 1 cell "
            "tall",
            line_number);
      }
      for (int i = 0; i < XDim_; i++) {
        world_.push_back(std::vector<Cell>());
        for (int j = 0; j < YDim_; j++) {
         world_[i].push_back(Cell());
        }
      }

      //Read the rest of the file to get rocks and road locations.
      while (world_file >> line_prefix) {
        line_number++;
        if (line_prefix == road_prefix) {
        DirectionAndOrientation wall = ParsePositionAndOrientation(world_file, line_number);
        world_[wall.x_][wall.y_].AddRoad(wall.orientation_);
        }
        else if (line_prefix == rock_prefix) {
          DirectionAndOrientation rock = ParsePosition(world_file, line_number);
          int count;
          if (!(world_file >> count)) {
           ParseWorldFileError("Error reading Beeper count", line_number);
          }
          world_[rock.x_][rock.y_].SetNumOfRock(count);
          world_[rock.x_][rock.y_].setContainsRock(true);
        }
        else if (line_prefix == rccar_prefix) {
          position_ = ParsePositionAndOrientation(world_file, line_number);
        } 
        else{
          ParseWorldFileError("Unexpected token in file: " + line_prefix, line_number);
          break;
        }

      }
      world_file.close();
    }

    const int margin = 32;
    int min_width = 5 * pxPerCell_ + margin;
    RCWorldImage_.Initialize(std::max(XDim_*pxPerCell_+margin, min_width),YDim_*pxPerCell_+margin);
    PopulateBoard();
    Show();
    DrawRCCar();
  }
}

/*************************************************************************** 
 * Function: DrawRCCar
 * Description:
 *      Draws the RC Car given the position and the orientation of the car
 * Parameters:
 *      int x_pixel: is the X position of the RC Car
 *      int y_pixel: is the Y position of the RC Car
 * Return:
 *      None
***************************************************************************/
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
              RCWorldImage_.SetColor(x_pixel-widthOffset,y_pixel-heightOffset,color);
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
              RCWorldImage_.SetColor(x_pixel-widthOffset,y_pixel-heightOffset,color);
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
              RCWorldImage_.SetColor(x_pixel-widthOffset,y_pixel-heightOffset,color);
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
              RCWorldImage_.SetColor(x_pixel-widthOffset,y_pixel-heightOffset,color);
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

/*************************************************************************** 
 * Function: MoveForward
 * Description:
 *     The RC Car will move one cell forward in their current direction
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
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
  else
  {
    commandVec_.push_back('F');
  }
}

/*************************************************************************** 
 * Function: MoveBack
 * Description:
 *     The RC Car will move one cell backward in the opposite direction
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
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
  else
  {
    commandVec_.push_back('B');
  }
}

/*************************************************************************** 
 * Function: TurnLeft
 * Description:
 *     The RC Car will rotate Left of their current orientation
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
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
  else
  {
    commandVec_.push_back('L');
  }
}

/*************************************************************************** 
 * Function: MoveRight
 * Description:
 *     The RC Car will rotate to the Right of their current orientation
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
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
  else
  {
    commandVec_.push_back('R');
  }
}

/*************************************************************************** 
 * Function: MoveForward
 * Description:
 *     Display the current instance of the car for N ms
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
void RC::Show(){
  if(UsingRCGraphics_){
    RCWorldImage_.ShowForMs(Speed_,"RC World");
  }
}

void RC::CreateCommandFile()
{
  // Extra insurance this function is only called when using the RC
  if(UsingRCGraphics_)
    return;

  // Attempt to create file and write to it
  try
  {
    std::ofstream fout(fileName_);
   
    // Loop through and vector and print it to the file.
    for(int i = 0; i < commandVec_.size(); i++)
      fout << commandVec_[i];
    
    fout.close();
  }
  catch(std::ofstream::failure e)
  {
    std::cerr << e.what() << '\n';
  }

  for(int i = 0; i < commandVec_.size(); i++)
      std::cout << "VEC: " << commandVec_[i] << '\n';
}

void RC::SendFileToServer()
{
  // Check to ensure the file we wish to send exists
 // std::ifstream fin("temp.txt");
  //if(!fin.good())
  //  throw std::runtime_error("ERROR: Couldn't find file to send to server.");
  
  CURL* curl_ptr;
  CURLcode res;
  struct stat  fileInfo;
  curl_off_t u_speed, total_speed;


  // Open the file and ensure contents are okay
  FILE* fd = fopen(fileName_.c_str(), "rb");
  if(!fd || fstat(fileno(fd), &fileInfo) != 0) {throw std::runtime_error("FAILED TO OPEN FILE or FILE IS EMPTY");}


  // Initlaize Windows socket stuff
  curl_global_init(CURL_GLOBAL_ALL);

  // Initalize curl handle
  curl_ptr = curl_easy_init();

  if(curl_ptr)
  {
    // Give Curl the server address
    curl_easy_setopt(curl_ptr, CURLOPT_URL, "http://107.221.75.87/");

    // Tell curl we're going to be "Uploading" to the URL
    curl_easy_setopt(curl_ptr, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl_ptr, CURLOPT_READDATA, fd);
    curl_easy_setopt(curl_ptr, CURLOPT_VERBOSE, 1L);

    // Set the File Size to what we shall upload
    curl_easy_setopt(curl_ptr, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fileInfo.st_size);

    // Perform the Request, and grab the return code
    res = curl_easy_perform(curl_ptr);

    if(res != CURLE_OK)
      std::cout << "CURL FAILED: " << curl_easy_strerror(res) << '\n'; 
    else
    {
      curl_easy_getinfo(curl_ptr, CURLINFO_SPEED_UPLOAD_T, &u_speed);
      curl_easy_getinfo(curl_ptr, CURLINFO_TOTAL_TIME_T, &total_speed);

      fprintf(stderr, "UPLOAD SPEED: %" CURL_FORMAT_CURL_OFF_T " bytes/sec during %"
              CURL_FORMAT_CURL_OFF_T ".%01d ~seconds\n",u_speed, (total_speed /(pow(10,6))), (long)(total_speed % 1000000));
    }
    // Cleanup Resources
    curl_easy_cleanup(curl_ptr);
  }
  curl_global_cleanup();
}

#endif