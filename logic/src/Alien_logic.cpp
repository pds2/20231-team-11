#include "../logic/include/Alien_logic.hpp"

Alien_logic::Alien_logic() : MotionObject_logic() {

}

Alien_logic::~Alien_logic() {

}

Alien_logic::Alien_logic(Vector2 position, Vector2 velocity, Vector2 acceleration, 
Vector2 alien_dimension, float speed_limit, float aceleration_limit) 
    : MotionObject_logic(position, velocity, acceleration, alien_dimension, speed_limit, aceleration_limit) {
        // Alien padrão tem score igual a 10
        _score = 10u;
}

unsigned Alien_logic::get_score() {
    return _score;
}

void Alien_logic::set_score(unsigned score) {
    _score = score;
}