#include "Fleets.hpp"
#include "Game.hpp"


Game* Fleets::_game = nullptr;

Fleets::Fleets() {

}

Fleets::Fleets(Game* game) {
    _game = game;
    _id = 0;

    _fleets.push_back(&Fleets::fleet_1);
    _fleets.push_back(&Fleets::fleet_2);
    _fleets.push_back(&Fleets::fleet_3);
}

Fleets::~Fleets() {

}

void Fleets::set_up_aliens(Behaviour* behaviour, Animation* animation, std::vector<Alien*> aliens) {
    for (Alien* alien : aliens) {
        alien->add_animation(animation);
        alien->add_behaviour(behaviour);
    }
}



// Executa uma função frota na posição _id da lista de frotas
void Fleets::load() {

    // armazeno a frota do id corrente
    FuncaoVoidPtr fleet = _fleets.at(_id);

    // executa a frota
    fleet();
    // atualiza o id
    _id = _fleets.size() - 1 == _id ? 0 : _id + 1; 
}

void Fleets::add_aliens(std::vector<Alien*>& aliens, Alien* first_alien, ...)
{
    aliens.push_back(first_alien);

    va_list args;
    va_start(args, first_alien);

    Alien* current_alien = va_arg(args, Alien*);
    while (current_alien != nullptr)
    {
        aliens.push_back(current_alien);
        current_alien = va_arg(args, Alien*);
    }

    va_end(args);
}

void Fleets::add_aliens_to_game(std::vector<Alien*>& aliens) {
    for (Alien* alien : aliens) {
        _game->add_alien(alien);
    }
}


// Funcoes que constroem aliens no jogo
void Fleets::fleet_1() {
      
    Fleets fleets;
    // cria comportamento
    Behaviour* kamikaze = _game->get_behaviour("kamikaze-to-ship");

    // cria animação
    Animation* alien_animation = _game->get_animation("alien");

    // cria aliens
    Alien* a1 = new Alien(Vector2 {50.0f, 30.0f}, Vector2 {0.0f, 0.0f}, Vector2 {0.01f, 0.0f}, Vector2 {80.0f, 80.0f});
    Alien* a2 = new Alien(Vector2 {300.0f, 40.0f}, Vector2 {0.0f, 0.0f}, Vector2 {0.01f, 0.0f}, Vector2 {100.0f, 100.0f});
    Alien* a3 = new Alien(Vector2 {500.0f, 50.0f}, Vector2 {0.0f, 0.0f}, Vector2 {0.01f, 0.0f}, Vector2 {110.0f, 110.0f});
    Alien* a4 = new Alien(Vector2 {800.0f, 50.0f}, Vector2 {0.0f, 0.0f}, Vector2 {0.01f, 0.0f}, Vector2 {50.0f, 50.0f});
  
    std::vector<Alien*> aliens;
    fleets.add_aliens(aliens, a1, a2, a3, a4, nullptr);
    fleets.set_up_aliens(kamikaze, alien_animation, aliens);
    fleets.add_aliens_to_game(aliens);    
}

void Fleets::fleet_2() {
    Fleets fleets;
        // cria comportamento
    Behaviour* kamikaze = _game->get_behaviour("default");

    // cria animação
    Animation* alien_animation = _game->get_animation("alien");

    // cria aliens
    Alien* a1 = new Alien(Vector2 {50.0f, 30.0f}, Vector2 {0.0f, 5.0f}, Vector2 {0.01f, 0.0f}, Vector2 {80.0f, 80.0f});
    Alien* a2 = new Alien(Vector2 {300.0f, 40.0f}, Vector2 {0.0f, 5.0f}, Vector2 {0.01f, 0.0f}, Vector2 {100.0f, 100.0f});
    Alien* a3 = new Alien(Vector2 {500.0f, 50.0f}, Vector2 {0.0f, 5.0f}, Vector2 {0.01f, 0.0f}, Vector2 {110.0f, 110.0f});
    Alien* a4 = new Alien(Vector2 {800.0f, 50.0f}, Vector2 {0.0f, 5.0f}, Vector2 {0.01f, 0.0f}, Vector2 {50.0f, 50.0f});

    std::vector<Alien*> aliens;
    fleets.add_aliens(aliens, a1, a2, a3, a4, nullptr);
    fleets.set_up_aliens(kamikaze, alien_animation, aliens);
    fleets.add_aliens_to_game(aliens);   
}


void Fleets::fleet_3() {
    Fleets fleets;
        // cria comportamento
    Behaviour* zigzag = _game->get_behaviour("zigzag");

    // cria animação
    Animation* alien_animation = _game->get_animation("alien");

    // cria aliens
    Alien* a1 = new Alien(Vector2 {50.0f, 30.0f}, Vector2 {10.0f, 2.0f}, Vector2 {0.00f, 0.0f}, Vector2 {80.0f, 80.0f});

    std::vector<Alien*> aliens;
    fleets.add_aliens(aliens, a1, nullptr);
    fleets.set_up_aliens(zigzag, alien_animation, aliens);
    fleets.add_aliens_to_game(aliens);   
}
