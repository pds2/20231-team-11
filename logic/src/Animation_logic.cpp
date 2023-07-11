#include "../logic/include/Animation_logic.hpp"

//
// ANIMATION
//

Animation_logic::Animation_logic() {

}

Animation_logic::~Animation_logic() {

}

void Animation_logic::update(float delta_time) {

}

float Animation_logic::get_width(){
    return _width;
}

float Animation_logic::get_height(){
    return _height;
}

void Animation_logic::set_width(float width){
    _width = width;
}

void Animation_logic::set_height(float height){
    _height = height;
}

//
// ANIMATION_FPS
//

AnimationFPS_logic::AnimationFPS_logic() : Animation_logic() {

}

AnimationFPS_logic::~AnimationFPS_logic() {

}

void AnimationFPS_logic::update(float delta_time) {
    _clock += delta_time;
    _update_frame();
}

void AnimationFPS_logic::_update_frame() {
    if (_clock >= _frame_timer) {
        _frame = _frame == _num_frames - 1 ? 0 : _frame+1;
        _clock = 0.0f;
    }
}

float AnimationFPS_logic::get_num_frames(){
    return _num_frames;
}

Vector2 AnimationFPS_logic::get_tx_frame_dim(){
    return _tx_frame_dim;
}

float AnimationFPS_logic::get_frame(){
    return _frame;
}
    
float AnimationFPS_logic::get_frame_timer(){
    return _frame_timer;
}

float AnimationFPS_logic::get_clock(){
    return _clock;
}

void AnimationFPS_logic::set_num_frames(float num_frames){
    _num_frames = num_frames;
}

void AnimationFPS_logic::set_tx_frame_dim(Vector2 tx_frame_dim){
    _tx_frame_dim = tx_frame_dim;
}

void AnimationFPS_logic::set_frame(float frame){
    _frame = frame;
}

void AnimationFPS_logic::set_frame_timer(float frame_timer){
    _frame_timer = frame_timer;
}

void AnimationFPS_logic::set_clock(float clock){
    _clock = clock;
}

