#ifndef BEHAVIOUR_HPP
#define BEHAVIOUR_HPP

#include "MotionObject.hpp"
#include "Colors.hpp"
#include "Settings.hpp"

class MotionObject;

/**
 * @brief Classe base para comportamentos de objetos em movimento
 */
class Behaviour {
public:
    /**
     * @brief Construtor padrão do comportamento
     */
    Behaviour();

    /**
     * @brief Destrutor do comportamento
     */
    ~Behaviour();

    /**
     * @brief Atualiza o objeto em movimento com base no comportamento
     * @param motion_object Ponteiro para o objeto em movimento
     */
    virtual void update(MotionObject* motion_object);
};


/**
 * @brief Comportamento padrão para a nave
 */
class DefaultShipBehaviour : public Behaviour {
public:
    /**
     * @brief Construtor do comportamento padrão da nave
     * @param key_inputs Ponteiro para o mapa de entradas do usuário
     * @param velocity Velocidade da nave
     */
    DefaultShipBehaviour(std::map<std::string, bool>* key_inputs, Vector2 velocity);

    /**
     * @brief Destrutor do comportamento padrão da nave
     */
    ~DefaultShipBehaviour();

    /**
     * @brief Atualiza a nave com base no comportamento padrão
     * @param motion_object Ponteiro para o objeto em movimento (nave)
     */
    void update(MotionObject* motion_object) override;

protected:
    /**
     * @brief Ponteiro para o mapa de entradas do usuário
     */
    std::map<std::string, bool>* _key_inputs;

    /**
     * @brief Velocidade da nave
     */
    Vector2 _velocity;
};


/**
 * @brief Comportamento de caça kamikaze
 */
class KamikazeBehaviour : public Behaviour {
public:
    /**
     * @brief Construtor do comportamento kamikaze
     * @param target_object Ponteiro para o objeto alvo
     */
    KamikazeBehaviour(MotionObject* target_object);

    /**
     * @brief Destrutor do comportamento kamikaze
     */
    ~KamikazeBehaviour();

    /**
     * @brief Atualiza o objeto em movimento com base no comportamento kamikaze
     * @param motion_object Ponteiro para o objeto em movimento (caça)
     */
    void update(MotionObject* motion_object) override;

private:
    /**
     * @brief Ponteiro para o objeto alvo
     */
    MotionObject* _target_object;

    /**
     * @brief Velocidade máxima do comportamento kamikaze
     */
    float _max_speed;

    /**
     * @brief Fator de aceleração do comportamento kamikaze
     */
    float _acceleration_factor;

    /**
     * @brief Velocidade de parada do comportamento kamikaze
     */
    float _threshold_speed;
};

#endif
