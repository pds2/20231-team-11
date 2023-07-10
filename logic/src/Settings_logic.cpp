#include "../include/Settings_logic.hpp"

Color::Color(Cores cor) : _cor(cor) {}

Cores Color::getColor() const {
    return _cor;
}
        
bool Color::operator==(Cores cor) const {
    return _cor == cor;
}

const int Config::SCREEN_WIDTH = 1200;
const int Config::SCREEN_HEIGHT = 900;

const std::string Config::SCREEN_TITLE = "Invaders";
const int Config::FPS = 60;

const std::string Config::BACKGROUND_TEXTURE = "images/alexandria/mapa.png";
const std::string Config::MENU_TEXTURE = "images/space.png";
const std::string Config::SHIP_TEXTURE = "images/alexandria/ship_grid.png";
const std::string Config::ALIEN_TEXTURE = "images/alexandria/alien_grid.png";
const std::string Config::BULLET_TEXTURE = "images/alexandria/bullet_grid.png";
const std::string Config::EXPLOSION_TEXTURE = "images/explosion.png";
const std::string Config::POWERUP_TEXTURE = "images/power-up.png";

const int Config::SCORE_FONT_SIZE = 70;
const Color Config::SCORE_FONT_COLOR = Cores::BLACK;

const std::string Config::GAME_FONT = "default";