#ifndef SHIP_H
#define SHIP_H

#include <raylib-cpp.hpp>
#include <string>
#include <map>

#include "Game.hpp"
#include "MotionObject.hpp"

class Game;

class Ship : public MotionObject {
    public:
        Ship();
        Ship(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 ship_dimension, std::string graphic_key);
        
        ~Ship();

        bool is_charged();

        void add_charge();
        void fire_bullet(Game* game);

        void draw(std::map<std::string, Texture2D>& textures, float* timer);
    
    private:
        void _update_frame();
        unsigned _total_charge;
        unsigned _current_charge;

        // Tempo para alterar o frame
        float _timer_frame;

        // Número total de frames
        unsigned _num_frames;

        // Frame corrente
        unsigned _frame;
        
 
};



#endif