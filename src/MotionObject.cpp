#include "MotionObject.hpp"

MotionObject::MotionObject() {
     _parameters_motion = {{"position", Vector2()}, {"velocity", Vector2()}, 
                          {"acceleration", Vector2()}};
    _object_dimension = Vector2();
    _alive = true;

};

MotionObject::~MotionObject() {

};

void MotionObject::update() {
    if (!_alive) {return;}
    for (auto it = _behaviours.begin(); it != _behaviours.end(); it++) {
        (*it)->update(this);
    }

};

void MotionObject::draw(Texture2D& texture, Rectangle src_object_rectangle) {
    if (!_alive) {return;}
    DrawTexturePro(texture, src_object_rectangle,
                   (Rectangle) {_parameters_motion.at("position").x, 
                    _parameters_motion.at("position").y, 
                    _object_dimension.x, _object_dimension.y},
                    Vector2 {_object_dimension.x/2, _object_dimension.y/2}, 0, WHITE);
};

void MotionObject::add_behaviour(Behaviour* behaviour) {
    behaviour->assertion(&_parameters_motion);
    _behaviours.push_back(behaviour);
}

// Getters e Setters

void MotionObject::set(std::string key, Vector2 value) {
    _parameters_motion.at(key) = value;
}

Vector2 MotionObject::get(std::string key) {
    return _parameters_motion.at(key);
}

std::vector<Behaviour*> MotionObject::get_behaviours() {
    return _behaviours;
}

Vector2 MotionObject::get_dimension() {
    return _object_dimension;
}
void MotionObject::set_dead() {
    _alive = false;
}