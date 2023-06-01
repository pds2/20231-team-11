#include "Ship.hpp"

Ship::Ship() : MotionObject() {

}

Ship::Ship(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 ship_dimension, std::string graphic_key) 
    : MotionObject(position, velocity, acceleration, ship_dimension, graphic_key) {
        _total_charge = 10;
        _current_charge = 0;
       _timer_frame = 0.2f;
       _frame = 0;

       // Textura com 10 frames para a nave
       _num_frames = 10;
        
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

void Ship::_update_frame() {
    _frame = _frame == _num_frames - 1 ? 0 : _frame+1;
}

void Ship::draw(std::map<std::string, Texture2D>& textures, float* timer) {
    if (*timer >= _timer_frame) {
        _update_frame();
        *timer = 0.0f;
    }

    float width = textures.at(_graphic_key).width;
    float height = textures.at(_graphic_key).height;

    // index 0 para os 5 primeiros frames e 1 para os 5 últimos
    float idy = (float) (_frame / 5);
    // indica a posição em x da origem do retângulo
    float idx = (float) (_frame % 5);

    DrawTexturePro(textures.at(_graphic_key), (Rectangle) {idx * (width/5.0f), idy * (height / 2.0f), width/5.0f, height/2.0f},
                   (Rectangle) {_parameters_motion.at("position").x, 
                    _parameters_motion.at("position").y, 
                    _object_dimension.x, _object_dimension.y},
                    Vector2 {_object_dimension.x/2, _object_dimension.y/2}, 0, WHITE);
};