#include "Ship.hpp"

Ship::Ship() : MotionObject() {

}

Ship::Ship(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 ship_dimension, std::string graphic_key) 
    : MotionObject(position, velocity, acceleration, ship_dimension, graphic_key) {
        _total_charge = 10;
        _current_charge = 0;
}

Ship::~Ship() {
}

bool Ship::is_charged() {
    return _current_charge == _total_charge;
}

void Ship::add_charge() {
    if (!is_charged()) {
        ++_current_charge;
    }
}

void Ship::fire_bullet(Game* game) {
    // Canhão carregado: crie uma bala no topo da nave
    Vector2 bullet_position = Vector2Subtract(_parameters_motion.at("position"), Vector2 {0, _object_dimension.y/2});
    MotionObject* bullet = new MotionObject(bullet_position, Vector2 {0, -10}, Vector2 {0, 0}, Vector2 {3, 30}, "bullet");
    
    // Adicionar comportamento
    bullet->add_behaviour(game->get_behaviour("default_bullet"));
    
    // Adicionae a bale no estado do jogo
    game->add_bullet(bullet);

    // Canhão descarregado
    _current_charge = 0;
}