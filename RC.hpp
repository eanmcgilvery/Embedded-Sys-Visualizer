#ifndef RC_H
#define RC_H
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "orientation.h"
#include <memory>

class RC{

  private: 
    std::string FileName_;
    bool UsingRCGraphics_;
    
    //Cell Variables
    graphics::Image RCWorldImage_;
    int pxPerCell_ = 50;
    int XDim_;
    int YDim_;
    const int wallThickness_ = 3;
    const int NumOfHorizontalLines_ = 20;
    const int NumOfVerticalLines_ = 20;


    //Car Variables
    DirectionAndOrientation position_;
    int Speed_;


  public: 
    RC() = delete;
    RC(int xDim, int yDim): XDim_(xDim) , YDim_(yDim){}; //overload constructor; ask Ean what he wanted to do with this again

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

    
    void PopulateBoard();
    void DrawRCCar(int,int);

    //Car Movements
    void MoveForward();
    void MoveBack();
    void TurnLeft();
    void TurnRight();
  
};

std::unique_ptr<RC> CAR(new RC(1000,1000)); //GLOBAL VARIABLE
#endif