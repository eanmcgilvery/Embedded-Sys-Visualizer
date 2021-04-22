#ifndef RC_CPP
#define RC_CPP
#include "RC.hpp"
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "orientation.h"
#include <memory>
#include <fstream> 

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
    const graphics::Color grey(128, 126, 120);
    const graphics::Color yellow (247,181,0);
    const int lineThickness = 4;   
    const int wallThickness_ = 3;
    const int fontsize = 16;
    const int margin = 32;
    

    CAR->RCWorldImage().DrawRectangle(0,0,XDim_*pxPerCell_-1,YDim_*pxPerCell_-1,backGroundColor);
    //Horizontal Lines
    for (int i = 0; i <= YDim_; i++) {
      // Draw horizontal lines and indexes.
      int x = pxPerCell_ * XDim_;
      int y = i * pxPerCell_;
      CAR->RCWorldImage().DrawLine(0, y, x, y, kWallColor, wallThickness_);
      
      //Adding Green Horizonal Grass to the Image to Make it prettier

      if(y < YDim_*pxPerCell_){
        if(y%100==0)
          CAR->RCWorldImage().DrawRectangle(0,y,x,pxPerCell_,green1);
        else
          CAR->RCWorldImage().DrawRectangle(0,y,x,pxPerCell_,green2);
      }
        
      

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
      CAR->RCWorldImage().DrawLine(x, 0, x, y, kWallColor, wallThickness_);

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
          
          //Set the width of the Rectangle
          // int width = XDim_ - i;
          // std::cout << "width: " << width;

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
                  CAR->RCWorldImage().SetColor(x_center-widthOffset,y_center-heightOffset,color);
                }
                y_center++;
            }
            y_center = temp;
            x_center++;
          }
          
          if (rockCount > 1) {
          // Draw the rock count in the cell if it's biger than 1.
          CAR->RCWorldImage().DrawText(x_center-widthOffset- fontsize / 4, y_center - heightOffset - fontsize / 2,
                                      std::to_string(rockCount), fontsize, kWallColor);
          }
        }
      }
    }
  }
}
// Helper methods
void RC::ParseWorldFileError(std::string error_text, int line_number) {
  if (line_number > 0) {
    error_text += " (line " + std::to_string(line_number) + ")";
  }
  std::cout << error_text << std::endl << std::flush;
  throw error_text;
}

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