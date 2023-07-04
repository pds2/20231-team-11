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
};


class DefaultShipBehaviour : public Behaviour {
    // Movimento de velocidade constante da nave
    public:
        DefaultShipBehaviour(std::map<std::string, bool>* key_inputs, Vector2 velocity);
        ~DefaultShipBehaviour();

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