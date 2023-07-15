//#include <raylib-cpp.hpp>
#include "../thirdy_party/raylib.hpp"
#include "../thirdy_party/raymath.hpp"

#include "Game.hpp"

int main() {
    
    // Inicialização
    Game invaders;

    invaders.initialize();
    invaders.run_loop();
    invaders.shutdown();
    
    return 0;
}