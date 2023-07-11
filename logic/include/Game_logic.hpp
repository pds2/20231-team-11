#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <thread>
#include <map>
#include <string>
#include <iterator>
#include <iostream>
#include <list>

#include "../logic/include/Structs_logic.hpp"
#include "../logic/include/Behaviour_logic.hpp"
#include "../logic/include/Settings_logic.hpp"
#include "../logic/include/Animation_logic.hpp"
#include "../logic/include/MotionObject_logic.hpp"
#include "../logic/include/Ship_logic.hpp"
#include "../logic/include/Alien_logic.hpp"

/*
* @brief Classe principal do jogo responsável por gerenciar todos os objetos de movimento,
* comportamentos e animações
*/
class Game_logic {
    public:
        // Construtor e destrutor padrão do jogo
        Game_logic();

        // Adiciona bala ao estado do jogo
        void add_bullet(MotionObject_logic* bullet);
        void add_behaviour(std::string key, Behaviour_logic* behaviour);
        void add_animation(std::string key, Animation_logic* behaviour);
        void add_alien(Alien_logic* alien);

        // Setter e Getters
        Behaviour_logic* get_behaviour(std::string key);
        
        Animation_logic* get_animation(std::string key);

        bool get_inputs(std::string key);

        std::map<std::string, Texture2D> get_textures();

        Ship_logic* get_ship();

        std::list<MotionObject_logic*> get_bullets();

        std::list<Alien_logic*> get_aliens();

        unsigned int get_score();

        bool get_game_status();

        void set_ship(Ship_logic* ship);

        // Load graphics
        void _load_graphics();

        // Carrega comportamentos
        void _load_behaviours();

    private:
        // Gráficos
        std::map<std::string, Texture2D> _textures;

        // Comportamento do jogo
        std::map<std::string, Behaviour_logic*> _behaviours;

        // Animação do jogo
        std::map<std::string, Animation_logic*> _animations;

        // Fonte do jogo
        std::string _font;

        // Objetos do jogo
        Ship_logic* _ship;
        std::list<MotionObject_logic*> _bullets;
        std::list<Alien_logic*> _aliens;

        // Inputs
        std::map<std::string, bool> _key_inputs;
        Vector2 _mouse_position;

        // Score
        unsigned _score;

        // Game status
        bool _game_status;
};

#endif
