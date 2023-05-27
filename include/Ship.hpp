#ifndef SHIP_H
#define SHIP_H

#include <raylib-cpp.hpp>
#include <string>
#include <map>

#include "MotionObject.hpp"

class Ship : public MotionObject {
    public:
        Ship();
        Ship(Vector2 position, Vector2 velocity, Vector2 acceleration);
        
        ~Ship();
       
};



#endif