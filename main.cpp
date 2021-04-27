#include "RCVisualizer.cpp"

/* 
COMPILE CODE: 
            clang++ -std=c++17 main.cpp cpputils/graphics/image.cc -o main -lm -I/opt/X11/include -lpthread -lX11 -lstdc++ -I/usr/X11R6/include -L/usr/X11R6/lib
EXECUTE CODE: ./main
*/

int main(){
  RC_initialize(false);
  RCTurnRight();
  RCMoveForward();
  RCMoveBackward();
  RCTurnRight();
  RCMoveBackward();
  RCTurnRight();
  RCMoveBackward();
  RC_finalize();
  return 0;
}