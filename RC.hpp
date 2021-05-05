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
* File: RC.hpp
* Description:
*       This file contains the creation of the RC object and all of the prototypes
*       Requires C++ 14 or later (Smart Pointers)
*
**************************************************************************************************/


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
    bool UsingRCGraphics_;
    const std::string fileName_ = "commands.txt";
    
    // Container for collecting the commands that are called
    const std::string serverAddress_ = "http://107.221.75.87/";
    
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

    std::vector<char> commandVec_;

    graphics::Image& RCWorldImage();

    //setters
    void SetRC(bool);
    void SetSpeed(int);
    
    //getters
    int XDim();
    int YDim();
    bool UsingGraphics();
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

    //Network Related
    void CreateCommandFile();
    void SendFileToServer();
};

std::unique_ptr<RC> CAR(new RC(10,10)); //GLOBAL VARIABLE
#endif