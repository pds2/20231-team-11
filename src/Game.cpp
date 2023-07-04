#include "Game.hpp"

#include <cstring>

Game::Game() {
    // Inputs
    _key_inputs = { {"move-right", false}, {"move-left", false}, {"fire", false}};
    _mouse_position = Vector2 {};

    // Fonte Default
    _font=GetFontDefault();

    // Textures
    _textures = std::map<std::string, Texture2D>();
    // Animações
    _animations = std::map<std::string, Animation*>();
    // Comportamentos
    _behaviours = std::map<std::string, Behaviour*>();
    // Objetos
    _ship = nullptr;
    _bullets = std::list<MotionObject*>();
    _aliens = std::list<Alien*>();

    // Score
    _score = 0u;

    // Game status
    _game_status = true;
    _pause = false;

    // Ponteiro para o jogo para as instâncias MotionObject;
    MotionObject motion_object;
    motion_object.set_game(this);

}

Game::~Game() {
    // Deleta toda a memória alocada no HEAP
    delete _ship;

    for (std::pair<std::string, Behaviour*> behaviour_pair : _behaviours) {
        delete behaviour_pair.second;
    }

    for (std::pair<std::string, Animation*> animation_pair : _animations) {
        delete animation_pair.second;
    }

    for (MotionObject* bullet : _bullets) {
        delete bullet;
    }

    for (Alien* alien : _aliens) {
        delete alien;
    }

}

void Game::initialize() {
    // Inicializa a janela do jogo e estabelece o FPS
    SetTargetFPS(FPS);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    // Carregando a fonte do jogo
    _font = std::strcmp(GAME_FONT, "default") == 0 ? GetFontDefault() : LoadFont(GAME_FONT);

    // Carregando todas as texturas do jogo
    _load_graphics();

    // Criando as animações do jogo
    _load_animations();

    // Criando os comportamentos do jogo
    _load_behaviours();

    // Construindo os objetos: comportamento + animação
    _build_objects();
    
}


void inline Game::_load_graphics() {
    // Armazena todas as texturas e os retângulos fontes cobrindo toda a imagem
    _textures["background"] = LoadTexture(BACKGROUND_TEXTURE);
    _textures["explosion"] = LoadTexture(EXPLOSION_TEXTURE);
    _textures["power-up"] = LoadTexture(POWERUP_TEXTURE);    

    _textures["ship"] = LoadTexture(SHIP_TEXTURE);
    _textures["alien"] = LoadTexture(ALIEN_TEXTURE);
    _textures["bullet"] = LoadTexture(BULLET_TEXTURE);                   

}

void inline Game::_load_animations() {
    // Animação do jogo
    _animations["explosion"] = new AnimationFPS(&_textures.at("explosion"), Vector2 {5, 1}, 0.1f);
    _animations["alien"] = new AnimationFPS(&_textures.at("alien"), Vector2 {4, 4}, 0.2f);
    _animations["ship"] = new AnimationFPS(& _textures.at("ship"), Vector2 {4, 3}, 0.2f);
    _animations["bullet"] = new AnimationFPS(&_textures.at("bullet"), Vector2 {4, 3}, 0.2f);
}

void inline Game::_load_behaviours() {
    // Comportamentos do jogo; 
    _behaviours["follow-mouse"] = new FollowMouseBehaviour(1.0f);
    _behaviours["default"] = new Behaviour();
    _behaviours["default-ship"] = new DefaultShipBehaviourS(&_key_inputs, Vector2 {10, 0.0});
}

