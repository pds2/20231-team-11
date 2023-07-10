#include "../logic/include/Ship_logic.hpp"
//#include "Game_logic.hpp"

Ship_logic::Ship_logic() : MotionObject_logic() {
    _total_charge = 0.2f;
    _current_charge = 0.0f;
    _life = 3;
}

Ship_logic::~Ship_logic() {

}


Ship_logic::Ship_logic(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 ship_dimension)
    : MotionObject_logic(position, velocity, acceleration, ship_dimension) {
    _total_charge = 0.2f;
    _current_charge = 0.0f;
    _life = 3;
}


// Não dá pra fazer ainda update pq precisa do game !!!!!

/*void Ship_logic::update(float delta_time) {
    // Atualização relativa a comportamentos: posição, velocidade, aceleração; e ao retângulo do objeto
    MotionObject_logic::update();

    // Atualização relativa a carga da bala
    if (is_charged() && _game->get_inputs("fire")) {
        // Crie uma bala e adicione ao estado do jogo
        fire_bullet();
        // Zerando a carga
        _current_charge = 0.0f;
        // Termine a função
        return;
    }

    // Carregue a bala
    _current_charge = is_charged() ? _total_charge : _current_charge + delta_time;

}*/

bool Ship_logic::is_charged() {
    return _current_charge >= _total_charge;
}


// Tem que só alterar o jeito que Vector2 e Vector2Subtract são usados pra nova declaração do Structs_logic.hpp

/*void Ship_logic::fire_bullet() {
    // Cria uma bala no topo da nave
    Vector2 bullet_position = Vector2Subtract(_parameters.at("position"), Vector2{0, _parameters.at("dimension").y / 2.0f});
    MotionObject_logic* bullet = new MotionObject_logic(bullet_position, Vector2{0, -10}, Vector2{0, 0}, Vector2{20, 50});

    // Adiciona comportamento a bala
    bullet->add_behaviour(_game->get_behaviour("default"));

    // Adiciona animação a bala
    bullet->add_animation(_game->get_animation("bullet"));

    // Adicionae a bala so estado do jogo
    _game->add_bullet(bullet);
}*/

// Nave mata a si mesma:  estranho?? kill_ship deve ser um método um método do jogo?
int Ship_logic::kill_ship() {
    --_life;
    //std::cout << TERMINAL_BOLDRED << "VIDA: " << _life <<TERMINAL_RESET << std::endl;
    return _life;
}

// Getters life
int Ship_logic::get_life() {
    return _life;
}