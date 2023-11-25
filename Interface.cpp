// Interface.cpp
#include "Interface.hpp"
#include <chrono>
#include <iostream>
#include <map>

void Interface::exibirMenu() {
    // Implementação do menu
     std::cout << "O que voce deseja faze ?" << std::endl;
        //Item
            std::cout << "1: Cadastrar novo item" << std::endl;
            std::cout << "2: Remover um item" << std::endl;
            std::cout << "3: Atualizar Valor do item" << std::endl;
        //Inventário
            std::cout << "4: Adicionar itens" << std::endl;
            std::cout << "5: Retiradr itens" << std::endl;
            std::cout << "6: Listar itens" << std::endl;
            std::cout << "7: Ver Historico de movimentacao" << std::endl;
        //Historicos
        //  std::cout << ": histórico de entradas" << std::endl;
        //  std::cout << ": Histórico de saidas" << std::endl;
        //Configurações
        //  std::cout << ": Idioma" << std::endl;
        //  std::cout << ": Moeda" << std::endl;
        std::cout << "10: Slavar e Sair" << std::endl;
}

void Interface::exibirMensagem(const std::string& mensagem) {
    std::cout << mensagem << std::endl;
}

void Interface::exibirItens(Inventario& inventario) {
    std::cout << "Itens no inventário: " << std::endl;
    for (auto& par : inventario.obterEstoque()) {
        std::cout << "ID " << par.first << "Nome " << par.second.getNome() << " Valor " << par.second.getValor() << " Quantidade " << par.second.getQuantidade() << std::endl;
    }
}

void Interface::exibirHistorico(const Inventario& inventario) {
    for (const auto& mov : inventario.obterHistorico()) {
         std::cout << "Nome: " << mov.getNome() << "Tipo: " << mov.getTipo() << ", Quantidade: " << mov.getQuantidade() << ", Data: ";

        // Cria uma cópia não constante de mov.getData()
        time_t data = mov.getData();
        // Converte o time_t para struct tm (tempo local)
        std::tm* localTime = std::localtime(&data);

        // Verifica se a conversão foi bem-sucedida
        if (localTime != nullptr) {
            std::cout << std::asctime(localTime);
        } else {
            std::cout << "Erro na conversão de data e hora" << std::endl;
        }
    }
}

void Interface::limparTela() {
    #ifdef _WIN32
        system("cls"); // Comando para limpar tela no Windows
    #else
        system("clear"); // Comando para limpar tela em sistemas Unix
    #endif
}

// Função genérica para ler um valor do usuário
template <typename T>
T Interface::lerValor(const std::string& mensagem) {
    T valor;
    std::cout << mensagem << ": ";
    std::cin >> valor;
    return valor;
}