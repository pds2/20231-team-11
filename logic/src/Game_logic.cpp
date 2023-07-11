#include "../logic/include/Game_logic.hpp"

Game_logic::Game_logic() {
    // Inputs
    _key_inputs = { {"move-right", false}, {"move-left", false}, {"fire", false}};
    //_mouse_position = Vector2 {};

    // Fonte Default
    _font = "default";

    // Textures
    _textures = std::map<std::string, Texture2D>();

    // Animações
    // _animations = std::map<std::string, Animation_logic*>();
    _animations = {{"alien", nullptr}, {"ship", nullptr}, {"bullet",  nullptr}, {"ship", nullptr}, {"explosion", nullptr}};

    // Comportamentos
    _behaviours = {{"default", nullptr}, {"default-ship", nullptr}, {"kamikaze-to-ship",  nullptr}};

    // Objetos
    _ship = nullptr;
    _bullets = std::list<MotionObject_logic*>();
    _aliens = std::list<Alien_logic*>();

    // Score
    _score = 0u;

    // Game status
    _game_status = false;
}

void Game_logic::_load_graphics() {
    // Armazena todas as texturas e os retângulos fontes cobrindo toda a imagem
    _textures["background"] = Texture2D().LoadTexture("images/alexandria/mapa.png");
    _textures["menu"] = Texture2D().LoadTexture("images/space.png");
    _textures["explosion"] = Texture2D().LoadTexture("images/explosion.png");
    _textures["power-up"] = Texture2D().LoadTexture("images/power-up.png");    
    
    _textures["ship"] = Texture2D().LoadTexture("images/alexandria/ship_grid.png");
    _textures["alien"] = Texture2D().LoadTexture("images/alexandria/alien_grid.png");
    _textures["bullet"] = Texture2D().LoadTexture("images/alexandria/bullet_grid.png");                   
}

void Game_logic::_load_behaviours() {
    // Comportamentos do jogo; 
    _behaviours["default"] = new Behaviour_logic();
    _behaviours["default-ship"] = new DefaultShipBehaviour_logic(&_key_inputs, Vector2 {10, 0.0});
}

void Game_logic::add_bullet(MotionObject_logic* bullet) {
    _bullets.push_back(bullet);
}

Behaviour_logic* Game_logic::get_behaviour(std::string key) {
    return _behaviours.at(key);
}

Animation_logic* Game_logic::get_animation(std::string key) {
    return _animations.at(key);
}

bool Game_logic::get_inputs(std::string key){
    return _key_inputs.at(key);
}

std::map<std::string, Texture2D> Game_logic::get_textures() {
    return _textures;
}

Ship_logic* Game_logic::get_ship() {
    return _ship;
}

std::list<MotionObject_logic*> Game_logic::get_bullets() {
    return _bullets;
}

std::list<Alien_logic*> Game_logic::get_aliens() {
    return _aliens;
}

unsigned int Game_logic::get_score() {
    return _score;
}

bool Game_logic::get_game_status() {
    return _game_status;
}

void Game_logic::add_behaviour(std::string key, Behaviour_logic* behaviour) {
    _behaviours[key] = behaviour;
}

void Game_logic::add_animation(std::string key, Animation_logic* animation) {
    _animations[key] = animation;
}

void Game_logic::add_alien(Alien_logic* alien) {
    _aliens.push_back(alien);
}

void Game_logic::set_ship(Ship_logic* ship) {
    _ship = ship;
}