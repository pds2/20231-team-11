#ifndef FLEETS_HPP
#define FLEETS_HPP

//#include <raylib-cpp.hpp>
#include "../thirdy_party/raylib.hpp"
#include "../thirdy_party/raymath.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <string>


class Game;
class Behaviour;
class Animation;
class Alien;

class Fleets {
public:
    Fleets();       
    /**
     * @brief Construtor padrão do objeto Fleets
     */
    Fleets(Game* game);

    /**
     * @brief Destrutor do objeto Fleets
     */
    ~Fleets();

    // executa carregamento de frota com base no id
    void load();

    void add_aliens(std::vector<Alien*>& aliens, Alien* first_alien ...);

    // Adiciona o mesmo comportamento e animação à um grupo de aliens
    void set_up_aliens(Behaviour* behaviour, Animation* animation, std::vector<Alien*> aliens);

    void add_aliens_to_game(std::vector<Alien*>& aliens);

    // Funcoes que constroem aliens no jogo
    static void fleet_1();
    static void fleet_2();
    static void fleet_3();

protected:
    typedef void (*FuncaoVoidPtr)();
    
    unsigned _id;
    std::vector<FuncaoVoidPtr> _fleets;
    
    static Game* _game;
};


#endif
