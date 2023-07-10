#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../logic/thirdy_party/doctest.hpp"

#include "../logic/include/Settings_logic.hpp"
#include "../logic/include/Structs_logic.hpp"
#include "../logic/include/Animation_logic.hpp"

#include "../logic/include/MotionObject_logic.hpp"

#include <stdexcept>

TEST_CASE("01-Teste de Settings_logic") {
    CHECK_EQ(Config::SCREEN_WIDTH, 1200);

    CHECK_EQ(Config::SCREEN_HEIGHT, 900);

    CHECK_EQ(Config::SCREEN_TITLE, "Invaders");

    CHECK_EQ(Config::FPS, 60);

    CHECK_EQ(Config::BACKGROUND_TEXTURE, "images/alexandria/mapa.png");

    CHECK_EQ(Config::MENU_TEXTURE, "images/space.png");

    CHECK_EQ(Config::SHIP_TEXTURE, "images/alexandria/ship_grid.png");

    CHECK_EQ(Config::ALIEN_TEXTURE, "images/alexandria/alien_grid.png");

    CHECK_EQ(Config::BULLET_TEXTURE, "images/alexandria/bullet_grid.png");

    CHECK_EQ(Config::EXPLOSION_TEXTURE, "images/explosion.png");

    CHECK_EQ(Config::POWERUP_TEXTURE, "images/power-up.png");

    CHECK_EQ(Config::SCORE_FONT_SIZE, 70);

    CHECK_EQ(Config::SCORE_FONT_COLOR, Cores::BLACK);

    CHECK_EQ(Config::GAME_FONT, "default");
}

TEST_CASE("02-Teste da classe Vector2") {
    Vector2 v1(2.0f, 3.0f);
    Vector2 v2(4.0f, 5.0f);
    Vector2 v3;
    
    SUBCASE("Teste do método get_x") {
        CHECK(v1.get_x() == 2.0f);
    }

    SUBCASE("Teste do método get_y") {
        CHECK(v1.get_y() == 3.0f);
    }

    v1.set_x(10.0f);
    CHECK(v1.get_x() == 10.0f);

    v1.set_y(20.0f);
    CHECK(v1.get_y() == 20.0f);

    v3 = v1.add(v2);

    SUBCASE("Teste do método add") {
        CHECK(v3.get_x() == 14.0f);
        CHECK(v3.get_y() == 25.0f);
    }

    SUBCASE("Teste do método length") {
        float length = v1.length();
        CHECK(length == doctest::Approx(22.3606797f));
    }

    SUBCASE("Teste do método scale") {
        Vector2 v4 = v1.scale(2.0f);
        CHECK(v4.get_x() == 20.0f);
        CHECK(v4.get_y() == 40.0f);
    } 

    SUBCASE("Teste do método subtract") {
        Vector2 v5 = v1.subtract(v2);
        CHECK(v5.get_x() == 6.0f);
        CHECK(v5.get_y() == 15.0f);
    }

    SUBCASE("Teste do método normalize") {
        Vector2 v6 = v1.normalize();
        CHECK(v6.get_x() == doctest::Approx(0.4472136f));
        CHECK(v6.get_y() == doctest::Approx(0.8944271f));
    }

    SUBCASE("Teste do método zero") {
        Vector2 v7 = Vector2::zero();
        CHECK(v7.get_x() == 0.0f);
        CHECK(v7.get_y() == 0.0f);
    }   

    SUBCASE("2.2-Posição negativa negativo") {
        CHECK_THROWS_AS(Vector2 v1(-50.0f, -100.0f), std::invalid_argument);
        CHECK_THROWS_WITH(
            Vector2 v1(-50.0f, -100.0f),
            "A posicao nao pode ser negativa"
        );
    }
}

TEST_CASE("03-Teste da classe Retangulo") {
    // Cria dois retângulos
    Vector2 position1(0.0f, 0.0f);
    float width1 = 5.0f;
    float height1 = 5.0f;
    Retangulo rec1(position1, width1, height1);

    Vector2 position2(4.0f, 4.0f);
    float width2 = 4.0f;
    float height2 = 4.0f;
    Retangulo rec2(position2, width2, height2);

    Vector2 position3(40.0f, 40.0f);
    float width3 = 4.0f;
    float height3 = 4.0f;
    Retangulo rec3(position3, width3, height3);

    SUBCASE("Teste de getters") {
        CHECK(rec1.get_position().get_x() == 0.0f);
        CHECK(rec1.get_position().get_y() == 0.0f);
        CHECK(rec1.get_width() == 5.0f);
        CHECK(rec1.get_height() == 5.0f);
    }

    SUBCASE("Teste de colisões entre retângulos") {
        CHECK(rec1.CheckCollisionRecs(rec1, rec2) == true);
    }

    SUBCASE("Teste de não-colisão entre retângulos") {
        CHECK(rec1.CheckCollisionRecs(rec1, rec3) == false);
    }
}

