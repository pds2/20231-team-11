//#include "../thirdy_party/raylib.hpp"
//#include "../thirdy_party/raymath.h"
#include "Game.hpp"

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
    _explosions = std::list<MotionObjectTemp*>();

    _fleets = Fleets(this);

    // Score
    _score = 0u;

    // Game status
    _game_status = false;

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

    // mostra logo do raylib
    logo();
}


void inline Game::_load_graphics() {
    // Armazena todas as texturas e os retângulos fontes cobrindo toda a imagem
    _textures["background"] = LoadTexture(BACKGROUND_TEXTURE);
    _textures["menu"] = LoadTexture(MENU_TEXTURE);
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
    _behaviours["default"] = new Behaviour();
    _behaviours["default-ship"] = new DefaultShipBehaviour(&_key_inputs, Vector2 {10, 0.0});
    _behaviours["zigzag"] = new ZigZagBehaviour();
}

void inline Game::_build_objects() {
    // Construindo a nave do jogador
    Vector2 dimension = {90.0f, 90.0f};
    _ship = new Ship(Vector2 {SCREEN_WIDTH/2, SCREEN_HEIGHT - dimension.y/2.0f},  Vector2 {10.0f, 0.0f}, Vector2 {0.0f, 0.0f}, dimension);

    // Comportamento kamikaze com target: _ship
    // faz sentido criar esses comportamentos à medida que os objetos são criados
    _behaviours["kamikaze-to-ship"] = new KamikazeBehaviour(_ship);

    // Adicionando comportamentos e animações
    _ship->add_behaviour(_behaviours.at("default-ship"));
    _ship->add_animation(_animations.at("ship"));
    
    // Carregando frota
    _fleets.load();
   
}

void Game::logo(){
    //
    int logoPositionX = SCREEN_WIDTH/2 - 128;
    int logoPositionY = SCREEN_HEIGHT/2 - 128;

    int framesCounter = 0;
    int lettersCount = 0;

    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;

    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;

    int state = 0;                  // Tracking animation states (State Machine)
    float alpha = 1.0f;             // Useful for fading 

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (state == 0)                 // State 0: Small box blinking
        {
            framesCounter++;

            if (framesCounter == 120)
            {
                state = 1;
                framesCounter = 0;      // Reset counter... will be used later...
            }
        }
        else if (state == 1)            // State 1: Top and left bars growing
        {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;

            if (topSideRecWidth == 256) state = 2;
        }
        else if (state == 2)            // State 2: Bottom and right bars growing
        {
            bottomSideRecWidth += 4;
            rightSideRecHeight += 4;

            if (bottomSideRecWidth == 256) state = 3;
        }
        else if (state == 3)            // State 3: Letters appearing (one by one)
        {
            framesCounter++;

            if (framesCounter/12)       // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }

            if (lettersCount >= 10)     // When all letters have appeared, just fade out everything
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (state == 0)
            {
                if ((framesCounter/15)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
            }
            else if (state == 1)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
            }
            else if (state == 2)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
                DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

                DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
            }
            else if (state == 3)
            {
                DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

                DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
                DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

                DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

                DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, alpha));
            }
            else if (state == 4)
            {
                break;
            }
        EndDrawing();
    }
    ClearBackground(RAYWHITE);
    //
}

void Game::_show_menu() {
    int selected_option = 0;

    while (!_game_status) {
        BeginDrawing();

        Texture2D menu_texture = _textures.at("menu");
        DrawTexturePro(menu_texture, (Rectangle) {0, 0, (float) menu_texture.width, (float) menu_texture.height}, 
        (Rectangle) {0, 0, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT}, 
        Vector2Zero(), 0, WHITE);

        // Desenhar as opções do menu
        DrawText("Menu", SCREEN_WIDTH / 2 - MeasureText("Menu", 30) / 2, 100, 30, WHITE);
        DrawText("Start", SCREEN_WIDTH / 2 - MeasureText("Start", 20) / 2, 200, 20, selected_option == 0 ? RED : WHITE);
        DrawText("Exit", SCREEN_WIDTH / 2 - MeasureText("Exit", 20) / 2, 250, 20, selected_option == 1 ? RED : WHITE);

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
                _game_status = true;
            }
            else if (selected_option == 1) {
                // Opção "Exit" selecionada
                shutdown();
                exit(0);
            }
        }

        EndDrawing();
    }
}


void Game::run_loop() {
    
    // Loop principal do jogo
    
     while(!WindowShouldClose()) {
        _show_menu();
        _process_input();
        _update_game();
        _draw_game();
    }

}

void Game::_process_input() {
    // Captura as entradas: mouse e teclado
    _mouse_position = GetMousePosition();

    _key_inputs.at("move-right") = IsKeyDown(MOVE_RIGHT_KEY);
    _key_inputs.at("move-left") = IsKeyDown(MOVE_LEFT_KEY);
    _key_inputs.at("fire") = IsKeyDown(FIRE_KEY);

}

void Game::_update_game() {
    // Atualiza objetos do jogo: balas, nave, aliens e explosoes
    _update_objects();

    // Checar colisões entre os objetos
    _check_colisions();

    // Deleta objetos mortos
    _delete_deads();
}

