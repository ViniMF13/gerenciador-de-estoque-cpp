#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Inventario.hpp"  // Certifique-se de incluir o arquivo de cabeçalho correspondente

TEST_CASE("Teste da função itemExiste") {
    Inventario inventario;
    Item item1(1, "Item1", 10, 5.0);
    Item item2(2, "Item2", 20, 8.0);

    inventario.obterEstoque()[1] = item1;
    inventario.obterEstoque()[2] = item2;

    SUBCASE("Item existe") {
        REQUIRE(inventario.itemExiste("Item1") == true);
    }

    SUBCASE("Item não existe") {
        REQUIRE(inventario.itemExiste("Item3") == false);
    }
}

TEST_CASE("Teste da função getItem") {
    Inventario inventario;
    Item item1(1, "Item1", 10, 5.0);
    Item item2(2, "Item2", 20, 8.0);

    inventario.obterEstoque()[1] = item1;
    inventario.obterEstoque()[2] = item2;

    SUBCASE("Item existe") {
        Item& result = inventario.getItem("Item1");
        REQUIRE(result.getId() == 1);
        REQUIRE(result.getNome() == "Item1");
        REQUIRE(result.getQuantidade() == 10);
        REQUIRE(result.getValor() == 5.0);
    }

    SUBCASE("Item não existe") {
        REQUIRE_THROWS_AS(inventario.getItem("Item3"), std::runtime_error);
    }
}

TEST_CASE("Teste da função adicionarItens") {
    Inventario inventario;
    Item item1(1, "Item1", 10, 5.0);

    inventario.obterEstoque()[1] = item1;

    std::string input = "Item1\n5\n";
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf());

    SUBCASE("Adiciona itens ao inventário") {
        inventario.adicionarItens();
        REQUIRE(inventario.getItem("Item1").getQuantidade() == 15);
    }
}

TEST_CASE("Teste da função retirarItens") {
    Inventario inventario;
    Item item1(1, "Item1", 10, 5.0);

    inventario.obterEstoque()[1] = item1;

    std::string input = "Item1\n5\n";
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf());

    SUBCASE("Retira itens do inventário") {
        inventario.retirarItens();
        REQUIRE(inventario.getItem("Item1").getQuantidade() == 5);
    }
}

TEST_CASE("Teste da função adicionarMovimentacao") {
    Inventario inventario;
    Item item1(1, "Item1", 10, 5.0);

    inventario.obterEstoque()[1] = item1;

    SUBCASE("Adiciona movimentação ao histórico") {
        inventario.adicionarMovimentacao("Item1", "entrada", 5);
        const std::vector<Movimentacao>& historico = inventario.obterHistorico();
        REQUIRE(historico.size() == 1);
        REQUIRE(historico[0].getNome() == "Item1");
        REQUIRE(historico[0].getTipo() == "entrada");
        REQUIRE(historico[0].getQuantidade() == 5);
    }
}

TEST_CASE("Teste da função salvarDados e carregarDados") {
    Inventario inventario;
    Item item1(1, "Item1", 10, 5.0);
    inventario.obterEstoque()[1] = item1;

    inventario.adicionarMovimentacao("Item1", "entrada", 5);
    
    inventario.salvarDados("test_inventario.json", "test_historico.json");
    
    Inventario novoInventario;
    novoInventario.carregarDados("test_inventario.json", "test_historico.json");

    const std::map<int, Item>& estoque = novoInventario.obterEstoque();
    const std::vector<Movimentacao>& historico = novoInventario.obterHistorico();

    SUBCASE("Estoque carregado corretamente") {
        REQUIRE(estoque.size() == 1);
        REQUIRE(estoque.at(1).getQuantidade() == 10);
    }

    SUBCASE("Histórico carregado corretamente") {
        REQUIRE(historico.size() == 1);
        REQUIRE(historico[0].getNome() == "Item1");
        REQUIRE(historico[0].getTipo() == "entrada");
        REQUIRE(historico[0].getQuantidade() == 5);
    }
}