TEST_CASE("04-Teste da classe Animation") {

    SUBCASE("4.1-Animation_logic"){
        Animation_logic animation;

        animation.set_width(200);
        animation.set_height(500);

        CHECK(animation.get_width() == 200.0f);
        CHECK(animation.get_height() == 500.0f);
    }
}

TEST_CASE("05-Teste classe AnimationFPS") {
    AnimationFPS_logic animationFPS;
    Vector2 v(5.0f, 2.0f);

    animationFPS.set_num_frames(10); 
    animationFPS.set_tx_frame_dim(v);
    
    SUBCASE("5.1-mudança do frame 0 para 1 [clock > frame_timer]"){
        // set frame para zero
        animationFPS.set_frame(0);
        // set tempo de mudanca de frame para 0.2s
        animationFPS.set_frame_timer(0.2);
        // inicializo o relogio como zero
        animationFPS.set_clock(0);

        // altera o frame
        animationFPS.update(0.5);

        // clock é maior que delta_frame_timer: altera-se o frame
        // relógio retonar a zero
        CHECK(animationFPS.get_clock() == 0.0f);
        // frame seguinte ao zero
        CHECK(animationFPS.get_frame() == 1.0f);

    }

    SUBCASE("5.2-mudança do frame 9 para 0: [clock > frame_timer]"){
        // set frame para zero
        animationFPS.set_frame(9);
        // set tempo de mudanca de frame para 0.2s
        animationFPS.set_frame_timer(0.2);
        // inicializo o relogio como zero
        animationFPS.set_clock(0);

        // altera o frame
        animationFPS.update(0.5);

        // clock é maior que delta_frame_timer: altera-se o frame
        // relógio retona a zero
        CHECK(animationFPS.get_clock() == 0.0f);
        // frame retorna a zero
        CHECK(animationFPS.get_frame() == 0.0f);
    }

    SUBCASE("5.3-não há mudança de frame: [clock < frame_timer]"){
        // set frame para zero
        animationFPS.set_frame(5);
        // set tempo de mudanca de frame para 0.2s
        animationFPS.set_frame_timer(2.0);
        // inicializo o relogio como zero
        animationFPS.set_clock(0.5);

        // altera o frame
        animationFPS.update(0.1);

        // clock é maior que delta_frame_timer: altera-se o frame
        // relógio retona a zero
        CHECK(animationFPS.get_clock() == 0.6f);
        // frame retorna a zero
        CHECK(animationFPS.get_frame() == 5.0f);
    }
}

TEST_CASE("Teste da classe MotionObject_logic") {

    // Crie um objeto MotionObject_logic com valores iniciais
    Vector2 position(100.0f, 100.0f);
    Vector2 velocity(1.0f, 1.0f);
    Vector2 acceleration(0.5f, 0.5f);
    Vector2 dimension(50.0f, 50.0f);
    float speed_limit = 10.0f;
    float acceleration_limit = 5.0f;

    MotionObject_logic motionObject(position, velocity, acceleration, dimension, speed_limit, acceleration_limit);

    SUBCASE("Teste do construtor com parâmetros") {

        // Verifique se os parâmetros foram armazenados corretamente
        CHECK(motionObject.get("position") == position);

        CHECK(motionObject.get("velocity")== velocity);

        CHECK(motionObject.get("acceleration") == acceleration);

        CHECK(motionObject.get("dimension") == dimension);

        // floats
        CHECK(motionObject.get_speed_limit() == speed_limit);
        CHECK(motionObject.get_acceleration_limit() == acceleration_limit);
    }

    SUBCASE("Teste da função update") {
        // Chame a função update
        motionObject.update();
        // Verifique se a posição do objeto foi atualizada corretamente
        Vector2 updatedPosition = motionObject.get("position");

        CHECK(motionObject.get("position").get_x() == doctest::Approx(101.0f));
        CHECK(motionObject.get("position").get_y() == doctest::Approx(101.0f));
        CHECK(motionObject.get_rectangle().get_position().get_x() == doctest::Approx(76.0f));
        CHECK(motionObject.get_rectangle().get_position().get_y() == doctest::Approx(76.0f));
        CHECK(motionObject.get_rectangle().get_width() == doctest::Approx(50.0f));
        CHECK(motionObject.get_rectangle().get_height() == doctest::Approx(50.0f));

        // compara retangulos
        CHECK(motionObject.get_rectangle() == Retangulo(Vector2 (76.0f, 76.0f), 50.0f, 50.0f));
    }

    // SUBCASE("Teste da função add_animation") {
    //     // Crie uma animação
    //     Animation_logic a1, a2, a3;

    //     // Adicione a animação ao objeto
    //     motionObject.add_animation(&animation);

    //     // Verifique se a animação foi adicionada corretamente
    //     std::vector<Animation_logic*> animations = motionObject.get_animations();
    //     CHECK(animations.size() == 1);
    //     CHECK(animations[0] == &animation);

    //     // TODO: Adicione mais testes relevantes para a função add_animation
    // }
}