#ifndef GAME_H
#define GAME_H

#include <raylib-cpp.hpp>
#include <map>
#include <string>
#include <vector>

#include "MotionObject.hpp"
#include "Alien.hpp"
#include "Ship.hpp"
#include "Behaviour.hpp"
#include "Settings.hpp"

class Game {
    public:
        Game();
        ~Game();

        // Configura janelas e inicializa objetos do jogo
        bool initialize();

        // Render Loop
        void run_loop();

        // Fecha jogo
        void shutdown();
    
    private:
        // Recebe entradas do usuário (teclado e mouse)
        void _process_input();

        // Altera o estado do jogo com base nas entradas
        void _update_game();

        // Desenha o novo estado do jogo
        void _draw_game();

        // Add objects
        void _add_alien(Alien* alien);

        // Checagem de colisões
        void _check_colisions();

        // Objetos que descrevem o estado do jogo
        Ship* _ship;
        std::vector<Alien*> _aliens;

        // Comportamentos do jogo
        std::vector<Behaviour*> _behaviours;

        // Inputs
        std::map<std::string, bool> _key_inputs;
        raylib::Vector2 _mouse_position;

        // Gráficos
        Texture2D _background_texture;
        Rectangle _src_screen_rectangle;
        
        Texture2D _ship_texture;
        Rectangle _src_ship_rectangle;

        Texture2D _alien_texture;
        Rectangle _src_alien_rectangle;
        
        

};

#endif