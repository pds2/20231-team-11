
#include "../thirdy_party/doctest.hpp"

#include"../include/Alien.hpp"
#include"../include/Animation.hpp"
#include"../include/Behaviour.hpp"
#include"../include/Game.hpp"
#include"../include/MotionObject.hpp"
#include"../include/Ship.hpp"



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