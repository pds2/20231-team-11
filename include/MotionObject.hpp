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

        MotionObject();
        ~MotionObject();

        void update();
        virtual void draw(Texture2D& texture, Rectangle src_object_rectangle);

        void add_behaviour(Behaviour* behaviour);

        std::vector<Behaviour*> get_behaviours();

        // Getters e Setters
        void set(std::string key, Vector2 value);
        Vector2 get(std::string key);

        Vector2 get_dimension();

        void set_dead();
    

    protected:
        std::map<std::string, Vector2> _parameters_motion;
      
        std::vector<Behaviour*> _behaviours;

        Vector2 _object_dimension;

        bool _alive;

};

#endif