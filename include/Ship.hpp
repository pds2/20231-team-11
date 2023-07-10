#ifndef SHIP_HPP
#define SHIP_HPP

#include "MotionObject.hpp"

class Ship : public MotionObject {
public:
    /**
     * @brief Construtor padrão da nave
     */
    Ship();

    /**
     * @brief Construtor da nave com especificação do estado
     * @param position Posição inicial da nave
     * @param velocity Velocidade inicial da nave
     * @param acceleration Aceleração inicial da nave
     * @param ship_dimension Dimensões da nave
     */
    Ship(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 ship_dimension, 
    float speed_limit=1.0f, float acceleration_limit=0.5f);
    
    /**
     * @brief Destrutor da nave
     */
    ~Ship();

    /**
     * @brief Atualiza a nave em cada quadro
     * @param delta_time Tempo desde o último quadro
     */
    void update(float delta_time);

    /**
     * @brief Verifica se a bala está carregada
     * @return Verdadeiro se a bala estiver carregada, falso caso contrário
     */
    bool is_charged();

    /**
     * @brief Dispara uma bala
     */
    void fire_bullet();

    /**
     * @brief Diminui a vida da nave
     * @return Nova vida da nave após o dano
     */
    int kill_ship();

    /**
     * @brief Retorna a vida atual da nave
     * @return Vida atual da nave
     */
    int get_life();

private:
    /**
     * @brief Carga total e carga atual da nave
     */
    float _total_charge;
    float _current_charge; 

    /**
     * @brief Vida da nave
     */
    int _life;
};

#endif
