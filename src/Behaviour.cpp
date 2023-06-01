#include "Behaviour.hpp"



// BEHAVIOUR

Behaviour::Behaviour() {
    
};

Behaviour::~Behaviour() {

};

void Behaviour::update(MotionObject* motion_object) {
    // Posição no centro da tela
    Vector2 position = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

    motion_object->set("position", position);

}

void Behaviour::assertion(std::map<std::string, Vector2>* parameters_motion) {
    // Casting para void: parâmtro não utilizado intencionalmente
    (void)parameters_motion; 

} 

// DEFAULT_BULLET_BEHAVIOUR
DefaultBulletBehaviour::DefaultBulletBehaviour() {

}

DefaultBulletBehaviour::~DefaultBulletBehaviour() {

}

void DefaultBulletBehaviour::update(MotionObject* motion_object) {
     // Movimento retilíneo e uniforme vertical da bala
    Vector2 position = motion_object->get("position");
    Vector2 velocity= motion_object->get("velocity");

    motion_object->set("position", Vector2Add(position, velocity));
}


// DEFAULT_SHIP_BEHAVIOUR

DefaultShipBehaviour::DefaultShipBehaviour(std::map<std::string, bool>* key_inputs)
    : _key_inputs(key_inputs) {
}


DefaultShipBehaviour::~DefaultShipBehaviour() {

}

void DefaultShipBehaviour::update(MotionObject* motion_object) {
    // Movimento retilíneo e uniforme da nave (velocidade constante e aceleração nula)
    Vector2 position = motion_object->get("position");
    Vector2 velocity= motion_object->get("velocity");

    bool move_right = _key_inputs->at("down_right"), move_left = _key_inputs->at("down_left");
    position.x += move_right * velocity.x - move_left * velocity.x;

    // Checa fronteiras laterais: substituir o 20 por um valor em função da dimensão da nave
    if (position.x > 20 && position.x < SCREEN_WIDTH - 20)
        motion_object->set("position", position);

    motion_object->set("velocity", velocity);
}

void DefaultShipBehaviour::assertion(std::map<std::string, Vector2>* parameters_motion) {
    Vector2 velocity= parameters_motion->at("velocity");
    Vector2 acceleration= parameters_motion->at("acceleration");

    bool condition = Vector2Length(acceleration) == 0.0f && velocity.x > 0.0f && velocity.y == 0.0f;
    if (!condition) {
        std::cout << TERMINAL_RED << "ALERTA: NAVE COM DEFAULT_SHIP_BEHAVIOUR DEVE TER ACELERAÇÃO NULA E VELOCIDADE ESTRITAMENTE HORIZONTAL NÃO-NULA !!" << TERMINAL_RESET << std::endl;
        std::abort();
    }
}

// ACCELERED_SHIP_BEHAVIOUR

AcceleredShipBehaviour::AcceleredShipBehaviour(std::map<std::string, bool>* key_inputs, float max_speed, float stop_speed)
    : DefaultShipBehaviour(key_inputs) {
        _max_speed = max_speed;
        _stop_speed = stop_speed;
}

AcceleredShipBehaviour::~AcceleredShipBehaviour() {
    
}

void AcceleredShipBehaviour::update(MotionObject* motion_object) {
    // Movimento retilíneo uniformemente acelerado da nave (aceleração constante)
    Vector2 position = motion_object->get("position");
    Vector2 velocity= motion_object->get("velocity");
    Vector2 acceleration = motion_object->get("acceleration");

    bool move_right = _key_inputs->at("down_right"), move_left = _key_inputs->at("down_left");
   
    // Se a velocidade é nula a nave recebe um boost para ultrapassar _stop_speed
    bool zero_flag = Vector2Length(velocity) == 0;
    if (!zero_flag) {
        velocity.x += move_right * acceleration.x - move_left * acceleration.x;
        _check_resistance(&velocity, move_right, move_left);
        _check_velocity_edges(&velocity);
    } else {
        velocity.x += move_right * (_stop_speed + 0.1f) + move_left * (-_stop_speed - 0.1f);
    }
    
    position.x += velocity.x;
    
    motion_object->set("position", position);
    motion_object->set("velocity", velocity);
}

