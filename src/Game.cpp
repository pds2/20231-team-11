#include "Game.hpp"

Game::Game() {
    // Dimensões da Tela
    _src_screen_rectangle = {0, 0, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT};
    
    _key_inputs = { {"down_right", false}, {"down_left", false}};

    Vector2 positionA = {400.0f, 30.0f}, velocityA = {10.0f, 0.0f}, accelerationA = {0.0f, 0.0f};
    Vector2 positionB = {400.0f, 600.0f}, velocityB = {0.0f, 0.0f}, accelerationB = {0.01f, 0.0f};
    Vector2 positionC = {100.0f, 500.0f};
    
    _ship= new Ship(positionA, velocityA, accelerationA);
    Alien* alien = new Alien(positionB, velocityB, accelerationB);
    Alien* alien2 = new Alien(positionC, velocityB, accelerationB);

    // Behaviour* behaviour = new Behaviour(); 
    // FollowMouseBehaviour* follow_mouse = new FollowMouseBehaviour();
    DefaultShipBehaviour* default_ship = new DefaultShipBehaviour(&_key_inputs);
    // AcceleredShipBehaviour* accelered_ship = new AcceleredShipBehaviour(&_key_inputs, 50.0f, 2.0f);
    // ResistanceShipBehaviour* resistance_ship = new ResistanceShipBehaviour(&_key_inputs,0.5f, 50.0f, 0.01f);
    KamikazeBehaviour* kamikaze_to_ship = new KamikazeBehaviour(_ship);
    KamikazeBehaviour* kamikaze_to_alien = new KamikazeBehaviour(alien);

    // Salvando todos os comportamentos no estado do jogo
    _behaviours.push_back(default_ship);
    _behaviours.push_back(kamikaze_to_ship);
    _behaviours.push_back(kamikaze_to_alien);

    _ship->add_behaviour(default_ship);
    alien->add_behaviour(kamikaze_to_ship);
    alien2->add_behaviour(kamikaze_to_alien);

    // Salvando todos os aliens no estado do jogo
   _add_alien(alien);
   _add_alien(alien2);
}

Game::~Game() {

    delete _ship;

    for (Alien* alien : _aliens) {
        delete alien;
    }

    for (Behaviour* behaviour : _behaviours) {
        delete behaviour;
    }
}

bool Game::initialize() {
    SetTargetFPS(60);
    raylib::InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Invaders");

    return true;

}

void Game::run_loop() {
    // Textura da nave e retângulo fonte
    _ship_texture = LoadTexture("images/spaceship_red.png");
    _src_ship_rectangle = {0, 0, (float)_ship_texture.width, (float)_ship_texture.height};

    // Textura de fundo e retângulo fonte
    _background_texture = LoadTexture("images/space.png");
    _src_screen_rectangle = {0, 0, (float)_background_texture.width, (float)_background_texture.height};

    // Textura do alien e retângulo fonte
    _alien_texture = LoadTexture("images/spaceship_yellow.png");
    _src_alien_rectangle = {0, 0, (float)_alien_texture.width, (float)_alien_texture.height};

     while(!WindowShouldClose()) {
        _process_input();
        _update_game();
        _draw_game();
        _check_colisions();
    }

    UnloadTexture(_ship_texture);
    UnloadTexture(_background_texture);
    UnloadTexture(_alien_texture);

}

void Game::_process_input() {
    _mouse_position = GetMousePosition();

    _key_inputs.at("down_right") = IsKeyDown(KEY_RIGHT);
    _key_inputs.at("down_left") = IsKeyDown(KEY_LEFT);

}

void Game::_update_game() {
    // O jogo contém aliens e uma nave
    _ship->update();
    for (Alien* object : _aliens) {
        object->update();
    }

}

void Game::_draw_game() {
    // Desenha todos os objetos do jogo
    BeginDrawing();

    ClearBackground(WHITE);
    DrawTexturePro(_background_texture, _src_screen_rectangle, 
    (Rectangle) {0, 0, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT}, Vector2Zero(), 0, WHITE);

    _ship->draw(_ship_texture, _src_ship_rectangle);
    for (Alien* alien : _aliens) {
        alien->draw(_alien_texture, _src_alien_rectangle);
    }

    EndDrawing();
}

void Game::shutdown() {
    CloseWindow();
}

void Game::_add_alien(Alien* alien) {
    _aliens.push_back(alien);
}

void Game::_check_colisions() {
    Vector2 ship_dimension = _ship->get_dimension();
    for (Alien* alien : _aliens) {
        Vector2 alien_dimension = alien->get_dimension();
        Vector2 alien_position = alien->get("position");

        float distance = Vector2Length(Vector2Subtract(alien_position, _ship->get("position")));
        float threshold = fmin(ship_dimension.x/2 + alien_dimension.x/2,  ship_dimension.y/2 + alien_dimension.y/2);
        
        if (distance < threshold) {
            alien->set_dead();
            _ship->set_dead();
        }

        if (alien_position.y < 0) {
            alien->set_dead();
        }
    }
}

    