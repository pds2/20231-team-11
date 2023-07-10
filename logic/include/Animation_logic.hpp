#ifndef ANIMATION_LOGIC_HPP
#define ANIMATION_LOGIC_HPP

#include "../logic/include/Structs_logic.hpp"

class Animation_logic {
public:
    Animation_logic();

    //Animation_logic(Texture2D* texture);

    ~Animation_logic();

    //virtual void draw(MotionObject_logic* motion_object);

    virtual void update(float delta_time);

    float get_width();
    float get_height();

    void set_width(float width);
    void set_height(float height);

protected:
    //Texture2D* _texture;
    float _width;
    float _height;
};


class AnimationFPS_logic : public Animation_logic {
public:

    AnimationFPS_logic();

    //AnimationFPS_logic(Texture2D* texture, Vector2 tx_frames_dim, float frame_timer);

    ~AnimationFPS_logic();

    //void draw(MotionObject_logic* motion_object) override;

    void update(float delta_time) override;

    // getters
    float get_num_frames();
    Vector2 get_tx_frame_dim();  
    float get_frame();  
    float get_frame_timer();
    float get_clock();

    // sets
    void set_num_frames(float num_frames);
    void set_tx_frame_dim(Vector2 tx_frame_dim);  
    void set_frame(float frame);  
    void set_frame_timer(float frame_timer);
    void set_clock(float clock);
    
private:
    void _update_frame();

    void _update_clock(float delta_time);

    float _num_frames;

    Vector2 _tx_frame_dim;

    float _frame;

    float _frame_timer;

    float _clock;
};

#endif
