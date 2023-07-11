#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../logic/thirdy_party/doctest.hpp"

#include "../logic/include/Settings_logic.hpp"
#include "../logic/include/Structs_logic.hpp"
#include "../logic/include/Animation_logic.hpp"

#include "../logic/include/MotionObject_logic.hpp"
#include "../logic/include/Alien_logic.hpp"
#include "../logic/include/Ship_logic.hpp"
#include "../logic/include/Behaviour_logic.hpp"
#include "../logic/include/Game_logic.hpp"

// acceleration
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
    
    SUBCASE("2.1Teste do método get_x") {
        CHECK(v1.get_x() == 2.0f);
    }

    SUBCASE("2.2-Teste do método get_y") {
        CHECK(v1.get_y() == 3.0f);
    }

    v1.set_x(10.0f);
    CHECK(v1.get_x() == 10.0f);

    v1.set_y(20.0f);
    CHECK(v1.get_y() == 20.0f);

    v3 = v1.add(v2);

    SUBCASE("2.3-Teste do método add") {
        CHECK(v3.get_x() == 14.0f);
        CHECK(v3.get_y() == 25.0f);
    }

    SUBCASE("2.4-Teste do método length") {
        float length = v1.length();
        CHECK(length == doctest::Approx(22.3606797f));
    }

    SUBCASE("2.5-Teste do método scale") {
        Vector2 v4 = v1.scale(2.0f);
        CHECK(v4.get_x() == 20.0f);
        CHECK(v4.get_y() == 40.0f);
    } 

    SUBCASE("2.6-Teste do método subtract") {
        Vector2 v5 = v1.subtract(v2);
        CHECK(v5.get_x() == 6.0f);
        CHECK(v5.get_y() == 15.0f);
    }

    SUBCASE("2.7-Teste do método normalize") {
        Vector2 v6 = v1.normalize();
        CHECK(v6.get_x() == doctest::Approx(0.4472136f));
        CHECK(v6.get_y() == doctest::Approx(0.8944271f));
    }

    SUBCASE("2.8-Teste do método zero") {
        Vector2 v7 = Vector2::zero();
        CHECK(v7.get_x() == 0.0f);
        CHECK(v7.get_y() == 0.0f);
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

    SUBCASE("3.1-Teste de getters") {
        CHECK(rec1.get_position().get_x() == 0.0f);
        CHECK(rec1.get_position().get_y() == 0.0f);
        CHECK(rec1.get_width() == 5.0f);
        CHECK(rec1.get_height() == 5.0f);
    }

    SUBCASE("3.2-Teste de colisões entre retângulos") {
        CHECK(rec1.CheckCollisionRecs(rec1, rec2) == true);
    }

    SUBCASE("3.3-Teste de não-colisão entre retângulos") {
        CHECK(rec1.CheckCollisionRecs(rec1, rec3) == false);
    }
}

TEST_CASE("04-Teste da classe Texture2D") {
    // Criação de objetos Texture2D
    Texture2D texture1;
    Texture2D texture2;

    texture1.LoadTexture("textura1.png");
    texture2.LoadTexture("textura2.png");

    // Teste do método get_texture()
    CHECK(texture1.get_texture() == "textura1.png");
    CHECK(texture2.get_texture() == "textura2.png");
}

TEST_CASE("05-Teste da classe Animation") {

    SUBCASE("5.1-Animation_logic"){
        Animation_logic animation;

        animation.set_width(200);
        animation.set_height(500);

        CHECK(animation.get_width() == 200.0f);
        CHECK(animation.get_height() == 500.0f);
    }
}

