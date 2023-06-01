#include "Alien.hpp"

Alien::Alien() : MotionObject() {
    _motion_flags = std::map<std::string, bool>();
}

Alien::Alien(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 alien_dimension, std::string graphic_key) 
    : MotionObject(position, velocity, acceleration, alien_dimension, graphic_key) {
    _motion_flags = std::map<std::string, bool>();
}

Alien::~Alien() {

}