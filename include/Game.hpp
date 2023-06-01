#ifndef GAME_H
#define GAME_H

#include <raylib-cpp.hpp>
#include <map>
#include <string>
#include <iterator>
#include <list>

#include "MotionObject.hpp"
#include "Ship.hpp"
#include "Alien.hpp"
#include "Behaviour.hpp"
#include "Settings.hpp"

class Ship;

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

        // Setters e Getters
        Behaviour* get_behaviour(std::string key);

        void add_bullet(MotionObject* bullet);
    
    private:
        // Recebe entradas do usuário (teclado e mouse)
        void _process_input();

        // Altera o estado do jogo com base nas entradas
        void _update_game();

        // Desenha o novo estado do jogo
        void _draw_game();

        // Checagem de colisões
        void _check_colisions();

        // Finaliza o jogo
        void _end_game();

        // Load graphics
        void inline _load_graphics();

        // Unload graphics
        void inline _unload_graphics();

        // Objetos que descrevem o estado do jogo
        Ship* _ship;
        std::list<Alien*> _aliens;
        std::list<MotionObject*> _bullets;
        std::list<MotionObject*> _deads;

        // Comportamentos do jogo
        std::map<std::string, Behaviour*> _behaviours;

        // Inputs
        std::map<std::string, bool> _key_inputs;
        raylib::Vector2 _mouse_position;

        // Gráficos
        std::map<std::string, Texture2D> _textures;
        std::map<std::string, Rectangle> _rectangles;

        // Flag booleana indicando status do jogo
        bool _game_status;
        

};

#endif