TEST_CASE("06-Teste classe AnimationFPS") {
    AnimationFPS_logic animationFPS;
    Vector2 v(5.0f, 2.0f);

    animationFPS.set_num_frames(10); 
    animationFPS.set_tx_frame_dim(v);
    
    SUBCASE("6.1-mudança do frame 0 para 1 [clock > frame_timer]"){
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

    SUBCASE("6.2-mudança do frame 9 para 0: [clock > frame_timer]"){
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

    SUBCASE("6.3-não há mudança de frame: [clock < frame_timer]"){
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

TEST_CASE("07-Teste da classe MotionObject_logic") {
    // Parâmetros de movimento
    Vector2 position(100.0f, 100.0f);
    Vector2 velocity(1.0f, 1.0f);
    Vector2 acceleration(0.5f, 0.5f);
    Vector2 dimension(50.0f, 50.0f);
    float speed_limit = 10.0f;
    float acceleration_limit = 5.0f;

    MotionObject_logic motionObject(position, velocity, acceleration, dimension, speed_limit, acceleration_limit);

    SUBCASE("7.1-Teste do construtor com parâmetros") {

        // Verifique se os parâmetros foram armazenados corretamente
        CHECK(motionObject.get("position") == position);

        CHECK(motionObject.get("velocity")== velocity);

        CHECK(motionObject.get("acceleration") == acceleration);

        CHECK(motionObject.get("dimension") == dimension);

        // floats
        CHECK(motionObject.get_speed_limit() == speed_limit);
        CHECK(motionObject.get_acceleration_limit() == acceleration_limit);
    }

    SUBCASE("7.2-Teste da função update") {
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

    SUBCASE("7.3-Teste da função add_animation") {
        // Crie uma animação
        Animation_logic* a1 = new Animation_logic();
        Animation_logic* a2 = new Animation_logic();
        Animation_logic* a3 = new Animation_logic();

        a1->set_width(54.25f);
        a1->set_height(76.36f);

        a2->set_width(54.0f);
        a2->set_height(76.0f);

        a3->set_width(50.0f);
        a3->set_height(30.0f);
        
        // Adicione a animação ao objeto
        motionObject.add_animation(a1);
        motionObject.add_animation(a2);
        motionObject.add_animation(a3);
        
        // Verifique se a animação foi adicionada corretamente
        std::vector<Animation_logic*> animations = motionObject.get_animations();

        // da pra verificar desse jeito:
        CHECK(animations.size() == 3);

        CHECK(animations[0] == a1); //  checando endereço
        CHECK(animations[1] == a2); 
        CHECK(animations[2] == a3); 

        CHECK(animations[0]->get_width() == doctest::Approx(54.25f));
        CHECK(animations[0]->get_height() == doctest::Approx(76.36f));

        CHECK(animations[1]->get_width() == doctest::Approx(54.0f));
        CHECK(animations[1]->get_height() == doctest::Approx(76.0f));
        
        CHECK(animations[2]->get_width() == doctest::Approx(50.0f));
        CHECK(animations[2]->get_height() == doctest::Approx(30.0f));

        delete a1; // liberar a memória alocada
        delete a2;
        delete a3;
    }
}

TEST_CASE("08-Teste da classe Alien_logic"){
    // Parâmetros de movimento
    Vector2 position(100.0f, 100.0f);
    Vector2 velocity(1.0f, 1.0f);
    Vector2 acceleration(0.5f, 0.5f);
    Vector2 alien_dimension(50.0f, 50.0f);

    Alien_logic alien1(position, velocity, acceleration, alien_dimension, 1.2f, 1.3f);
    Alien_logic alien2(position, velocity, acceleration, alien_dimension);

    SUBCASE("8.1-Teste do construtor dando speed_limit e acceleration_limit"){
        unsigned expectedScore = 10u;

        CHECK_EQ(alien1.get_score(), expectedScore);

        CHECK(alien1.get("position") == position);
        CHECK(alien1.get("velocity") == velocity);
        CHECK(alien1.get("acceleration") == acceleration);
        CHECK(alien1.get("dimension") == alien_dimension);

        CHECK(alien1.get_speed_limit() == doctest::Approx(1.2f));
        CHECK(alien1.get_acceleration_limit() == doctest::Approx(1.3f));
    }

    SUBCASE("8.2-Teste do construtor sem dar speed_limit e acceleration_limit"){
        CHECK(alien2.get_speed_limit() == doctest::Approx(1.0f));
        CHECK(alien2.get_acceleration_limit() == doctest::Approx(0.5f));
    }

    SUBCASE("8.3-Teste da função set_score"){
        alien1.set_score(25u);
        CHECK_EQ(alien1.get_score(), 25u);
    }
}

TEST_CASE("09-Teste da classe Ship_logic"){
    // Parâmetros de movimento
    Vector2 position(200.0f, 150.0f);
    Vector2 velocity(1.5f, 1.5f);
    Vector2 acceleration(0.7f, 0.7f);
    Vector2 ship_dimension(42.0f, 42.0f);

    Ship_logic ship1(position, velocity, acceleration, ship_dimension);
    Ship_logic ship2(position, velocity, acceleration, ship_dimension, 1.5f, 1.2f);

    SUBCASE("9.1-Teste do construtor com parâmetros dando speed_limit e acceleration_limit"){
        CHECK(ship1.get("position") == position);
        CHECK(ship1.get("velocity") == velocity);
        CHECK(ship1.get("acceleration") == acceleration);
        CHECK(ship1.get("dimension") == ship_dimension);

        CHECK(ship1.get_speed_limit() == doctest::Approx(1.0f));
        CHECK(ship1.get_acceleration_limit() == doctest::Approx(0.5f));

        CHECK(ship1.get_life() == 3);
        CHECK(ship1.get_total_charge() == doctest::Approx(0.2f));
        CHECK(ship1.get_current_charge() == doctest::Approx(0.0f));
    }

    SUBCASE("9.2-Teste do construtor com parâmetros sem dar speed_limit e acceleration_limit"){
        CHECK(ship2.get_speed_limit() == doctest::Approx(1.5f));
        CHECK(ship2.get_acceleration_limit() == doctest::Approx(1.2f));
    }

    SUBCASE("9.3-Teste da função is_charged"){
        CHECK(ship1.is_charged() == false);
    }

    SUBCASE("9.4-Teste da função kill_ship"){
        CHECK(ship1.kill_ship() == 2);
        CHECK(ship1.kill_ship() == 1);
        CHECK(ship1.kill_ship() == 0);

        CHECK_THROWS_AS(ship1.kill_ship(), std::invalid_argument);
        CHECK_THROWS_WITH(
            ship1.kill_ship(),
            "Vida nao pode ser negativa"
        );
    }
}

TEST_CASE("10-Teste da classe Behaviour_logic") {
    // Parâmetros de movimento
    Vector2 position(100.0f, 100.0f);
    Vector2 velocity(1.0f, 1.0f);
    Vector2 acceleration(0.5f, 0.5f);
    Vector2 dimension(50.0f, 50.0f);
    Vector2 ship_dimension(40.0f, 40.0f);
    float speed_limit = 10.0f;
    float acceleration_limit = 5.0f;

    // Mapa de entradas para DefaultShipBehaviour
    std::map<std::string, bool> key_inputs = { {"move-right", false}, {"move-left", false}, {"fire", false}};

    // Objeto cinemático: MotionObject
    MotionObject_logic motion_object(position, velocity, acceleration, dimension, speed_limit, acceleration_limit);
    
    // Comportamentos
    Behaviour_logic behaviour;
    DefaultShipBehaviour_logic default_ship_behaviour(&key_inputs, velocity);

    Ship_logic ship(position, velocity, acceleration, ship_dimension, speed_limit, acceleration_limit);
    KamikazeBehaviour_logic kamikaze(&ship);

    SUBCASE("10.1-Teste da função update de Behaviour_logic"){
        CHECK(motion_object.get("velocity") == velocity);

        behaviour.update(&motion_object);

        CHECK(motion_object.get("velocity") == velocity);
    }

    SUBCASE("10.2-Teste do construtor DefaultShipBehaviour_logic"){
        CHECK(*default_ship_behaviour.get_key_inputs() == key_inputs);
        CHECK(default_ship_behaviour.get_velocity() == velocity);
    }

    SUBCASE("10.3-Teste de DefaultShipBehaviour_logic::update"){
        Vector2 resultado(0.0f, 1.0f);

        CHECK(motion_object.get("velocity") == velocity);
        //std::cout << "1. velocity (x,y): " << motion_object.get("velocity").get_x() << " "<< motion_object.get("velocity").get_y() <<std::endl;

        default_ship_behaviour.update(&motion_object);

        //std::cout << "2. velocity (x,y): " << motion_object.get("velocity").get_x() << " "<< motion_object.get("velocity").get_y() <<std::endl;

        CHECK(motion_object.get("velocity") == resultado);
        //std::cout << "resultado (x,y): " << resultado.get_x() << " "<< resultado.get_y() <<std::endl;
    }

    SUBCASE("10.4-Teste da função update de DefaultShipBehaviour_logic::update"){
        key_inputs = { {"move-right", false}, {"move-left", true}, {"fire", false}};
        
        Vector2 resultado(-1.0f, 1.0f);

        default_ship_behaviour.update(&motion_object);

        CHECK(motion_object.get("velocity") == resultado);
    }

    SUBCASE("10.5-Teste da função update de DefaultShipBehaviour_logic"){
        key_inputs = { {"move-right", true}, {"move-left", true}, {"fire", false}};
        
        Vector2 resultado(0.0f, 1.0f);

        default_ship_behaviour.update(&motion_object);

        CHECK(motion_object.get("velocity") == resultado);
    }

    SUBCASE("10.6-Teste da função update de DefaultShipBehaviour_logic"){
        key_inputs = { {"move-right", true}, {"move-left", false}, {"fire", false}};
        
        Vector2 resultado(1.0f, 1.0f);

        default_ship_behaviour.update(&motion_object);

        CHECK(motion_object.get("velocity") == resultado);
    }

    SUBCASE("10.7-Teste do construtor de KamikazeBehaviour_logic"){
        CHECK(kamikaze.get_max_speed() == doctest::Approx(20.0f));
        CHECK(kamikaze.get_acceleration_factor() == doctest::Approx(1.02f));
        CHECK(kamikaze.get_threshold_speed() == doctest::Approx(20.0f * 0.34f));
        CHECK(kamikaze.get_target_object() == &ship);
    }
}

TEST_CASE("11-Teste de KamikazeBehaviour_logic::update") {
    Vector2 dimension = {90.0f, 90.0f};
    Ship_logic* ship = new Ship_logic(Vector2 {600.0f, 900.0f - dimension.get_y()/2.0f},  Vector2 {10.0f, 0.0f}, Vector2 {0.0f, 0.0f}, dimension);
    Alien_logic* alien = new Alien_logic(Vector2 {50.0f, 30.0f}, Vector2 {0.0f, 0.0f}, Vector2 {0.01f, 0.0f}, Vector2 {80.0f, 80.0f});

    // Comportamento kamikaze com target: _ship
    Behaviour_logic* kamikaze_behaviour = new KamikazeBehaviour_logic(ship);    

    SUBCASE("11.1-Teste de KamikazeBehaviour_logic::update"){
        // {600, 900} - {50, 30} = {550, 870}
        // normalizando {550, 870} obtemos {0.53435848, 0.84525796}
        // norma da aceleracao de alien: {0.01}
        // escalando {0.53435848, 0.84525796}  a um fator 0.01 obtemos {0.0053435848, 0.0084525796}
        // velocity_length = 58.3 
        kamikaze_behaviour->update(alien);

        CHECK(alien->get("velocity").get_x() == doctest::Approx(0.005547));
        CHECK(alien->get("velocity").get_y() == doctest::Approx(0.0083205));
    }

    delete ship;
    delete alien;
    delete kamikaze_behaviour;
}

TEST_CASE("12-Teste da classe Game_logic"){
    SUBCASE("12.1-Construtor"){
        // Teste dos atributos iniciais
        Game_logic game1;

        CHECK(game1.get_behaviour("kamikaze-to-ship") == nullptr);
        CHECK(game1.get_animation("alien") == nullptr);
        CHECK(game1.get_inputs("move-right") == false);
        CHECK(game1.get_inputs("move-left") == false);
        CHECK(game1.get_inputs("fire") == false);
        CHECK(game1.get_ship() == nullptr);
        CHECK(game1.get_bullets().empty());
        CHECK(game1.get_aliens().empty());
        CHECK(game1.get_score() == 0u);
        CHECK(game1.get_game_status() == false);
    }

    SUBCASE("12.2-_load_graphics") {
        Game_logic game2;
        game2._load_graphics();

        // Verifica se as texturas foram carregadas corretamente
        CHECK(game2.get_textures().count("background") == 1);
        CHECK(game2.get_textures().count("menu") == 1);
        CHECK(game2.get_textures().count("explosion") == 1);
        CHECK(game2.get_textures().count("power-up") == 1);
        CHECK(game2.get_textures().count("ship") == 1);
        CHECK(game2.get_textures().count("alien") == 1);
        CHECK(game2.get_textures().count("bullet") == 1);
    }

    SUBCASE("12.3-_load_behaviours") {
        Game_logic game3;
        game3._load_behaviours();

        // Verifica se os comportamentos foram carregados corretamente
        CHECK(game3.get_behaviour("default") != nullptr);
        CHECK(game3.get_behaviour("default-ship") != nullptr);
    }
}

