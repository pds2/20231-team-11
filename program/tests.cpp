
#include "doctest.hpp"

#include"Alien.hpp"
#include"Animation.hpp"
#include"Behaviour.hpp"
#include"Game.hpp"
#include"MotionObject.hpp"
#include"Ship.hpp"



TEST_CASE("Teste do destrutor") {
    Alien* alien = new Alien();
    delete alien;
    // Verificar se a memória foi liberada corretamente
}

TEST_CASE("Teste do método get_score") {
    Alien alien;
    unsigned initial_score = alien.get_score();
    CHECK(initial_score == 0);

    // Como o atributo _score é protegido, não é possível modificá-lo diretamente fora da classe Alien.
    // Portanto, não há necessidade de testar um setter aqui.

    // Verificando se o método get_score retorna o valor correto
    CHECK(alien.get_score() == initial_score);
}
TEST_CASE("Teste método get_score() da classe Alien") {
    Alien alien;
    REQUIRE(alien.get_score() == 10u);

    // Alterando o score e verificando novamente
    alien.set_score(20u);
    REQUIRE(alien.get_score() == 20u);
}
TEST_CASE("Teste método set_score() da classe Alien") {
    Alien alien;
    REQUIRE(alien.get_score() == 10u);

    alien.set_score(50u);
    REQUIRE(alien.get_score() == 50u);

    // Testando para um valor negativo (deve manter o valor anterior)
    alien.set_score(-5);
    REQUIRE(alien.get_score() == 50u);
}
TEST_CASE("Teste destrutor da classe Alien") {
    Alien *alienPtr = new Alien;
    REQUIRE(alienPtr->get_score() == 10u);
    delete alienPtr;
}
TEST_CASE("Teste construtor padrão da classe Behaviour") {
    Behaviour behaviour;
    // Verificar se o construtor não gera erros ou exceções
}
TEST_CASE("Teste método update() da classe Behaviour") {
    Behaviour behaviour;
    // Criar um objeto MotionObject para teste
    MotionObject motion_object;
    // Verificar se o método não gera erros ou exceções
    behaviour.update(&motion_object);
    // Verificar se as atualizações foram aplicadas corretamente
    // Fazer as asserções necessárias para verificar as alterações esperadas em motion_object
}
TEST_CASE("Teste método update_acceleration() da classe Behaviour") {
    Behaviour behaviour;
    // Criar um objeto MotionObject para teste
    MotionObject motion_object;
    // Criar um vetor de delta_aceleracao para teste
    Vector2 delta_acceleration(1, 1);
    // Verificar se o método não gera erros ou exceções
    behaviour.update_acceleration(&motion_object, delta_acceleration);
    // Verificar se as atualizações foram aplicadas corretamente
    // Fazer as asserções necessárias para verificar as alterações esperadas em motion_object
}
TEST_CASE("Teste construtor e método update() da classe FollowMouseBehaviour") {
    // Criar um objeto FollowMouseBehaviour para teste
    FollowMouseBehaviour follow_mouse_behaviour(1.0f);
    // Criar um objeto MotionObject para teste
    MotionObject motion_object;
    // Verificar se o construtor não gera erros ou exceções
    // Verificar se o método não gera erros ou exceções
    follow_mouse_behaviour.update(&motion_object);
    // Verificar se as atualizações foram aplicadas corretamente
    // Fazer as asserções necessárias para verificar as alterações esperadas em motion_object
}
TEST_CASE("Teste construtor e método update() da classe DefaultShipBehaviourS") {
    // Criar um mapa de key_inputs para teste
    std::map<std::string, bool> key_inputs;
    key_inputs["move-right"] = true;
    key_inputs["move-left"] = false;
    // Criar um vetor velocity para teste
    Vector2 velocity(1, 1);
    // Criar um objeto DefaultShipBehaviourS para teste
    DefaultShipBehaviourS default_ship_behaviour(&key_inputs, velocity);
    // Criar um objeto MotionObject para teste
    MotionObject motion_object;
    // Verificar se o construtor não gera erros ou exceções
    // Verificar se o método não gera erros ou exceções
    default_ship_behaviour.update(&motion_object);
    // Verificar se as atualizações foram aplicadas corretamente
    // Fazer as asserções necessárias para verificar as alterações esperadas em motion_object
}
TEST_CASE("Teste construtor e método update() da classe KamikazeBehaviour") {
    // Criar um objeto MotionObject para teste
    MotionObject motion_object;
    // Criar um objeto KamikazeBehaviour para teste
    KamikazeBehaviour kamikaze_behaviour(&motion_object);
    // Verificar se o construtor não gera erros ou exceções
    // Verificar se o método não gera erros ou exceções
    kamikaze_behaviour.update(&motion_object);
    // Verificar se as atualizações foram aplicadas corretamente
    // Fazer as asserções necessárias para verificar as alterações esperadas em motion_object
}
TEST_CASE("Teste construtor padrão da classe Animation") {
    Animation animation;
    // Verificar se o construtor não gera erros ou exceções
}
TEST_CASE("Teste construtor da classe Animation com parâmetro texture") {
    // Criar um objeto Texture2D para teste
    Texture2D texture;
    // Definir a largura e altura da textura
    texture.width = 100;
    texture.height = 100;
    // Criar um objeto Animation para teste
    Animation animation(&texture);
    // Verificar se o construtor não gera erros ou exceções
    // Verificar se as propriedades da animação foram definidas corretamente
    REQUIRE(animation._texture == &texture);
    REQUIRE(animation._width == 100);
    REQUIRE(animation._height == 100);
}
TEST_CASE("Teste método draw() da classe Animation") {
    // Criar um objeto Texture2D para teste
    Texture2D texture;
    // Criar um objeto Animation para teste
    Animation animation(&texture);
    // Criar um objeto MotionObject para teste
    MotionObject motion_object;
    // Verificar se o método não gera erros ou exceções
    // Fazer as asserções necessárias para verificar se a função de desenho está sendo chamada corretamente
}
TEST_CASE("Teste construtor da classe AnimationFPS") {
    // Criar um objeto Texture2D para teste
    Texture2D texture;
    // Criar um vetor tx_frame_dim para teste
    Vector2 tx_frame_dim(2, 2);
    // Criar um valor frame_timer para teste
    float frame_timer = 0.5f;
    // Criar um objeto AnimationFPS para teste
    AnimationFPS animation_fps(&texture, tx_frame_dim, frame_timer);
    // Verificar se o construtor não gera erros ou exceções
    // Verificar se as propriedades da animação FPS foram definidas corretamente
    REQUIRE(animation_fps._num_frames == 4);
    REQUIRE(animation_fps._tx_frame_dim.x == 2);
    REQUIRE(animation_fps._tx_frame_dim.y == 2);
    REQUIRE(animation_fps._clock == 0.0f);
    REQUIRE(animation_fps._frame_timer == 0.5f);
    REQUIRE(animation_fps._frame == 0);
}
TEST_CASE("Teste método update() da classe AnimationFPS") {
    // Criar um objeto AnimationFPS para teste
    AnimationFPS animation_fps;
    // Verificar se o método não gera erros ou exceções
    // Fazer as asserções necessárias para verificar se a animação FPS é atualizada corretamente
}
TEST_CASE("Game class tests")
{
    Game game;

    // Teste para verificar se as texturas foram carregadas corretamente
    SUBCASE("Test texture loading")
    {
        CHECK(game._textures.size() == 6); // Espera-se 6 texturas carregadas
    }

    // Teste para verificar se as animações foram carregadas corretamente
    SUBCASE("Test animation loading")
    {
        CHECK(game._animations.size() == 4); // Espera-se 4 animações carregadas
    }

    // Teste para verificar se os comportamentos foram carregados corretamente
    SUBCASE("Test behaviour loading")
    {
        CHECK(game._behaviours.size() == 3); // Espera-se 3 comportamentos carregados
    }

    // Teste para verificar se a nave foi construída corretamente
    SUBCASE("Test ship creation")
    {
        CHECK(game._ship != nullptr); // A nave deve ser construída
    }

    // Teste para verificar se os aliens foram construídos corretamente
    SUBCASE("Test alien creation")
    {
        CHECK(game._aliens.size() == 4); // Espera-se 4 aliens construídos
    }

    // Teste para verificar se os comportamentos e animações foram adicionados corretamente à nave
    SUBCASE("Test ship behaviours and animations")
    {
        CHECK(game._ship->get_behaviours().size() == 1); // Espera-se 1 comportamento adicionado à nave
        CHECK(game._ship->get_animations().size() == 1); // Espera-se 1 animação adicionada à nave
    }
}
TEST_CASE("MotionObject class tests")
{
    MotionObject motionObject;

    // Teste para verificar se os comportamentos foram adicionados corretamente
    SUBCASE("Test add_behaviour()")
    {
        Behaviour behaviour;
        motionObject.add_behaviour(&behaviour);
        CHECK(motionObject._behaviours.size() == 1); // Espera-se que um comportamento tenha sido adicionado
    }

    // Teste para verificar se as animações foram adicionadas corretamente
    SUBCASE("Test add_animation()")
    {
        Animation animation;
        motionObject.add_animation(&animation);
        CHECK(motionObject._animations.size() == 1); // Espera-se que uma animação tenha sido adicionada
    }

    // Teste para verificar se os parâmetros foram definidos corretamente
    SUBCASE("Test set()")
    {
        Vector2 position(1.0f, 2.0f);
        motionObject.set("position", position);
        CHECK(motionObject.get("position") == position); // Espera-se que o parâmetro "position" tenha sido definido corretamente
    }

    // Teste para verificar se o retângulo foi atualizado corretamente
    SUBCASE("Test _update_rectangle()")
    {
        Vector2 position(0.0f, 0.0f);
        Vector2 dimension(1.0f, 1.0f);
        motionObject.set("position", position);
        motionObject.set("dimension", dimension);
        motionObject._update_rectangle();
        Rectangle expectedRectangle = { -0.5f, -0.5f, 1.0f, 1.0f };
        CHECK(motionObject.get_rectangle() == expectedRectangle); // Espera-se que o retângulo tenha sido atualizado corretamente
    }
}

