#ifndef BEHAVIOUR_HPP
#define BEHAVIOUR_HPP

#include "MotionObject.hpp"
#include "Colors.hpp"
#include "Settings.hpp"

class MotionObject;

// Determina o comportamento cinemático do objeto (posicao e velocidade)
class Behaviour {
    public:
        Behaviour();
        ~Behaviour();

        virtual void update(MotionObject* motion_object);
        void update_acceleration(MotionObject* motion_object, Vector2 delta_acceleration);

};


class FollowMouseBehaviour : public Behaviour {
    public:
        FollowMouseBehaviour(float delta_acceleration_size);
        ~FollowMouseBehaviour();

        void update(MotionObject* motion_object) override;
    
    private:
        float _delta_acceleration_size;
};


class DefaultShipBehaviourS : public Behaviour {
    // Movimento de velocidade constante da nave
    public:
        DefaultShipBehaviourS(std::map<std::string, bool>* key_inputs, Vector2 velocity);
        ~DefaultShipBehaviourS();

        virtual void update(MotionObject* motion_object) override;
    
    protected:
        std::map<std::string, bool>* _key_inputs;
        Vector2 _velocity; 
          
        
};

// KAMIKAZE_BEHAVIOUR
class KamikazeBehaviour : public Behaviour {
    // Comportamento de caça a um MotionObject objetivo/target
    // A aceleração, velocidade são próprios do MotionObject
    // Esse comportamento determina apenas a resistência do dinâmica, a velocidade máxima e a velocidade de parada
    public:
        KamikazeBehaviour(MotionObject* target_object);
        ~KamikazeBehaviour();

        void update(MotionObject* motion_object) override;
    
    private:
        MotionObject* _target_object;
        float _max_speed;
        float _acceleration_factor;
        float _threshold_speed;

        
};

#endif