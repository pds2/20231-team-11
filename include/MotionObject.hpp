#ifndef MOTION_OBJECT_HPP
#define MOTION_OBJECT_HPP

#include <raylib-cpp.hpp>
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <string>

class Game;
class Behaviour;
class Animation;

class MotionObject {
public:
    /**
     * @brief Construtor padrão do objeto em movimento
     */
    MotionObject();

    /**
     * @brief Construtor do objeto em movimento com especificação do estado cinemático
     * @param position Posição inicial do objeto
     * @param velocity Velocidade inicial do objeto
     * @param acceleration Aceleração inicial do objeto
     * @param dimension Dimensões do objeto
     * @param speed_limit Limite de velocidade do objeto (opcional, padrão é 1.0f)
     * @param acceleration_limit Limite de aceleração do objeto (opcional, padrão é 0.5f)
     */
    MotionObject(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 dimension, float speed_limit = 1.0f, float acceleration_limit = 0.5f);

    /**
     * @brief Destrutor do objeto em movimento
     */
    ~MotionObject();

    /**
     * @brief Atualiza a posição do objeto com base nos comportamentos
     */
    void update();

    /**
     * @brief Desenha o objeto com base nas animações em seu estado
     */
    void draw();

    /**
     * @brief Adiciona um comportamento para modificar a função de atualização
     * @param behaviour Ponteiro para o comportamento a ser adicionado
     */
    void add_behaviour(Behaviour* behaviour);

    /**
     * @brief Adiciona uma animação para modificar a função de desenho
     * @param animation Ponteiro para a animação a ser adicionada
     */
    void add_animation(Animation* animation);

    /**
     * @brief Define o valor de um parâmetro de movimento ou dimensão
     * @param key Chave do parâmetro
     * @param value Valor a ser definido
     */
    void set(std::string key, Vector2 value);

    /**
     * @brief Retorna o valor de um parâmetro de movimento ou dimensão
     * @param key Chave do parâmetro
     * @return Valor do parâmetro correspondente à chave
     */
    Vector2 get(std::string key);

    /**
     * @brief Retorna o retângulo correspondente ao objeto em movimento
     * @return Retângulo representando o objeto
     */
    Rectangle get_rectangle();

    /**
     * @brief Retorna o limite de velocidade do objeto
     * @return Limite de velocidade
     */
    float get_speed_limit();

    /**
     * @brief Retorna o limite de aceleração do objeto
     * @return Limite de aceleração
     */
    float get_acceleration_limit();

    /**
     * @brief Define o ponteiro para o jogo
     * @param game Ponteiro para o jogo
     */
    void set_game(Game* game);

protected:
    /**
     * @brief Ponteiro para o jogo
     */
    static Game* _game;

    /**
     * @brief Parâmetros de movimento e dimensão do objeto
     */
    std::map<std::string, Vector2> _parameters;

    /**
     * @brief Retângulo representando o objeto
     */
    Rectangle _rectangle;

    /**
     * @brief Comportamentos do objeto
     */
    std::vector<Behaviour*> _behaviours;

    /**
     * @brief Animações do objeto
     */
    std::vector<Animation*> _animations;

    /**
     * @brief Atualiza o retângulo do objeto
     */
    void _update_rectangle();

    /**
     * @brief Limite de velocidade do objeto
     */
    float _speed_limit;

    /**
     * @brief Limite de aceleração do objeto
     */
    float _acceleration_limit;
};

// class MotionObjectTemp : public MotionObject {
//     public:
//         MotionObjectTemp();
//         MotionObjectTemp(Game* game);
    
//     private:
//         float _born_time;
//         float _end_time;
// }

#endif
