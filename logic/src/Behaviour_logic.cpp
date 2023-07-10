#include "../logic/include/Behaviour_logic.hpp"

// BEHAVIOUR
Behaviour_logic::Behaviour_logic() {
    
};

Behaviour_logic::~Behaviour_logic() {

};

void Behaviour_logic::update(MotionObject_logic* motion_object) {

}


// DEFAULT_SHIP_BEHAVIOUR

DefaultShipBehaviour_logic::DefaultShipBehaviour_logic(std::map<std::string, bool>* key_inputs, Vector2 velocity)
    : _key_inputs(key_inputs), _velocity(velocity) {
}


DefaultShipBehaviour_logic::~DefaultShipBehaviour_logic() {

}

void DefaultShipBehaviour_logic::update(MotionObject_logic* motion_object) {
    // Movimento retilíneo e uniforme da nave (velocidade constante e aceleração nula)
    // A velocidade da nave é sobrescrita pela do objeto
    Vector2 velocity= motion_object->get("velocity");
    bool move_right = _key_inputs->at("move-right"), move_left = _key_inputs->at("move-left");
    velocity.set_x(move_right * _velocity.get_x() - move_left * _velocity.get_x());
    velocity.set_y(_velocity.get_y());

    motion_object->set("velocity", velocity);

}

std::map<std::string, bool>* DefaultShipBehaviour_logic::get_key_inputs(){
    return _key_inputs;
}

Vector2 DefaultShipBehaviour_logic::get_velocity(){
    return _velocity;
}


// KAMIKAZE_BEHAVIOUR

KamikazeBehaviour_logic::KamikazeBehaviour_logic(MotionObject_logic* target_object) {
    // Ponteiro para o objeto perseguido
    _target_object = target_object;
    // Velocidade máxima que o alien kamikaze atinge
    _max_speed = 20.0f;
    // Taxa em que a aceleração é almentada JERK
    _acceleration_factor = 1.02f;
    // Velocidade em que os aliens perdem a manobrabilidade 
    _threshold_speed = _max_speed * (0.34f);

}

KamikazeBehaviour_logic::~KamikazeBehaviour_logic() {

}


void KamikazeBehaviour_logic::update(MotionObject_logic* motion_object) {
    
    Vector2 position = motion_object->get("position");
    Vector2 velocity= motion_object->get("velocity");
    Vector2 acceleration = motion_object->get("acceleration");
    Vector2 direction = _target_object->get("position").subtract(position);
    
    //acceleration = Vector2Scale(Vector2Normalize(direction), Vector2Length(acceleration));
    acceleration = direction.normalize().scale(acceleration.length());
    
    float velocity_length = velocity.length();

   
    if (velocity_length < _threshold_speed) {
        //velocity =  Vector2Scale(Vector2Normalize(direction), velocity_length);
        velocity =  direction.normalize().scale(velocity_length);
    }

    velocity = acceleration.add(velocity);
    velocity_length = velocity.length();   

    if (velocity_length > _max_speed) {
        //velocity =  Vector2Scale(Vector2Normalize(velocity), _max_speed);
        velocity = velocity.normalize().scale(_max_speed);
    }
    
    motion_object->set("velocity", velocity);
    motion_object->set("position", velocity.add(position));
    motion_object->set("acceleration", acceleration.scale(_acceleration_factor));
}

float KamikazeBehaviour_logic::get_max_speed(){
    return _max_speed;
}

float KamikazeBehaviour_logic::get_acceleration_factor(){
    return _acceleration_factor;
}

float KamikazeBehaviour_logic::get_threshold_speed(){
    return _threshold_speed;
}

MotionObject_logic* KamikazeBehaviour_logic::get_target_object(){
    return _target_object;
}
