#include "Ship.hpp"

Ship::Ship() : MotionObject() {
    _parameters_motion.at("position") = Vector2{400.0f, 30.0f};
    _parameters_motion.at("velocity") = Vector2{0.0f, 0.0f};
    _parameters_motion.at("acceleration") = Vector2{0.4f, 0.0f};

    _object_dimension = Vector2 {50, 50};
}

Ship::Ship(Vector2 position, Vector2 velocity, Vector2 acceleration) : MotionObject() {
    
    _parameters_motion.at("position") = position;
    _parameters_motion.at("velocity") = velocity;
    _parameters_motion.at("acceleration") = acceleration;

    _object_dimension = Vector2 {50, 50};
}

Ship::~Ship() {
    
}