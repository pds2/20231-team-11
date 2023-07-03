#include "Behaviour.hpp"

// BEHAVIOUR
Behaviour::Behaviour() {
    
};

Behaviour::~Behaviour() {

};

void Behaviour::update(MotionObject* motion_object) {

}

void Behaviour::update_acceleration(MotionObject* motion_object, Vector2 delta_acceleration) {
    Vector2 new_acceleration = Vector2Add(motion_object->get("acceleration"), delta_acceleration);
    float acceleration_limit = motion_object->get_acceleration_limit();
    if (Vector2Length(new_acceleration) > acceleration_limit) {
        new_acceleration = Vector2Scale(new_acceleration, acceleration_limit);
    }

    motion_object->set("acceleration", new_acceleration);
}

// FOLLOW_MOUSE_BEHAVIOUR
FollowMouseBehaviour::FollowMouseBehaviour(float delta_acceleration_size) {
    _delta_acceleration_size = delta_acceleration_size;
};

FollowMouseBehaviour::~FollowMouseBehaviour() {

};

void FollowMouseBehaviour::update(MotionObject* motion_object) {
    Vector2 direction = Vector2Subtract(motion_object->get("position"), GetMousePosition());
    Vector2 delta_acceleration = Vector2Scale(direction, _delta_acceleration_size);
    update_acceleration(motion_object, delta_acceleration);
};


// DEFAULT_SHIP_BEHAVIOUR

DefaultShipBehaviourS::DefaultShipBehaviourS(std::map<std::string, bool>* key_inputs, Vector2 velocity)
    : _key_inputs(key_inputs), _velocity(velocity) {
}


DefaultShipBehaviourS::~DefaultShipBehaviourS() {

}

void DefaultShipBehaviourS::update(MotionObject* motion_object) {
    // Movimento retilíneo e uniforme da nave (velocidade constante e aceleração nula)
    // A velocidade da nave é sobrescrita pela do objeto
    Vector2 velocity= motion_object->get("velocity");

    bool move_right = _key_inputs->at("move-right"), move_left = _key_inputs->at("move-left");
    velocity.x = move_right * _velocity.x - move_left * _velocity.x;
    velocity.y = _velocity.y;
    motion_object->set("velocity", velocity);
}


// KAMIKAZE_BEHAVIOUR

KamikazeBehaviour::KamikazeBehaviour(MotionObject* target_object) {
    // Ponteiro para o objeto perseguido
    _target_object = target_object;
    // Velocidade máxima que o alien kamikaze atinge
    _max_speed = 20.0f;
    // Taxa em que a aceleração é almentada JERK
    _acceleration_factor = 1.02f;
    // Velocidade em que os aliens perdem a manobrabilidade 
    _threshold_speed = _max_speed * (0.6f);

}

KamikazeBehaviour::~KamikazeBehaviour() {

}


void KamikazeBehaviour::update(MotionObject* motion_object) {
    
    Vector2 position = motion_object->get("position");
    Vector2 velocity= motion_object->get("velocity");
    Vector2 acceleration = motion_object->get("acceleration");
    Vector2 direction = Vector2Subtract(_target_object->get("position"), position);
    
    acceleration = Vector2Scale(Vector2Normalize(direction), Vector2Length(acceleration));
    
    float velocity_length = Vector2Length(velocity);

   
    if (velocity_length < _threshold_speed) {
        velocity =  Vector2Scale(Vector2Normalize(direction), velocity_length);
    }

    velocity = Vector2Add(acceleration, velocity);
    velocity_length = Vector2Length(velocity);

    if (velocity_length > _max_speed) {
        velocity =  Vector2Scale(Vector2Normalize(velocity), _max_speed);
    }
    
    motion_object->set("velocity", velocity);
    motion_object->set("position", Vector2Add(velocity, position));
    motion_object->set("acceleration", Vector2Scale(acceleration, _acceleration_factor));

}