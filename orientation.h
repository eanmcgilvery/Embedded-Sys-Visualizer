#ifndef RCVISUALIZER_HPP
#define RCVISUALIZER_HPP
#include <iostream>

//Tells which direction the Car should be facing in a given turn

enum Direction{
  North = 0,
  South = 1,
  East = 2,
  West = 3,
};

struct DirectionAndOrientation{
  int x_ = 0;
  int y_ = 0;
  Direction orientation_ = Direction::East;
};

#endif 