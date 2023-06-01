#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <raylib-cpp.hpp>
#include <map>
#include <iostream>

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
        virtual void assertion(std::map<std::string, Vector2>* parameters_motion); 

};


class DefaultBulletBehaviour : public Behaviour {
    // Movimento com velocidade vertical constante da bala
    public:
        DefaultBulletBehaviour();
        ~DefaultBulletBehaviour();

        virtual void update(MotionObject* motion_object) override;          
        
};


class DefaultShipBehaviour : public Behaviour {
    // Movimento com velocidade e aceleração da nave
    // Limites inferior e superior de velocidades estabelecidos
    public:
        DefaultShipBehaviour(std::map<std::string, bool>* key_inputs);
        ~DefaultShipBehaviour();

        virtual void update(MotionObject* motion_object) override;
        virtual void assertion(std::map<std::string, Vector2>* parameters_motion) override;    
    
    protected:
        std::map<std::string, bool>* _key_inputs; 
          
        
};

class AcceleredShipBehaviour : public DefaultShipBehaviour {
    public:
        AcceleredShipBehaviour(std::map<std::string, bool>* key_inputs, float max_speed=50.0f, float stop_speed=0.5f);
        ~AcceleredShipBehaviour();

        virtual void update(MotionObject* motion_object) override;
        virtual void assertion(std::map<std::string, Vector2>* parameters_motion) override; 

    protected:
        float _max_speed;
        float _stop_speed;
        // Checa se a velocidade está fora dos limites inferior e superior permitidos
        void _check_velocity_edges(Vector2* velocity);
        // Função vazia para objetos AcceleredShipBehaviour; Interface
        virtual void _check_resistance(Vector2* velocity, bool move_right, bool move_left);
    
};

class ResistanceShipBehaviour : public AcceleredShipBehaviour {
    // Movimento da nave acelerado com resistência de um fluído hipotético
    // "Motores Desligados" implica em desaceleração da nave
    public:
        ResistanceShipBehaviour(std::map<std::string, bool>* key_inputs, float stop_speed=0.5f, float max_speed=50.0f, float dynamic_resistance=0.1f);
        ~ResistanceShipBehaviour();

    private:
        void _check_resistance(Vector2* velocity,bool move_right, bool move_left) override;
        float _dynamic_resistance;
};

class KamikazeBehaviour : public Behaviour {
    // Comportamento de caça a um MotionObject objetivo/target
    // A aceleração, velocidade são próprios do MotionObject
    // Esse comportamento determina apenas a resistência do dinâmica, a velocidade máxima e a velocidade de parada
    public:
        KamikazeBehaviour(MotionObject* target_object);
        ~KamikazeBehaviour();

        void update(MotionObject* motion_object) override;
        void assertion(std::map<std::string, Vector2>* parameters_motion) override;
    
    private:
        MotionObject* _target_object;
        float _max_speed;
        float _acceleration_factor;
        float _threshold_speed;

        
};

// class ZigZagBehaviour : public Behaviour {
//     public:
//         ZigZagBehaviour();
//         ZigZagBehaviour(float edge_x, float step_y);
//         ~ZigZagBehaviour();
        
//         void update(Alien* alien);
    
//     private:
//         // distância em que o alien pode chegar das laterias da tela
//         float _edge_x;

//         // distância que o alien percorre até retornar ao movimento horizontal
//         float _step_y;

// };

class FollowMouseBehaviour : public Behaviour {
    public:
        FollowMouseBehaviour();
        ~FollowMouseBehaviour();

        void update(MotionObject* motion_object) override;
};

#endif