#include <raylib-cpp.hpp>

#include "Game.hpp"

int main() {
    
    // Inicialização
    Game invaders;

    invaders.initialize();
    invaders.run_loop();
    
    return 0;
}