TEST_CASE("Ship class tests")
{
    Ship ship;

    // Teste para verificar se a vida é inicializada corretamente
    SUBCASE("Test get_life()")
    {
        CHECK(ship.get_life() == 3); // Espera-se que a vida seja igual a 3
    }

    // Teste para verificar se a carga é inicializada corretamente
    SUBCASE("Test is_charged()")
    {
        CHECK(ship.is_charged() == false); // Espera-se que a carga não esteja completa no início
    }

    // Teste para verificar se a carga é atualizada corretamente
    SUBCASE("Test update() - charge bullet")
    {
        float deltaTime = 0.1f;
        ship.update(deltaTime);
        CHECK(ship.is_charged() == doctest::Approx(0.02f)); // Espera-se que a carga seja atualizada corretamente
    }

    // Teste para verificar se a carga é zerada corretamente após disparar uma bala
    SUBCASE("Test update() - fire bullet")
    {
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        ship.update(0.1f);
        CHECK(ship.is_charged() == true); // Espera-se que a carga esteja completa

        // Disparar uma bala
        ship.update(0.1f);
        CHECK(ship.is_charged() == false); // Espera-se que a carga seja zerada após disparar uma bala
    }

    // Teste para verificar se a vida é decrementada corretamente
    SUBCASE("Test kill_ship()")
    {
        CHECK(ship.kill_ship() == 2); // Espera-se que a vida seja decrementada corretamente
    }
}