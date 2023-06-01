#include <raylib-cpp.hpp>
#include <string>
#include <map>

class Animation {
    public:
        Animation();
        Animation(Vector2 position, Vector2 animation_dimension);
        ~Animation();

        void draw(std::map<std::string, Texture2D>& textures, float* timer);

    private:
        Vector2 _animation_dimension;
        Vector2 _position;
        std::string _graphic_key;

        unsigned _num_frames;
        unsigned _frame;
        float _timer_frame;

        void _update_frame();
        
};