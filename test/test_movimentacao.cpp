#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Movimentacao.hpp"  // Certifique-se de incluir o arquivo de cabeçalho correspondente

TEST_CASE("Teste do construtor Movimentacao") {
    SUBCASE("Construtor com valores padrão") {
        Movimentacao mov("Compra", "Entrada", 10);
        REQUIRE(mov.getNome() == "Compra");
        REQUIRE(mov.getTipo() == "Entrada");
        REQUIRE(mov.getQuantidade() == 10);
        REQUIRE(mov.getData() <= std::time(0)); // A data deve ser menor ou igual à data atual
    }

    SUBCASE("Construtor com data fornecida") {
        Movimentacao mov("Venda", "Saída", 5, 1638572394);
        REQUIRE(mov.getNome() == "Venda");
        REQUIRE(mov.getTipo() == "Saída");
        REQUIRE(mov.getQuantidade() == 5);
        REQUIRE(mov.getData() == 1638572394);
    }
}

TEST_CASE("Teste do construtor Movimentacao a partir de JSON") {
    std::string jsonString = R"(
        {
            "nome": "Transferência",
            "tipo": "Saída",
            "quantidade": 3,
            "data": 1638572394
        }
    )";

    Movimentacao mov(jsonString);
    REQUIRE(mov.getNome() == "Transferência");
    REQUIRE(mov.getTipo() == "Saída");
    REQUIRE(mov.getQuantidade() == 3);
    REQUIRE(mov.getData() == 1638572394);
}

TEST_CASE("Teste da função toJson") {
    Movimentacao mov("Pagamento", "Saída", 2, 1638572394);
    std::string expectedJson = R"(
        {
            "nome": "Pagamento",
            "tipo": "Saída",
            "quantidade": 2,
            "data": 1638572394
        }
    )";

    REQUIRE(mov.toJson() == expectedJson);
}