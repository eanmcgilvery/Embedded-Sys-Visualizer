#include "RCVisualizer.cpp"

/* 
COMPILE CODE: 
            clang++ -std=c++17 main.cpp cpputils/graphics/image.cc -o main -lm -I/opt/X11/include -lpthread -lX11 -lstdc++ -I/usr/X11R6/include -L/usr/X11R6/lib
EXECUTE CODE: ./main
*/
#define LOOP(NumOfIterations) for(int i = 0; i < NumOfIterations; i++)
int main(){
  

  RC_initialize("file.txt", "./worlds/10x10.w", true);
  RCTurnLeft();
  RCMoveForward();
  RCMoveForward();
  RCMoveForward();
  // RCTurnRight();
  
  RCTurnRight();
  RCMoveForward();
  RCMoveForward();
  RCTurnRight();
  // LOOP(2){
  //   RCMoveForward();
  // }
  // RCMoveBackward();
  // RCTurnRight();
  // RCTurnLeft();
  // RCMoveForward();
  // RCTurnRight();
  RC_finalize();
  return 0;
}