#include <raylib-cpp.hpp>

class Textures {
    public:
        Texture2D ship_tx;
        Texture2D background_tx;
    
        Textures() {
            ship_tx = LoadTexture("images/spaceship_red.png");
            background_tx = LoadTexture("images/space.png");
        }

        ~Textures() {
            UnloadTexture(ship_tx);
            UnloadTexture(background_tx);
        }
};