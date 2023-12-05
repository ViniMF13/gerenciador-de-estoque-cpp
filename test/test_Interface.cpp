#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Interface.hpp"  // Certifique-se de incluir o arquivo de cabeçalho correspondente

TEST_CASE("Teste da função solicitarInt") {
    std::istringstream input;

    SUBCASE("Entrada válida") {
        input.str("42\n");
        std::cin.rdbuf(input.rdbuf());
        REQUIRE(Interface::solicitarInt("Mensagem") == 42);
    }

    SUBCASE("Entrada inválida") {
        input.str("texto\n42\n");
        std::cin.rdbuf(input.rdbuf());
        REQUIRE(Interface::solicitarInt("Mensagem") == 42);
    }
}

TEST_CASE("Teste da função solicitarDouble") {
    std::istringstream input;

    SUBCASE("Entrada válida") {
        input.str("3.14\n");
        std::cin.rdbuf(input.rdbuf());
        REQUIRE(Interface::solicitarDouble("Mensagem") == doctest::Approx(3.14));
    }

    SUBCASE("Entrada inválida") {
        input.str("texto\n3.14\n");
        std::cin.rdbuf(input.rdbuf());
        REQUIRE(Interface::solicitarDouble("Mensagem") == doctest::Approx(3.14));
    }
}

TEST_CASE("Teste da função solicitarString") {
    std::istringstream input;

    SUBCASE("Entrada válida") {
        input.str("Teste\n");
        std::cin.rdbuf(input.rdbuf());
        REQUIRE(Interface::solicitarString("Mensagem") == "Teste");
    }

    SUBCASE("Entrada inválida") {
        input.str("\nTeste\n");
        std::cin.rdbuf(input.rdbuf());
        REQUIRE(Interface::solicitarString("Mensagem") == "Teste");
    }
}
