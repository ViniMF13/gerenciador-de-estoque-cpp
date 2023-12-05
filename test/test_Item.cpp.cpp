#include "Include/doctest.h"
#include "Item.hpp"
#include "Inventario.hpp"

TEST_CASE("Construtor padrão e getters") {
    Item item("Espada", 50.0);
    CHECK(item.getNome() == "Espada");
    CHECK(item.getValor() == 50.0);
    CHECK(item.getQuantidade() == 0);
}

TEST_CASE("Construtor com quantidade e getters") {
    Item item("Poção", 10.0, 3);
    CHECK(item.getNome() == "Poção");
    CHECK(item.getValor() == 10.0);
    CHECK(item.getQuantidade() == 3);
}

TEST_CASE("ToJson e desserialização") {
    Item item("Arco", 30.0, 2);
    std::string jsonString = item.toJson();

    Item itemDesserializado(jsonString);

    CHECK(itemDesserializado.getNome() == "Arco");
    CHECK(itemDesserializado.getValor() == 30.0);
    CHECK(itemDesserializado.getQuantidade() == 2);
}

TEST_CASE("Setters") {
    Item item("Machado", 40.0, 5);
    
    item.setValor(45.0);
    item.setQuantidade(3);

    CHECK(item.getValor() == 45.0);
    CHECK(item.getQuantidade() == 3);
}

TEST_CASE("Cadastrar e Remover Item do Inventario") {
    Inventario inventario;
    
    Item::cadastrarItem(inventario);
    CHECK(inventario.itemExiste("NovoItem"));

    Item::removerItem(inventario);
    CHECK_FALSE(inventario.itemExiste("NovoItem"));
}

TEST_CASE("Atualizar Valor do Item no Inventario") {
    Inventario inventario;

    Item::cadastrarItem(inventario);
    Item::atualizarValor(inventario);
    
    Item& itemAtualizado = inventario.getItem("NovoItem");
    CHECK(itemAtualizado.getValor() > 0.0);
}