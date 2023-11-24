#include "Movimentacao.hpp"
#include "Include/json.hpp"

#include <string>
#include <ctime>

Movimentacao::Movimentacao(const std::string& n, std::string& t, int q) : nome(n), tipo(t), quantidade(q) {
    data = std::time(0); // Obtém a data e hora atuais
}

Movimentacao::Movimentacao(const std::string& n, std::string& t, int q, int d){
    this->nome = n;
    this->tipo = t;
    this->quantidade = q;
    this->data = d;
}

Movimentacao::Movimentacao(const std::string& jsonString){
    nlohmann::json j = nlohmann::json::parse(jsonString);

    // Obtém os valores do JSON
    this->nome = j["nome"];
    this->tipo = j["tipo"];
    this->quantidade = j["quantidade"];
    this->data = j["data"];
}

std::string Movimentacao::getNome() const {
    return nome;
}

std::string Movimentacao::getTipo() const {
    return tipo;
}

int Movimentacao::getQuantidade() const {
    return quantidade;
}

std::time_t Movimentacao::getData() const {
    return data;
}

std::string Movimentacao::toJson() const {
    nlohmann::json j;

    j["nome"] = nome;
    j["tipo"] = tipo;
    j["quantidade"] = quantidade;
    j["data"] = data;

    return j.dump(); // Converte o JSON para uma string
}