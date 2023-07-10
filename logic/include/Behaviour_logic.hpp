#ifndef BEHAVIOUR_LOGIC_HPP
#define BEHAVIOUR_LOGIC_HPP

#include "../logic/include/MotionObject_logic.hpp"
#include "../logic/include/Structs_logic.hpp"

/**
 * @brief Classe base para comportamentos de objetos em movimento
 */
class Behaviour_logic {
    public:
        /**
         * @brief Construtor padrão do comportamento
         */
        Behaviour_logic();

        /**
         * @brief Destrutor do comportamento
         */
        ~Behaviour_logic();

        /**
         * @brief Atualiza o objeto em movimento com base no comportamento
         * @param motion_object Ponteiro para o objeto em movimento
         */
        virtual void update(MotionObject_logic* motion_object);
};


/**
 * @brief Comportamento padrão para a nave
 */
class DefaultShipBehaviour_logic : public Behaviour_logic {
    public:
        /**
         * @brief Construtor do comportamento padrão da nave
         * @param key_inputs Ponteiro para o mapa de entradas do usuário
         * @param velocity Velocidade da nave
         */
        DefaultShipBehaviour_logic(std::map<std::string, bool>* key_inputs, Vector2 velocity);

        /**
         * @brief Destrutor do comportamento padrão da nave
         */
        ~DefaultShipBehaviour_logic();

        /**
         * @brief Atualiza a nave com base no comportamento padrão
         * @param motion_object Ponteiro para o objeto em movimento (nave)
         */
        void update(MotionObject_logic* motion_object) override;

        std::map<std::string, bool>* get_key_inputs();

        Vector2 get_velocity();

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
class KamikazeBehaviour_logic : public Behaviour_logic {
public:
    /**
     * @brief Construtor do comportamento kamikaze
     * @param target_object Ponteiro para o objeto alvo
     */
    KamikazeBehaviour_logic(MotionObject_logic* target_object);

    /**
     * @brief Destrutor do comportamento kamikaze
     */
    ~KamikazeBehaviour_logic();

    /**
     * @brief Atualiza o objeto em movimento com base no comportamento kamikaze
     * @param motion_object Ponteiro para o objeto em movimento (caça)
     */
    void update(MotionObject_logic* motion_object) override;

    float get_max_speed();

    float get_acceleration_factor();

    float get_threshold_speed();

    MotionObject_logic* get_target_object();

private:
    /**
     * @brief Ponteiro para o objeto alvo
     */
    MotionObject_logic* _target_object;

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