void AcceleredShipBehaviour::_check_resistance(Vector2* velocity, bool move_right, bool move_left) {
    // Casting para void, parâmetros não utilizados intecionalmente
    (void) velocity;
    (void) move_right;
    (void) move_left;
}

void AcceleredShipBehaviour::_check_velocity_edges(Vector2* velocity) {
    float velocity_length = Vector2Length(*velocity);
    if (velocity_length  > _max_speed) {
        *velocity = Vector2Scale(Vector2Normalize(*velocity), _max_speed);
    } else if (velocity_length < _stop_speed) {
        *velocity = Vector2 {0.0f, 0.0f};
    }
 }

void AcceleredShipBehaviour::assertion(std::map<std::string, Vector2>* parameters_motion) {
    Vector2 velocity= parameters_motion->at("velocity");
    Vector2 acceleration= parameters_motion->at("acceleration");

    bool condition = Vector2Length(acceleration) > 0.0f && acceleration.y == 0.0f && velocity.y == 0.0f;

    if (!condition) {
        std::cout << TERMINAL_RED << "ALERTA: NAVE COM ACCELERED_SHIP_BEHAVIOUR/RESISTANCE_SHIP_BEHAVIOUR DEVE TER ";
        std::cout << "\n1- ACELERAÇÃO HORIZONTAL E NÃO-NULA\n2- VELOCIDADE HORIZONTAL";
        std::cout << TERMINAL_RESET << std::endl;
        std::abort();
    }
}

// RESISTANCE_SHIP_BEHAVIOUR

ResistanceShipBehaviour::ResistanceShipBehaviour(std::map<std::string, bool>* key_inputs, float stop_speed, float max_speed, float dynamic_resistance)
    : AcceleredShipBehaviour(key_inputs, max_speed, stop_speed) {
    // Constructor implementation
    _dynamic_resistance = dynamic_resistance;
}


ResistanceShipBehaviour::~ResistanceShipBehaviour() {

}

void ResistanceShipBehaviour::_check_resistance(Vector2* velocity, bool move_right, bool move_left) {
    // Resistência do fluído proporcional ao módulo da velocidade
    if (!move_right && !move_left) {
        float velocity_length = Vector2Length(*velocity);
        velocity->x += _dynamic_resistance * (velocity->x > 0 ? -velocity_length: +velocity_length);
    }
}

// KAMIKAZE_SHIP_BEHAVIOUR

KamikazeBehaviour::KamikazeBehaviour(MotionObject* target_object) {
    _target_object = target_object;
    _max_speed = 20.0f;
    _acceleration_factor = 1.02f;
    _threshold_speed = _max_speed/2.0f;

}

KamikazeBehaviour::~KamikazeBehaviour() {

}

void KamikazeBehaviour::assertion(std::map<std::string, Vector2>* parameters_motion) {
    Vector2 acceleration= parameters_motion->at("acceleration");
    bool condition = Vector2Length(acceleration) > 0.0f;

    if (!condition) {
        std::cout << TERMINAL_RED << "ALERTA: ACELERAÇÃO DE UM KAMIKAZE NÃO PODE SER NULA !!" << TERMINAL_RESET << std::endl;
        std::abort();
    }
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

// FOLLOW_MOUSE_BEHAVIOUR

FollowMouseBehaviour::FollowMouseBehaviour() {

};

FollowMouseBehaviour::~FollowMouseBehaviour() {

};

void FollowMouseBehaviour::update(MotionObject* motion_object) {
    motion_object->set("position", GetMousePosition());
};

// ZIG-ZAG BEHAVIOUR
// Exclusivo para aliens
// ZigZagBehaviour::ZigZagBehaviour() {
//     _edge_x = 0.0f;
//     _step_y = 0.0f;
// }

// ZigZagBehaviour::ZigZagBehaviour(float edge_x, float step_y) {
//     _edge_x = edge_x;
//     _step_y = step_y;
// }

// void ZigZagBehaviour::update(Alien* alien) {
//    Vector2 position = alien->get("position");
// }

