#ifndef GAME_H
#define GAME_H

#include <raylib-cpp.hpp>
#include <thread>
#include <map>
#include <string>
#include <iterator>
#include <iostream>
#include <list>

#include "Behaviour.hpp"
#include "Colors.hpp"
#include "Settings.hpp"
#include "Animation.hpp"
#include "MotionObject.hpp"
#include "Ship.hpp"
#include "Alien.hpp"
#include "Fleets.hpp"

class Animation;
class Behaviour;

/*
 * @brief Classe principal do jogo responsável por gerenciar todos os objetos de movimento,
 * comportamentos e animações
 */
class Game {
public:
    /**
     * @brief Construtor padrão do jogo
     */
    Game();
    
    /**
     * @brief Destrutor padrão do jogo
     */
    ~Game();
    
    /**
     * @brief Inicializa as configurações e objetos do jogo
     */
    void initialize();
    
    /**
     * @brief Loop principal do jogo
     */
    void run_loop();

    /**
     * @brief Encerra o jogo
     */
    void shutdown();
    
    /**
     * @brief Adiciona uma bala ao estado do jogo
     * @param bullet Ponteiro para o objeto bala a ser adicionado
     */
    void add_bullet(MotionObject* bullet);

     /**
     * @brief Adiciona um alien ao estado do jogo
     * @param bullet Ponteiro para o obeto alien
     */
    void add_alien(Alien* alien);
    
    /**
     * @brief Retorna o comportamento correspondente à chave fornecida
     * @param key Chave do comportamento desejado
     * @return Ponteiro para o comportamento correspondente à chave
     */
    Behaviour* get_behaviour(std::string key);
    
    /**
     * @brief Retorna a animação correspondente à chave fornecida
     * @param key Chave da animação desejada
     * @return Ponteiro para a animação correspondente à chave
     */
    Animation* get_animation(std::string key);
    
    /**
     * @brief Retorna o estado do input correspondente à chave fornecida
     * @param key Chave do input desejado
     * @return Valor booleano indicando o estado do input
     */
    bool get_inputs(std::string key);

private:
    /**
     * @brief Processa as entradas do usuário (teclado e mouse)
     */
    void _process_input();
    
    /**
     * @brief Atualiza o estado do jogo com base nas entradas
     */
    void _update_game();

    void _update_objects();
    
    /**
     * @brief Desenha o novo estado do jogo
     */
    void _draw_game();
    
    /**
     * @brief Verifica se ocorreram colisões
     */
    void _check_colisions();
    
    /**
     * @brief Destroi objetos mortosa
     */
    void _delete_deads();
    
    /**
     * @brief Carrega as animações do jogo
     */
    void inline _load_animations();
    
    /**
     * @brief Carrega os comportamentos do jogo
     */
    void inline _load_behaviours();
    
    /**
     * @brief Carrega os gráficos do jogo
     */
    void inline _load_graphics();
    
    /**
     * @brief Descarrega os gráficos do jogo
     */
    void inline _unload_graphics();
    
    /**
     * @brief Constrói os objetos do jogo
     */
    void inline _build_objects();

    
    /**
     * @brief Reinicia o jogo
     */
    void _reset_game();
    
    /**
     * @brief Finaliza o jogo
     */
    void _game_over();

    void _clear();
    
    // Gráficos
    std::map<std::string, Texture2D> _textures;
    
    // Comportamento do jogo
    std::map<std::string, Behaviour*> _behaviours;
    
    // Animação do jogo
    std::map<std::string, Animation*> _animations;
    
    // Fonte do jogo
    Font _font;
    
    // Objetos do jogo
    Ship* _ship;
    std::list<MotionObject*> _bullets;
    std::list<Alien*> _aliens;
    std::list<MotionObjectTemp*> _explosions;

    // Frotas
    Fleets _fleets;
    
    // Inputs
    std::map<std::string, bool> _key_inputs;
    Vector2 _mouse_position;
    
    // Pontuação
    unsigned _score;
    
    // Status do jogo
    bool _game_status;
};

#endif
