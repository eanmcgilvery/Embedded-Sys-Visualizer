#ifndef RC_H
#define RC_H
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "Cell.h"
#include "orientation.h"
#include <memory>
#include <vector>

class RC{

  private: 
    std::string FileName_;
    bool UsingRCGraphics_;
    
    //grid dimensions
    int XDim_ = 10; 
    int YDim_ = 10;

    //underlying image;
    graphics::Image RCWorldImage_;
    
    //Cell Variables
    int pxPerCell_ = 50;
    
    //Car Variables
    DirectionAndOrientation position_;
    int Speed_ = 1000;

    //the cells in the world
    std::vector<std::vector<Cell>> world_; 

  public: 
    RC() = delete;
    RC(int xDim, int yDim): XDim_(xDim) , YDim_(yDim){}; 

    graphics::Image& RCWorldImage();

    //setters
    void SetFileName(std::string);
    void SetRC(bool);
    void SetSpeed(int);
    
    //getters
    int XDim();
    int YDim();
    bool GetRC();
    int Speed();
    DirectionAndOrientation positions();
    int pxPerCell();

    //Board Updates
    void PopulateBoard();
    void ParseWorldFileError(std::string, int); //Initialize() helper function
    void Initialize(std::string); //parse through file and populate board accordingly
    void CheckParsePosition(char, char, char,int); //checks the syntax of ( , ) in file
    DirectionAndOrientation ParsePositionAndOrientation(std::fstream&, int) ;
    DirectionAndOrientation ParsePosition(std::fstream& file, int line_number) ;
    void DrawRCCar(); //Helper Function
    void DrawRCCar(int,int); 
    void Show();

    //Car Movements
    void MoveForward();
    void MoveBack();
    void TurnLeft();
    void TurnRight();
  
    void testRock();
};

std::unique_ptr<RC> CAR(new RC(10,10)); //GLOBAL VARIABLE
#endif