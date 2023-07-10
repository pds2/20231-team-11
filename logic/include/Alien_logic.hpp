#ifndef ALIEN_LOGIC_HPP
#define ALIEN_LOGIC_HPP

#include "../logic/include/MotionObject_logic.hpp"
#include "../logic/include/Structs_logic.hpp"


class Alien_logic : public MotionObject_logic {
public:
    /**
     * @brief Construtor padrão do alienígena
     */
    Alien_logic();

    /**
     * @brief Construtor do alienígena com especificação do estado
     * @param position Posição inicial do alienígena
     * @param velocity Velocidade inicial do alienígena
     * @param acceleration Aceleração inicial do alienígena
     * @param alien_dimension Dimensão do alienígena
     */
    Alien_logic(Vector2 position, Vector2 velocity, Vector2 acceleration, 
    Vector2 alien_dimension, float speed_limit=1.0f, float acceleration_limit=0.5f);

    /**
     * @brief Destrutor do alienígena
     */
    ~Alien_logic();

    /**
     * @brief Obtém a pontuação do alienígena
     * @return Pontuação do alienígena
     */
    unsigned get_score();

    void set_score(unsigned int score);

protected:
    /**
     * @brief Pontuação do alienígena
     */
    unsigned _score;
};

#endif
