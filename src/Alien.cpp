#include "Alien.hpp"
#include "Game.hpp"

Alien::Alien() : MotionObject() {

}

Alien::~Alien() {

}


Alien::Alien(Vector2 position, Vector2 velocity, Vector2 acceleration, 
Vector2 alien_dimension, float speed_limit, float aceleration_limit) 
    : MotionObject(position, velocity, acceleration, alien_dimension, speed_limit, aceleration_limit) {
        // Alien padrão tem score igual a 10
        _score = 10u;
}

unsigned Alien::get_score() {
    return _score;
}
