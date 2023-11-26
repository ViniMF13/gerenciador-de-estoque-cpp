#include "Item.hpp"
#include "Inventario.hpp"
#include "Interface.hpp"

#include "Include/JSON/json.hpp"

#include <iostream>
#include <string>

// Construtor padrão
Item::Item(const std::string& nome, double valor) {
    try {
        this->nome = nome;
        this->valor = valor;
        this->quantidade = 0;
        this->id = Item::gerarId();
    } catch (const std::exception& e) {
        throw std::invalid_argument("Erro ao construir o Item: " + std::string(e.what()));
    }
}

Item::Item(const std::string& nome, double valor, int quantidade) {
    try {
        this->nome = nome;
        this->valor = valor;
        this->quantidade = quantidade;
    } catch (const std::exception& e) {
        throw std::invalid_argument("Erro ao construir o Item: " + std::string(e.what()));
    }
}

// Construtor para desserialização do Item 
Item::Item(const std::string& jsonString) {
  try {
      nlohmann::json j = nlohmann::json::parse(jsonString);

      // Usando `at` para garantir que a chave exista
      this->id = j.at("id").get<int>();
      this->nome = j.at("nome").get<std::string>();
      this->valor = j.at("valor").get<double>();
      this->quantidade = j.at("quantidade").get<int>();
  } catch (const nlohmann::json::exception& e) {
      throw std::invalid_argument("Erro ao desserializar o Item: " + std::string(e.what()));
  } catch (const std::exception& e) {
      throw std::invalid_argument("Erro ao desserializar o Item: " + std::string(e.what()));
  }
}

std::string Item::toJson() const {
    nlohmann::json j;

    j["id"] = id;
    j["nome"] = nome;
    j["valor"] = valor;
    j["quantidade"] = quantidade;

    return j.dump(); // Converte o JSON para uma string
}

int Item::gerarId() {
    // Inicializa a semente do gerador de números aleatórios com o tempo atual
    std::srand(std::time(0));
    // Gera um número aleatório entre 1 e 10000 
    return std::rand() % 10000 + 1;
}

// Implementação dos métodos getter
int Item::getId() const {
    return id;
}

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

void Item::cadastrarItem(Inventario& inventario){
    try {
        std::string nome = Interface::lerValor<std::string>("Digite o nome do item que deseja cadastrar:");
        
        // Verifica se já existe um item com o mesmo nome no inventário antes de adicionar
        if(inventario.itemExiste(nome)){
            // Se o Item existe
            Interface::exibirMensagem("Erro: O Item já está cadastrado no sistema");
        } else {
            double valor = -1;
            while(valor < 0){ 
                valor = Interface::lerValor<double>("Digite o valor do item");
                if(valor < 0)
                    Interface::exibirMensagem("Valor invalido");
            }
            Item newItem = Item(nome, valor);
            inventario.obterEstoque().insert(std::make_pair(newItem.getId(), newItem));
            Interface::exibirMensagem("O item foi cadastrado no inventário!");
        }
    } catch (const std::exception& e) {
        // Tratar exceções relacionadas à entrada do usuário
        Interface::exibirMensagem("Erro ao cadastrar o item: " + std::string(e.what()));
    }
}

void Item::removerItem(Inventario& inventario){
    try {
        std::string nome = Interface::lerValor<std::string>("Digite o nome do item que deseja remover");

        // Verifica se já existe o item no inventário
        if (inventario.itemExiste(nome)) {
            // Se o Item existe, o remove do inventário
            Item& item = inventario.getItem(nome);
            auto it = inventario.obterEstoque().find(item.getId());
            inventario.obterEstoque().erase(it);
            
            Interface::exibirMensagem("O item foi Removido do inventário!");
        } else {
            Interface::exibirMensagem("Erro: O item não está cadastrado no inventário.");
        }
    } catch (const std::exception& e) {
        // Tratar exceções relacionadas à entrada do usuário
        Interface::exibirMensagem("Erro ao remover o item: " + std::string(e.what()));
    }
}

void Item::atualizarValor(Inventario& inventario){
    try {
        std::string nome = Interface::lerValor<std::string>("Digite o nome do item");

        // Verifica se já existe o item no inventário
        if (inventario.itemExiste(nome)) {
            // Se o Item existe
            double novoValor = Interface::lerValor<double>("Digite o novo valor do item:");
            inventario.getItem(nome).setValor(novoValor);
            Interface::exibirMensagem("O valor do item foi atualizado");
        } else {
            // Se o Item não existe
            Interface::exibirMensagem("O item não está cadastrado no inventário");
        }
    } catch (const std::exception& e) {
        // Tratar exceções relacionadas à entrada do usuário
        Interface::exibirMensagem("Erro ao atualizar o valor do item: " + std::string(e.what()));
    }
}