void inline Game::_build_objects() {
    // Todos os objetos serão construídos através de uma fleet.load(); fleet é uma classe a ser implementada
    // Construindo a nave do jogador
    Vector2 velocity = {10.0f, 0.0f};
    Vector2 acceleration = {0.0f, 0.0f};
    Vector2 dimension = {90.0f, 90.0f};
    Vector2 position = {SCREEN_WIDTH/2, SCREEN_HEIGHT - dimension.y/2.0f};

    // Configurando nave
    _ship = new Ship(position, velocity, acceleration, dimension);

    // Comportamento kamikaze com target: _ship
    // faz sentido criar esses comportamentos à medida que os objetos são criados
    _behaviours["kamikaze-to-ship"] = new KamikazeBehaviour(_ship);

    // Adicionando comportamentos e animações
    _ship->add_behaviour(_behaviours.at("default-ship"));
    _ship->add_animation(_animations.at("ship"));
    _build_aliens();
   
}

 void Game::_build_aliens() {
    // Construindo os aliens
    _aliens.push_back(new Alien(Vector2 {50.0f, 30.0f}, Vector2 {0.0f, 0.0f}, Vector2 {0.01f, 0.0f}, Vector2 {80.0f, 80.0f}));
    _aliens.push_back(new Alien(Vector2 {300.0f, 40.0f}, Vector2 {0.0f, 0.0f}, Vector2 {0.01f, 0.0f}, Vector2 {100.0f, 100.0f}));
    _aliens.push_back(new Alien(Vector2 {500.0f, 50.0f}, Vector2 {0.0f, 0.0f}, Vector2 {0.01f, 0.0f}, Vector2 {110.0f, 110.0f}));
    _aliens.push_back(new Alien(Vector2 {800.0f, 50.0f}, Vector2 {0.0f, 0.0f}, Vector2 {0.01f, 0.0f}, Vector2 {50.0f, 50.0f}));

    for (Alien* alien : _aliens) {
        alien->add_behaviour(_behaviours.at("kamikaze-to-ship"));
        alien->add_animation(_animations.at("alien"));
    }
 }



void Game::show_menu() {
    bool menu_active = true;
    int selected_option = 0;

    while (menu_active) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Desenhar o texto do menu
        DrawText("Menu", SCREEN_WIDTH / 2 - 50, 100, 30, WHITE);

        // Desenhar as opções do menu
        DrawText("Start", SCREEN_WIDTH / 2 - 40, 200, 20, selected_option == 0 ? RED : WHITE);
        DrawText("Exit", SCREEN_WIDTH / 2 - 30, 250, 20, selected_option == 1 ? RED : WHITE);

        // Lógica de seleção das opções
        if (IsKeyPressed(KEY_DOWN)) {
            selected_option = (selected_option + 1) % 2;
        }
        else if (IsKeyPressed(KEY_UP)) {
            selected_option = (selected_option - 1 + 2) % 2;
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            if (selected_option == 0) {
                // Opção "Start" selecionada
                menu_active = false;
            }
            else if (selected_option == 1) {
                // Opção "Exit" selecionada
                CloseWindow();
                exit(0);
            }
        }

        EndDrawing();
    }
}


void Game::run_loop() {
    
    // Loop principal do jogo
    show_menu();

     while(!WindowShouldClose() && _game_status) {

        _process_input();
        _update_game();
        _draw_game();
    }

}


void Game::_process_input() {
    // Captura as entradas: mouse e teclado
    if (IsKeyPressed(KEY_P)){
        _pause = !_pause;
    }
    _mouse_position = GetMousePosition();

    _key_inputs.at("move-right") = IsKeyDown(MOVE_RIGHT_KEY);
    _key_inputs.at("move-left") = IsKeyDown(MOVE_LEFT_KEY);
    _key_inputs.at("fire") = IsKeyDown(FIRE_KEY);

}

void Game::_update_game() {
    if(_pause == true){
        return;
    }

    float time = GetFrameTime();

    // Atualiza as animações do jogo
    for (std::pair<std::string, Animation*> animation_pair : _animations) {
        animation_pair.second->update(time);
    }
    
    // Atualiza as balas do jogo
    for (MotionObject* bullet : _bullets) {
        bullet->update(); 
    }

    // Atualiza os aliens do jogo
    for (Alien* alien : _aliens) {
        alien->update();
    }
  
    // Atualização a nave do jogador
    _ship->update(time);

    // Checar colisões [pode ser uma função separa no run_loop]
    _check_colisions();
}