void Game::_update_objects() {
    float time = GetFrameTime();
    // Atualiza as animações do jogo:  tempo
    for (std::pair<std::string, Animation*> animation_pair : _animations) {
        animation_pair.second->update(time);
    }
    
    // Atualiza as balas do jogo: movimento
    for (MotionObject* bullet : _bullets) {
        bullet->update(); 
    }

    // Atualiza os aliens do jogo
    for (Alien* alien : _aliens) {
        alien->update();
    }

    //Atualiza as explosões do jogo: movimento e tempo
    for (MotionObjectTemp* explosion : _explosions) {
        explosion->update(time);
    }
  
    // Atualização a nave do jogador : movimento e tempo
    _ship->update(time);
}

void Game::_check_colisions() {
    // Checa colisões de aliens contra tiro, nave ou limites da tela
    Rectangle ship_rectangle = _ship->get_rectangle();
    for (std::list<Alien*>::iterator it_a=_aliens.begin(); it_a!=_aliens.end();) {
        
        if ((*it_a)->get("position").y > SCREEN_HEIGHT) {
            (*it_a)->kill();
            ++it_a;
            continue;
        }
        
        // Checar colisão entre os retângulos do jogador e do alien: resetar jogo
        if (CheckCollisionRecs(ship_rectangle, (*it_a)->get_rectangle())) {
            _ship->kill();
            (*it_a)->kill();
            std::cout << TERMINAL_BOLDBLACK << "Ship Colission!"<< TERMINAL_RESET << std::endl;

            _reset_game();
            return;
        }

        bool colision=false;
        // Checar colisão entre os retângulos do alien com os retângulos das balas
        for (std::list<MotionObject*>::iterator it_b=_bullets.begin(); it_b!=_bullets.end();++it_b) {
             if (CheckCollisionRecs((*it_a)->get_rectangle(), (*it_b)->get_rectangle())) {
                // Houve colisão
                colision=true;
                // Atualiza o score do jogo
                _score += (*it_a)->get_score();
                std::cout << TERMINAL_BOLDCYAN << "SCORE: " << _score << TERMINAL_RESET << std::endl;
                // cria uma explosão
                MotionObjectTemp* explosion = new MotionObjectTemp(0.5f, 0.0f, (*it_a)->get("position"), 
                Vector2 {0, 0}, Vector2 {20, 50}, (*it_a)->get("dimension"));

                // Adiciona comportamento a explosão
                explosion->add_behaviour(_behaviours.at("default"));

                // Adiciona animação a explosão
                explosion->add_animation(_animations.at("explosion"));
                
                // Adiciona a explosão ao estado do jogo
                _explosions.push_back(explosion);

                (*it_a)->kill();
                (*it_b)->kill();
                ++it_a;
                break;
             }

            // Bala atinge o topo da tela
            if ((*it_b)->get("position").y < 0) {
                (*it_b)->kill();
             }
            
        }

        if (!colision) {
            ++it_a;
        }

    }
}

void Game::_delete_deads() {
    for (std::list<MotionObject*>::iterator it_b = _bullets.begin(); it_b != _bullets.end();) {
        if (!((*it_b))->is_alive()) {
            delete (*it_b);
            it_b = _bullets.erase(it_b);
        } else {
            ++it_b;
        }
    }

    for (std::list<Alien*>::iterator it_a = _aliens.begin(); it_a != _aliens.end();) {
        if (!((*it_a)->is_alive())) {
            delete (*it_a);
            it_a = _aliens.erase(it_a);
        } else {
            ++it_a;
        }
    }

    for (std::list<MotionObjectTemp*>::iterator it_e = _explosions.begin(); it_e != _explosions.end();) {
        if (!((*it_e))->is_alive()) {
            delete (*it_e);
            it_e = _explosions.erase(it_e);
        } else {
            ++it_e;
        }
    }

    if (_aliens.empty() && _game_status) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            _fleets.load();
    }
}

void Game::_reset_game() {
    // Deletar todos dos objetos: exceto a nave
    _clear();

    // Diminui a vida da nave e checa game_over
    if (!(_ship->is_alive())) {
        _game_over();
        return;
    }
    
    // Reinicio a nave na posição bottom-center da tela
    _ship->set("position", Vector2 {SCREEN_WIDTH/2, SCREEN_HEIGHT - _ship->get("dimension").y/2.0f});

    // Reconstruir os aliens
    _fleets.load();
    // Aguardar um segundo antes de desenhar a nova frota
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

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

    // Desenha as explosões no jogo
    for (MotionObjectTemp* explosion : _explosions) {
        explosion->draw();
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

void Game::add_alien(Alien* alien) {
    _aliens.push_back(alien);
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

void Game::_clear() {
    // Limpa o estado do jogo: elimina balas, aliens e explosões
    // Não elimina a nave
    for (MotionObject* bullet : _bullets) {
        delete bullet;
    }

    _bullets.clear();
 
    // Remover os aliens
    for (Alien* alien : _aliens) {
        delete alien;
    }
    _aliens.clear();

    // Remover explosões
    for (MotionObjectTemp* explosion : _explosions) {
        delete explosion;
    }
    _explosions.clear();
} 
