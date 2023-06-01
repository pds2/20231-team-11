#include "Animation.hpp"

Animation::Animation() {

}

Animation::Animation(Vector2 position, Vector2 animation_dimension) {
    _position = position;
    _animation_dimension = animation_dimension;
    _timer_frame = 0.2f;
    _frame = 0;
    
    // Textura com 5 frames para a explosão
    _num_frames = 5;
}

Animation::~Animation() {

}

void Animation::_update_frame() {
    _frame = _frame == _num_frames - 1 ? 0 : _frame+1;
}

void Animation::draw(std::map<std::string, Texture2D>& textures, float* timer) {
    if (*timer >= _timer_frame) {
        _update_frame();
        *timer = 0.0f;
    }

    float width = textures.at(_graphic_key).width;
    float height = textures.at(_graphic_key).height;

    DrawTexturePro(textures.at(_graphic_key), (Rectangle) {(float) _frame * (width/4.0f), 0, width/4.0f, height},
                   (Rectangle) {_position.x, _position.y, 
                    _animation_dimension.x, _animation_dimension.y},
                    Vector2 {_animation_dimension.x/2, _animation_dimension.y/2}, 0, WHITE);
};