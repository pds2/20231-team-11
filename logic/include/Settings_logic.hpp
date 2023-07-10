#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

enum class Cores {
    LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN, WHITE, BLACK, BLANK, MAGENTA, RAYWHITE
};

class Color {
    private:
        Cores _cor;

    public:
        Color(Cores cor);

        Cores getColor() const;
        
        bool operator==(Cores cor) const;
};

class Config {
    public:
        static const int SCREEN_WIDTH;
        static const int SCREEN_HEIGHT;

        static const std::string SCREEN_TITLE;
        static const int FPS;

        static const std::string BACKGROUND_TEXTURE;
        static const std::string MENU_TEXTURE;
        static const std::string SHIP_TEXTURE;
        static const std::string ALIEN_TEXTURE;
        static const std::string BULLET_TEXTURE;
        static const std::string EXPLOSION_TEXTURE;
        static const std::string POWERUP_TEXTURE;

        static const int SCORE_FONT_SIZE;
        static const Color SCORE_FONT_COLOR;

        static const std::string GAME_FONT;
};

#endif
