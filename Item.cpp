#include "Item.hpp"
#include "Inventario.hpp"
#include "Interface.hpp"

#include "Include/JSON/json.hpp"

#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"


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

        Interface::limparTela();
        std::string nome = Interface::requisitarInfo<std::string>("Digite o nome do item que deseja cadastrar");
        
        // Verifica se já existe um item com o mesmo nome no inventário antes de adicionar
        if(inventario.itemExiste(nome)){
            // Se o Item existe
            std::cout << RED << "";
            Interface::limparTela();
            Interface::exibirMensagem("Erro: O Item ja esta cadastrado no sistema");
            std::cout << RESET << "" ;
        } else {

            double valor = -1;
            while(valor < 0){ 
                valor = Interface::requisitarInfo<double>("Digite o valor do item");
                if(valor < 0){
                    std::cout << RED << "";

                    Interface::exibirMensagem("Valor invalido");
                    std::cout << RESET << "" ;
                }
            }

            Item newItem = Item(nome, valor);
            inventario.obterEstoque().insert(std::make_pair(newItem.getId(), newItem));
            Interface::limparTela();
            std::cout << GREEN << "" ;
            Interface::exibirMensagem("O item foi cadastrado no inventario!");
            std::cout << RESET << "" ;
        }
    } catch (const std::exception& e) {
        // Tratar exceções relacionadas à entrada do usuário
        Interface::exibirMensagem("Erro ao cadastrar o item: " + std::string(e.what()));
    }
}

void Item::removerItem(Inventario& inventario){
    try {

        Interface::limparTela();
        std::string nome = Interface::requisitarInfo<std::string>("Digite o nome do item que deseja remover");


        // Verifica se já existe o item no inventário
        if (inventario.itemExiste(nome)) {
            // Se o Item existe, o remove do inventário
            Item& item = inventario.getItem(nome);
            auto it = inventario.obterEstoque().find(item.getId());
            inventario.obterEstoque().erase(it);
            Interface::limparTela();
            std::cout << GREEN << "" ;
            Interface::exibirMensagem("O item foi removido do inventario!");
            std::cout << RESET << "" ;
        } else {
            Interface::limparTela();
            std::cout << RED << "" ;
            Interface::exibirMensagem("Erro: O item nao esta cadastrado no inventario.");
            std::cout << RESET << "" ;
        }
    } catch (const std::exception& e) {
        // Tratar exceções relacionadas à entrada do usuário
        Interface::exibirMensagem("Erro ao remover o item: " + std::string(e.what()));
    }
}

void Item::atualizarValor(Inventario& inventario){
    try {
        std::string nome = Interface::requisitarInfo<std::string>("Digite o nome do item");

        // Verifica se já existe o item no inventário
        if (inventario.itemExiste(nome)) {
            // Se o Item existe

            double novoValor = -1;
            while(novoValor < 0){

                novoValor= Interface::requisitarInfo<double>("Digite o novo valor do item");
                if(novoValor<0){
                    std::cout << RED << "" ;

                    Interface::exibirMensagem("Valor invalido. ");
                    std::cout << RESET << "" ;
                }
            }

            inventario.getItem(nome).setValor(novoValor);
            Interface::limparTela();
            std::cout << GREEN << "" ;
            Interface::exibirMensagem("O valor do item foi atualizado.");
            std::cout << RESET << "" ;
        } else {
            // Se o Item não existe
            Interface::limparTela();
            std::cout << RED << "" ;
            Interface::exibirMensagem("O item nao esta cadastrado no inventario.");
            std::cout << RESET << "" ;
        }
    } catch (const std::exception& e) {
        // Tratar exceções relacionadas à entrada do usuário
        Interface::exibirMensagem("Erro ao atualizar o valor do item: " + std::string(e.what()));
    }
}