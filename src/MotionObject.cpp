#include "MotionObject.hpp"

MotionObject::MotionObject() {
     _parameters_motion = {{"position", Vector2()}, {"velocity", Vector2()}, 
                          {"acceleration", Vector2()}};
    _object_dimension = Vector2();
    _alive = true;
    _graphic_key = "";
};

MotionObject::MotionObject(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 object_dimension, std::string graphic_key) {
     _parameters_motion = {{"position", position}, {"velocity", velocity}, 
                          {"acceleration", acceleration}};
    _object_dimension = object_dimension;
    _alive = true;
    _graphic_key = graphic_key;
};


MotionObject::~MotionObject() {

};

void MotionObject::update() {
    for (auto it = _behaviours.begin(); it != _behaviours.end(); it++) {
        (*it)->update(this);
    }

};

void MotionObject::draw(std::map<std::string, Texture2D>& textures, std::map<std::string, Rectangle>& src_full_rectangles) {
    DrawTexturePro(textures.at(_graphic_key), src_full_rectangles.at(_graphic_key),
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