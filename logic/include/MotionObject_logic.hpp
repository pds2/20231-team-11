#ifndef MOTION_OBJECT_LOGIC_HPP
#define MOTION_OBJECT_LOGIC_HPP

#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <string>

#include "../logic/include/Structs_logic.hpp"
// #include "../logic/include/Settings_logic.hpp"
// #include "../logic/include/Animation_logic.hpp"

// class Structs_logic;
class Settings_logic;
class Animation_logic;

class MotionObject_logic {
    public:
        MotionObject_logic();

        MotionObject_logic(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 dimension, float speed_limit = 1.0f, float acceleration_limit = 0.5f);

        ~MotionObject_logic();

        void update();

        void draw();

        //void add_behaviour(Behaviour_logic* behaviour);

        void add_animation(Animation_logic* animation);

        void set(std::string key, Vector2 value);

        Vector2 get(std::string key);

        Retangulo get_rectangle();

        float get_speed_limit();

        float get_acceleration_limit();

        //void set_game(Game_logic* game);

    protected:
        //static Game_logic* _game;
        std::map<std::string, Vector2> _parameters;
        
        Retangulo _rectangle;

        //std::vector<Behaviour_logic*> _behaviours;

        std::vector<Animation_logic*> _animations;

        void _update_rectangle();

        float _speed_limit;

        float _acceleration_limit;
};

#endif
