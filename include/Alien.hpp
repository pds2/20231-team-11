#ifndef ALIEN_H
#define ALIEN_H

#include <raylib-cpp.hpp>
#include "MotionObject.hpp"

class Alien : public MotionObject {
    public:
        Alien();
        Alien(Vector2 position, Vector2 velocity, Vector2 acceleration);

        ~Alien();
     
};


#endif