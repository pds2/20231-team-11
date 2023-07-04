#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "Game.hpp"
#include "MotionObject.hpp"

class Game;
class MotionObject;

/**
 * @brief Classe base para animações.
 */
class Animation {
public:
    /**
     * @brief Construtor padrão da animação.
     */
    Animation();

    /**
     * @brief Construtor da animação com textura.
     * @param texture Ponteiro para a textura da animação.
     */
    Animation(Texture2D* texture);

    /**
     * @brief Destrutor da animação.
     */
    ~Animation();

    /**
     * @brief Desenha a animação do objeto em movimento.
     * @param motion_object Ponteiro para o objeto em movimento.
     */
    virtual void draw(MotionObject* motion_object);

    /**
     * @brief Atualiza a animação.
     * @param delta_time Tempo desde o último quadro.
     */
    virtual void update(float delta_time);

protected:
    /**
     * @brief Ponteiro para a textura da animação.
     */
    Texture2D* _texture;

    /**
     * @brief Dimensões da textura em pixels.
     */
    float _width;
    float _height;
};

/**
 * @brief Animação com taxa de quadros por segundo.
 */
class AnimationFPS : public Animation {
public:

    // Construtor Padrão da Animação
    AnimationFPS();
    /**
     * @brief Construtor da animação com taxa de quadros por segundo.
     * @param texture Ponteiro para a textura da animação.
     * @param tx_frames_dim Dimensões dos quadros na textura.
     * @param frame_timer Tempo entre a mudança de quadros.
     */
    AnimationFPS(Texture2D* texture, Vector2 tx_frames_dim, float frame_timer);

    /**
     * @brief Destrutor da animação com taxa de quadros por segundo.
     */
    ~AnimationFPS();

    /**
     * @brief Desenha a animação com taxa de quadros por segundo do objeto em movimento.
     * @param motion_object Ponteiro para o objeto em movimento.
     */
    void draw(MotionObject* motion_object) override;

    /**
     * @brief Atualiza a animação com taxa de quadros por segundo.
     * @param delta_time Tempo desde o último quadro.
     */
    void update(float delta_time) override;

private:
    /**
     * @brief Atualiza o quadro a ser desenhado.
     */
    void _update_frame();

    /**
     * @brief Atualiza o tempo da animação.
     * @param delta_time Tempo desde o último quadro.
     */
    void _update_clock(float delta_time);

    /**
     * @brief Número total de quadros na textura.
     */
    float _num_frames;

    /**
     * @brief Dimensões dos quadros na textura.
     */
    Vector2 _tx_frame_dim;

    /**
     * @brief Quadro atual.
     */
    float _frame;

    /**
     * @brief Tempo entre a mudança de quadros.
     */
    float _frame_timer;

    /**
     * @brief Armazena o tempo atual em segundos.
     */
    float _clock;
};

#endif