void Game::_check_colisions() {
    // Checa colisões de aliens contra tiro, nave ou limites da tela
    Rectangle ship_rectangle = _ship->get_rectangle();
    for (std::list<Alien*>::iterator it_a=_aliens.begin(); it_a!=_aliens.end();) {
        
        if ((*it_a)->get("position").y > SCREEN_HEIGHT) {
            delete *it_a;
            it_a = _aliens.erase(it_a);

            continue;
        }
        
        // Checar colisão entre os retângulos do jogador e do alien: resetar jogo
        if (CheckCollisionRecs(ship_rectangle, (*it_a)->get_rectangle())) {
            _reset_game();
            return;
        }

        bool colision=false;
        // Checar colisão entre os retângulos do alien com os retângulos das balas
        for (std::list<MotionObject*>::iterator it_b=_bullets.begin(); it_b!=_bullets.end();) {
             if (CheckCollisionRecs((*it_a)->get_rectangle(), (*it_b)->get_rectangle())) {
                // Houve colisão
                colision=true;
                // Atualiza o score do jogo
                _score += (*it_a)->get_score();
                std::cout << TERMINAL_BOLDCYAN << "SCORE: " << _score << TERMINAL_RESET << std::endl;
                // deleta o alien e a bala do HEAP e do estado do jogo
                delete *it_a;
                it_a = _aliens.erase(it_a);
                delete *it_b;
                it_b = _bullets.erase(it_b);

                break;
             }

            // Bala atinge o topo da tela
            if ((*it_b)->get("position").y < 0) {
                delete (*it_b);
                it_b = _bullets.erase(it_b);
                continue;
             }
            
            // Nenhuma colisão: passar para a próxima bala
            ++it_b;
        }

        if (!colision) {
            ++it_a;
        }

    }
}

void Game::_reset_game() {
    // Diminui a vida da nave e checa game_over
    if (_ship->kill_ship() == 0) {
        _game_over();
        return;
    }
    
    // Reinicio a nave na posição bottom-center da tela
    _ship->set("position", Vector2 {SCREEN_WIDTH/2, SCREEN_HEIGHT - _ship->get("dimension").y/2.0f});
    
    // Deletar todos dos objetos
    // Remover as balas
    for (MotionObject* bullet : _bullets) {
        delete bullet;
    }

    _bullets.clear();
 
    // Remover os aliens
    for (Alien* alien : _aliens) {
        delete alien;
    }
    _aliens.clear();

    // Reconstruir os aliens
    _build_aliens();
    // Aguarde um segundo antes de desenhar a nova frota
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

}

void Game::_game_over() {
    std::cout << TERMINAL_BOLDRED << "FIM DE JOGO" << TERMINAL_RESET << std::endl;
    _game_status = false;
}

void Game::_draw_game() {
    // Desenha todos os objetos do jogo
    BeginDrawing();

    ClearBackground(BLACK);

     // Desenha o background com a textura especificada
    Texture2D bg_texture = _textures.at("background");
    DrawTexturePro(bg_texture, (Rectangle) {0, 0, (float) bg_texture.width, (float) bg_texture.height}, 
    (Rectangle) {0, 0, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT}, 
    Vector2Zero(), 0, WHITE);

    // Desenha o Score do jogo
    DrawTextEx(_font, std::to_string(_score).c_str(), Vector2 {8, 8}, SCORE_FONT_SIZE, 1.0f, SCORE_FONT_COLOR);

    // Desenha as balas com as animações associadas
    for (MotionObject* bullet : _bullets) {
        bullet->draw();
    }

    // Desenha os aliens com as animações associadas
    for (Alien* alien : _aliens) {
        alien->draw();
    }

    // Desenha a nave com as animações associadas
    _ship->draw();

    // Desenha as vidas da nave
    for (int i=1; i < _ship->get_life()+1; ++i) {
        Texture2D ship_tx = _textures.at("ship");
        DrawTexturePro(ship_tx, (Rectangle) {0, 0, (float) ship_tx.width/4.0f, (float) ship_tx.height/3.0f}, 
        (Rectangle) {SCREEN_WIDTH - i*35.0f, 0, 30.0f, 30.0f}, 
        Vector2Zero(), 0.0f, WHITE);
    }

    if(_pause == true){
        DrawText("PAUSED", 490, 420, 50, YELLOW);
    }


    EndDrawing();
}

void Game::shutdown() {
    UnloadFont(_font);
    _unload_graphics();
    CloseWindow();
}

void inline Game::_unload_graphics() {
     // Libera memória alocada para os gráficos/texturas
    for (std::pair<std::string, Texture2D> tx_pair : _textures) {
        UnloadTexture(tx_pair.second);
    }
}

void Game::add_bullet(MotionObject* bullet) {
    _bullets.push_back(bullet);
}

Behaviour* Game::get_behaviour(std::string key) {
    return _behaviours.at(key);
}

Animation* Game::get_animation(std::string key) {
    return _animations.at(key);
}

 bool Game::get_inputs(std::string key){
    return _key_inputs.at(key);
 }
 