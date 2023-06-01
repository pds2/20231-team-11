#include "Game.hpp"

Game::Game() {
    // Status do jogo
    _game_status = true;
    
    // Entradas do Teclado

    _key_inputs = { {"down_right", false}, {"down_left", false}};

    // Vetores para posições, velocidades e acelerações

    Vector2 positionA = {SCREEN_WIDTH/2, SCREEN_HEIGHT - (80/2)};
    Vector2 positionB = {400.0f, 50.0f};
    Vector2 positionC = {100.0f, 50.0f};
    Vector2 positionD = {500.0f, 50.0f};
    Vector2 positionE= {50.0f, 100.0f};

    Vector2 velocityA = {10.0f, 0.0f};
    Vector2 velocityB = {0.0f, 0.0f};
    
    Vector2 accelerationA = {0.0f, 0.0f};
    Vector2 accelerationB = {0.01f, 0.0f};
    Vector2 accelerationC = {0.005f, 0.0f};
    
    // Armazena objetos cinemáticos no HEAP

    _ship= new Ship(positionA, velocityA, accelerationA, Vector2{50, 80}, "ship");

    Alien* alien = new Alien(positionB, velocityB, accelerationB, Vector2{40, 40}, "alien");
    Alien* alien2 = new Alien(positionC, velocityB, accelerationB, Vector2{30, 30}, "alien");
    Alien* alien3 = new Alien(positionD, velocityB, accelerationC, Vector2 {40, 40}, "alien");
    Alien* alien4 = new Alien(positionE, velocityB, accelerationC, Vector2 {70, 70}, "alien");

    // Armazena comportamentos cinemáticos no HEAP
    
    DefaultBulletBehaviour* default_bullet = new DefaultBulletBehaviour();
    DefaultShipBehaviour* default_ship = new DefaultShipBehaviour(&_key_inputs);
    KamikazeBehaviour* kamikaze_to_ship = new KamikazeBehaviour(_ship);

    // Adicionando comportamentos aos objetos cinemáticos

    _ship->add_behaviour(default_ship);
    alien->add_behaviour(kamikaze_to_ship);
    alien2->add_behaviour(kamikaze_to_ship);
    alien3->add_behaviour(kamikaze_to_ship);
    alien4->add_behaviour(kamikaze_to_ship);


    // Salvando pointers para todos os comportamentos no estado do jogo

    _behaviours["default_ship"] = default_ship;
    _behaviours["kamikaze_to_ship"] = kamikaze_to_ship;
    _behaviours["default_bullet"] = default_bullet;

    
    // Salvando pointers para todos os aliens no estado do jogo
    _aliens.push_back(alien);
    _aliens.push_back(alien2);
    _aliens.push_back(alien3);
    _aliens.push_back(alien4);

   // Deads
   _deads = std::list<MotionObject*>();

   // Bullets
   _bullets = std::list<MotionObject*>();

   // Textures
   _textures = std::map<std::string, Texture2D>();

   // Timer
   _timer = 0.0f;

}

Game::~Game() {
    // Deleta toda a memória alocada no HEAP
    delete _ship;
    std::cout << TERMINAL_BLUE << "DESTRUINDO SHIP" << TERMINAL_RESET << std::endl;

    for (Alien* alien : _aliens) {
        std::cout << TERMINAL_GREEN << "DESTRUINDO ALIEN VIVO" << TERMINAL_RESET << std::endl;
        delete alien;
    }

    for (MotionObject* dead : _deads) {
        std::cout << TERMINAL_MAGENTA << "DESTRUINDO DEAD OBJECT" << TERMINAL_RESET << std::endl;
        delete dead;
    }

    for (std::pair<std::string, Behaviour*> behaviour_pair : _behaviours) {
        std::cout << TERMINAL_BOLDCYAN << "DESTRUINDO " << behaviour_pair.first << TERMINAL_RESET << std::endl;
        delete behaviour_pair.second;
    }

    for (MotionObject* bullet : _bullets) {
         std::cout << TERMINAL_BOLDRED << "DESTRUINDO BULLET" << TERMINAL_RESET << std::endl;
        delete bullet;
    }
}

bool Game::initialize() {
    // Inicializa a janela do jogo e estabelece o FPS
    SetTargetFPS(FPS);
    raylib::InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    
    // Carrega os gráficos
    _load_graphics();

    return true;

}

void Game::run_loop() {
    
    // Loop principal do jogo

     while(!WindowShouldClose() && _game_status) {
        _timer += GetFrameTime();

        _process_input();
        _update_game();
        _draw_game();
        _check_colisions();
    }

}

void Game::_process_input() {
    // Captura as entradas: mouse e teclado
    _mouse_position = GetMousePosition();

    _key_inputs.at("down_right") = IsKeyDown(MOVE_RIGHT);
    _key_inputs.at("down_left") = IsKeyDown(MOVE_LEFT);

    if (IsKeyDown(FIRE_KEY) && _ship->is_charged()) {
        _ship->fire_bullet(this);
    }
    _ship->add_charge();

}

