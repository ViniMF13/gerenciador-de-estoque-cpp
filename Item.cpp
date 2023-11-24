#include "Item.hpp"
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