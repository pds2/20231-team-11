#ifndef MOTION_OBJECT_H
#define MOTION_OBJECT_H

#include <raylib-cpp.hpp>
#include <vector>
#include <iterator>
#include <map>
#include <string>
#include "Behaviour.hpp"


class Behaviour;

class MotionObject {
    public:
        // Construtor padrão
        MotionObject();

        // Construtor com especificação dos estado
        MotionObject(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 object_dimension, std::string graphic_key);

        // Destrutor
        ~MotionObject();

        // Atualiza a posição do objeto com base em comportamentos
        void update();

        // Desenha o objeto com a textura e source_rectangle especificados
        void draw(std::map<std::string, Texture2D>& textures, std::map<std::string, Rectangle>& src_full_rectangles);

        // Adiciona comportamentos para modificar a função update
        void add_behaviour(Behaviour* behaviour);

        std::vector<Behaviour*> get_behaviours();

        // Getters e Setters
        void set(std::string key, Vector2 value);
        Vector2 get(std::string key);

        Vector2 get_dimension();

        void set_dead();
    

    protected:
        // Posição, Velocidade e Aceleração
        std::map<std::string, Vector2> _parameters_motion;

        // Adicionar um comportamento
        std::vector<Behaviour*> _behaviours;

        // Dimensão do MotionObject
        Vector2 _object_dimension;

        bool _alive;

        std::string _graphic_key;

};

#endif