void Game::_update_game() {
    // Atualização da posição, velocidade e aceleração dos objetos cinemáticos
    _ship->update();
    for (Alien* alien : _aliens) {
        alien->update();
    }

    for (MotionObject* bullet : _bullets) {
        bullet->update();
    }

}

void Game::_draw_game() {
    // Desenha todos os objetos do jogo
    BeginDrawing();

    ClearBackground(BLACK);

    // Desenha o background com a textura especificada no estado do jogo
    DrawTexturePro(_textures.at("background"), _rectangles.at("background"), 
    (Rectangle) {0, 0, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT}, 
    Vector2Zero(), 0, WHITE);

    // Desenha a nave e os aliens com as texturas especificadas no estado do jogo
    _ship->draw(_textures, &_timer);
    for (Alien* alien : _aliens) {
        alien->draw(_textures, _rectangles);
    }

    for (MotionObject* bullet : _bullets) {
        bullet->draw(_textures, _rectangles);
    }

    EndDrawing();
}

void Game::shutdown() {
    _unload_graphics();
    CloseWindow();
}

void Game::_check_colisions() {
    // Checa colisões entre objetos e atualiza o estado de vida dos objetos

    // Colisão entre aliens e nave
    Vector2 ship_dimension = _ship->get_dimension();
    for (auto alien_it = _aliens.begin(); alien_it != _aliens.end();) {

        Vector2 alien_dimension = (*alien_it)->get_dimension();
        Vector2 alien_position = (*alien_it)->get("position");

        float distance = Vector2Length(Vector2Subtract(alien_position, _ship->get("position")));
        float threshold = fmin(ship_dimension.x/2 + alien_dimension.x/2,  ship_dimension.y/2 + alien_dimension.y/2);
        
        // Se o alien atinge a nave finalizamos o jogo [POR HORA]
        
        if (distance < threshold) {

            // Objetos mortos pela colisão; A nave não é contada
            _deads.push_back(*alien_it);

            // Remove alien da lista
            _aliens.erase(alien_it);
            
            _end_game();
            return;
        }

        // Se o alien atinge o bottom da tela remova o alien do estado do jogo

        if (alien_position.y > SCREEN_HEIGHT) {
            // Alien morto pela colisão
            _deads.push_back(*alien_it);

            // Remove alien da lista
            alien_it = _aliens.erase(alien_it);
            continue;
        }

        // Se uma bala colide com o alien adicionamos os dois a lista _deads
        bool colision = false;
        for (auto bullet_it = _bullets.begin(); bullet_it != _bullets.end(); ) {
            Vector2 bullet_position = (*bullet_it)->get("position");
            Vector2 bullet_dimension = (*bullet_it)->get_dimension();

            float distance = Vector2Length(Vector2Subtract(alien_position, bullet_position));
            float threshold = fmin(bullet_dimension.x/2 + alien_dimension.x/2,  bullet_dimension.y/2 + alien_dimension.y/2);

            if (distance < threshold) {

                // Objetos mortos pela colisão; A nave não é contada
                _deads.push_back(*alien_it);
                _deads.push_back(*bullet_it);

                // Remove alien da lista
                alien_it = _aliens.erase(alien_it);
                bullet_it = _bullets.erase(bullet_it);
                colision = true;
                break;
                
             }

            // Bala atinge o topo da tela
            if (bullet_position.y < 0) {
                _deads.push_back(*bullet_it);
                bullet_it = _bullets.erase(bullet_it);
                continue;
             }

             ++bullet_it;

        }
        if (!colision) {
            ++alien_it;
        }
    }
}  

void inline Game::_load_graphics() {
// Armazena todas as texturas e os retângulos fontes cobrindo toda a imagem
    _textures["background"] = LoadTexture(BACKGROUND_TEXTURE);
    _textures["ship"] = LoadTexture(SHIP_TEXTURE);
    _textures["alien"] = LoadTexture(ALIEN_TEXTURE);
    _textures["bullet"] = LoadTexture(BULLET_TEXTURE);
                                    
    _rectangles["background"] = {0, 0, (float)_textures.at("background").width, (float)_textures.at("background").height};
    _rectangles["ship"] = {0, 0, (float)_textures.at("ship").width, (float)_textures.at("ship").height};
    _rectangles["alien"] = {0, 0, (float)_textures.at("alien").width, (float)_textures.at("alien").height};
    _rectangles["bullet"] = {0, 0, (float)_textures.at("bullet").width, (float)_textures.at("bullet").height};

}

void inline Game::_unload_graphics() {
     // Libera memória alocada para os gráficos/texturas
    for (std::pair<std::string, Texture2D> texture_pair : _textures) {
        UnloadTexture(texture_pair.second);
    }
}

Behaviour* Game::get_behaviour(std::string key) {
    return _behaviours.at(key);
} 

void Game::add_bullet(MotionObject* bullet) {
    _bullets.push_back(bullet);
}

void Game::_end_game() { 
    std::cout << TERMINAL_RED << "FIM DO JOGO!" << TERMINAL_RESET << std::endl;
    _game_status = false;
}