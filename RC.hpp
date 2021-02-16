#ifndef RC_H
#define RC_H
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include <memory>

class RC{



};

std::unique_ptr<RC> CAR(new RC); //GLOBAL VARIABLE
#endif