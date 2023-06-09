#include "../logic/include/MotionObject_logic.hpp"

MotionObject_logic::MotionObject_logic() {
 
};

MotionObject_logic::MotionObject_logic(Vector2 position, Vector2 velocity, 
                           Vector2 acceleration, Vector2 dimension, 
                           float speed_limit, float acceleration_limit) {

     _parameters = {{"position", position}, {"velocity", velocity}, 
                    {"acceleration", acceleration}, {"dimension", dimension}};

    // Animações do objeto
    _animations = std::vector<Animation_logic*>();

    // Rectangle centralizado na posição do objeto e com as dimensões do objeto
    Vector2 center(position.get_x() - dimension.get_x()/2.0f, position.get_y() - dimension.get_y()/2.0f);
    _rectangle = Retangulo(center, dimension.get_x(), dimension.get_y());
    // Limites de velocidade e aceleração
    _speed_limit = speed_limit;
    _acceleration_limit = acceleration_limit;

};

MotionObject_logic::~MotionObject_logic() {

};

void MotionObject_logic::update() {
    // Modifica a posição do objeto

    float width = _parameters.at("dimension").get_x();
    Vector2 new_position = _parameters.at("position").add(_parameters.at("velocity"));
    
    if (new_position.get_x() > width/2.2f && new_position.get_x() < 1200.0f - width/2.2f)
        _parameters.at("position") = new_position;

    // Altera o retângulo do objeto com base na nova posição
    _update_rectangle();
};

void MotionObject_logic::_update_rectangle() {
    Vector2 position = _parameters.at("position");
    Vector2 dimension = _parameters.at("dimension");
    Vector2 center(position.get_x() - dimension.get_x()/2.0f, position.get_y() - dimension.get_y()/2.0f);
    _rectangle = Retangulo(center, dimension.get_x(), dimension.get_y());
}

void MotionObject_logic::add_animation(Animation_logic* animation) {
    _animations.push_back(animation);
}

// Getters e Setters

void MotionObject_logic::set(std::string key, Vector2 value) {
    _parameters.at(key) = value;
}

Vector2 MotionObject_logic::get(std::string key) {
    return _parameters.at(key);
}

Retangulo MotionObject_logic::get_rectangle() {
    return _rectangle;
}

float MotionObject_logic::get_speed_limit() {
    return _speed_limit;
}

float MotionObject_logic::get_acceleration_limit() {
    return _acceleration_limit;
}

std::vector<Animation_logic*> MotionObject_logic::get_animations() {
    return _animations;
}
