#include "../logic/include/Alien_logic.hpp"
//#include "Game_logic.hpp"

Alien_logic::Alien_logic() : MotionObject_logic() {

}

Alien_logic::~Alien_logic() {

}


Alien_logic::Alien_logic(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 alien_dimension) 
    : MotionObject_logic(position, velocity, acceleration, alien_dimension) {
        // Alien padrão tem score igual a 10
        _score = 10u;
}

unsigned Alien_logic::get_score() {
    return _score;
}

void Alien_logic::set_score(unsigned score) {
    _score = score;
}