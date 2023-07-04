#include "MotionObject.hpp"
#include "Behaviour.hpp"
#include "Animation.hpp"

// Inicializando ponteiro para jogo como nulo
Game* MotionObject::_game = nullptr;

MotionObject::MotionObject() {
 
};

MotionObject::MotionObject(Vector2 position, Vector2 velocity, 
                           Vector2 acceleration, Vector2 dimension, 
                           float speed_limit, float acceleration_limit) {
     _parameters = {{"position", position}, {"velocity", velocity}, 
                    {"acceleration", acceleration}, {"dimension", dimension}};

    // Comportamentos do objeto
    _behaviours = std::vector<Behaviour*>();

    // Animações do objeto
    _animations = std::vector<Animation*>();

    // Rectangle centralizado na posição do objeto e com as dimensões do objeto
    _rectangle = {position.x - dimension.x/2.0f, position.y - dimension.y/2.0f, dimension.x, dimension.y};

    // Limites de velocidade e aceleração
    _speed_limit = speed_limit;
    _acceleration_limit = acceleration_limit;

};

MotionObject::~MotionObject() {

};

void MotionObject::update() {
    // Modifica a posição do objeto

    // Modifica aceleração e velocidade do objeto
    for (auto it = _behaviours.begin(); it != _behaviours.end(); it++) {
        (*it)->update(this);
    }

    float width = _parameters.at("dimension").x;
    Vector2 new_position = Vector2Add(_parameters.at("position"), _parameters.at("velocity"));
    if (new_position.x > width/2.2f && new_position.x < SCREEN_WIDTH - width/2.2f)
        _parameters.at("position") = new_position;

    // Altera o retângulo do objeto com base na nova posição
    _update_rectangle();
};

void MotionObject::_update_rectangle() {
    Vector2 position = _parameters.at("position");
    Vector2 dimension = _parameters.at("dimension");
    _rectangle = {position.x - dimension.x/2.0f, position.y - dimension.y/2.0f, dimension.x, dimension.y};
}

void MotionObject::draw() {
     for (auto it = _animations.begin(); it != _animations.end(); it++) {
        (*it)->draw(this);
    }
};

void MotionObject::add_behaviour(Behaviour* behaviour) {
    _behaviours.push_back(behaviour);
}

void MotionObject::add_animation(Animation* animation) {
    _animations.push_back(animation);
}

// Getters e Setters

void MotionObject::set(std::string key, Vector2 value) {
    _parameters.at(key) = value;
}

void MotionObject::set_game(Game* game) {
    _game = game;
}

Vector2 MotionObject::get(std::string key) {
    return _parameters.at(key);
}

Rectangle MotionObject::get_rectangle() {
    return _rectangle;
}

float MotionObject::get_speed_limit() {
    return _speed_limit;
}

float MotionObject::get_acceleration_limit() {
    return _acceleration_limit;
}

// MOTION_OBJECT_TEMP
MotionObjectTemp::MotionObjectTemp() : MotionObject() {

}

MotionObjectTemp::MotionObjectTemp(
    Game* game, float end_time, float born_time, Vector2 position, 
    Vector2 velocity, Vector2 acceleration, Vector2 dimension, 
    float speed_limit, float acceleration_limit) :
    MotionObject(position, velocity, acceleration, dimension, speed_limit, acceleration_limit), 
    _game(game) {

}

MotionObjectTemp::~MotionObjectTemp() {
    
}


void MotionObjectTemp::update(float delta_time) {
    _born_time += delta_time;
}

bool MotionObjectTemp::is_dead() {
    return _born_time >= _end_time;
}