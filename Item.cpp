#include "Item.hpp"
#include "Inventario.hpp"
#include "Interface.hpp"
#include "Include/json.hpp"

#include <iostream>

// Implementação dos construtores do Item
Item::Item(const std::string& nome, double valor) {
    this->nome = nome;
    this->valor = valor;
    this->quantidade = 0;

// Tratamento de excessões
}

Item::Item(const std::string& nome, double valor, int quantidade) {
    this->nome = nome;
    this->valor = valor;
    this->quantidade = quantidade;

// Tratamento de excessões
}

Item::Item(const std::string& jsonString) {
    nlohmann::json j = nlohmann::json::parse(jsonString);

    // Obtém os valores do JSON
    this->nome = j["nome"];
    this->valor = j["valor"];
    this->quantidade = j["quantidade"];
}

void Item::cadastrarItem(Inventario& inventario){
    std::string nome = Interface::lerValor<std::string>("Digite o nome do item que deseja cadastrar:");
    double valor = Interface::lerValor<double>("Digite o valor do item:");
    
    // Verifica se já existe um item com o mesmo nome no inventário antes de adicionar
    if(inventario.itemExiste(nome)){
      // Se o Item existe------- +++++++++v
      Interface::exibirMensagem("Erro: O Item ja esta cadastrado no sistema");
    } else {
      // Se o Item não existe, cria o item e adiciona ao inventário ------- +++++++++v
      Item newItem = Item(nome, valor);
      inventario.obterEstoque().insert(std::make_pair(newItem.getNome(), newItem));
      Interface::exibirMensagem("O item foi cadastrado no inventario!");
    }
}

void Item::removerItem(Inventario& inventario){
    std::string nome = Interface::lerValor<std::string>("Digite o nome do item que deseja remover");

    // Verifica se já existe o item no inventário
    if (inventario.itemExiste(nome)) {
      // Se o Item existe, o remove do inventário ------- +++++++++v
      inventario.obterEstoque().erase(inventario.obterEstoque().find(nome));
      Interface::exibirMensagem("O item foi Removido do inventario!");
    } else {
      Interface::exibirMensagem("Erro: O item não está cadastrado no inventário.");
    }
}

void Item::atualizarValor(Inventario& inventario){
    std::string nome = Interface::lerValor<std::string>("Digite o nome do item");

    // Verifica se já existe o item no inventário
    if (inventario.itemExiste(nome)) {
      // Se o Item existe,  ------- +++++++++v
       double valor = Interface::lerValor<int>("Digite o novo valor do item:");
       inventario.getItem(nome).setValor(valor);
       Interface::exibirMensagem("O valor do item foi autualizado");

    } else {
      Interface::exibirMensagem("O item não está cadastrado no inventário");
    }
}

// Implementação dos métodos getter
std::string Item::getNome() const {
    return nome;
}

double Item::getValor() const {
    return valor;
}

int Item::getQuantidade() const {
    return quantidade;
}

void Item::setValor(double valor){
     this->valor = valor;
}

void Item::setQuantidade(int quantidade){
     this->quantidade = quantidade;
}

std::string Item::toJson() const {
    nlohmann::json j;

    j["nome"] = nome;
    j["valor"] = valor;
    j["quantidade"] = quantidade;

    return j.dump(); // Converte o JSON para uma string
}