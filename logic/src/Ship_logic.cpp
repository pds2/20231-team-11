#include "../logic/include/Ship_logic.hpp"

Ship_logic::Ship_logic() : MotionObject_logic() {

}

Ship_logic::~Ship_logic() {

}


Ship_logic::Ship_logic(Vector2 position, Vector2 velocity, Vector2 acceleration, 
Vector2 ship_dimension, float speed_limit, float aceleration_limit)
    : MotionObject_logic(position, velocity, acceleration, ship_dimension, speed_limit, aceleration_limit) {
    _total_charge = 0.2f;
    _current_charge = 0.0f;
    _life = 3;
}

bool Ship_logic::is_charged() {
    return _current_charge >= _total_charge;
}


int Ship_logic::kill_ship() {
    if (--_life < 0) {
        throw std::invalid_argument("Vida nao pode ser negativa");
    }
    //std::cout << "VIDA: " << _life << std::endl;
    return _life;
}

// Getters life
int Ship_logic::get_life() {
    return _life;
}

float Ship_logic::get_total_charge(){
    return _total_charge;
}

float Ship_logic::get_current_charge(){
    return _current_charge;
}