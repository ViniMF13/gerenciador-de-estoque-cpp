// Interface.cpp
#include "../Include/Interface.hpp"

#include <chrono>
#include <type_traits>
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"


void Interface::exibirMenu() {
    // Implementação do menu
    std::cout << YELLOW << " =================================== " << std::endl;
        //Item
    std::cout << "|             |Item|                |" << std::endl;
    std::cout << "| 1 - Cadastrar                     |" << std::endl;
    std::cout << "| 2 - Remover                       |" << std::endl;
    std::cout << "| 3 - Atualizar Valor               |" << std::endl;
    std::cout << "|-----------------------------------| " << std::endl;
         //Inventário
    std::cout << "|           |Inventario|            |" << std::endl;
    std::cout << "| 4 - Adicionar itens               |" << std::endl;
    std::cout << "| 5 - Retirar itens                 |" << std::endl;
    std::cout << "| 6 - Listar itens                  |" << std::endl;
    std::cout << "| 7 - Valor total                   |" << std::endl;
    std::cout << "| 8 - Historico de movimentacao     |" << std::endl;
    std::cout << "| 9 - Salvar e Sair                 |" << std::endl;
    std::cout << " =================================== " << RESET << std::endl;
    std::cout << std::endl;

}

void Interface::exibirMensagem(const std::string& mensagem) {
    std::cout << mensagem << std::endl;
}

void Interface::exibirItens(Inventario& inventario) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Itens no inventario: \n" << std::endl;
    std::cout << BLUE << "ID" << "\t\t" << "Nome" << "\t\t" << "Valor" << "\t\t" << "Unidades" << std::endl << RESET; 
    for (auto& par : inventario.obterEstoque()) {
        std::cout << par.first << "\t\t" << par.second.getNome() << "\t\t" << par.second.getValor() << "\t\t" << par.second.getQuantidade() << std::endl;
    }

    Interface::exibirMensagem("\nPressione ENTER para fechar a lista. ");
            getchar();
            getchar();
            Interface::limparTela();
}

void Interface::exibirHistorico(const Inventario& inventario) {
    std::cout << BLUE << "Nome \t\t Tipo \t\t Quantidade \t\t Data" <<  RESET << std::endl;
    for (const auto& mov : inventario.obterHistorico()) {
        std::cout << mov.getNome() << " \t\t" << mov.getTipo() << " \t\t" << mov.getQuantidade() << " \t\t";

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

    Interface::exibirMensagem("\nPressione ENTER para fechar o Historico. ");
            getchar();
            getchar();
            Interface::limparTela();
}

void Interface::verValorTotal(const Inventario& inventario){

    double total = inventario.calcularValorTotal();
    std::cout << YELLOW << std::endl;
    std::cout << "        Valor total :" << GREEN << " R$ " << total  << YELLOW << "      "<< std::endl;
    std::cout << RESET << std::endl;
    Interface::exibirMensagem("\nPressione ENTER para voltar ao menu. ");
    getchar();
    getchar();
    Interface::limparTela();
}

void Interface::limparTela() {
    #ifdef _WIN32
        system("cls"); // Comando para limpar tela no Windows
    #else
        system("clear"); // Comando para limpar tela em sistemas Unix
    #endif
}

int Interface::solicitarInt(const std::string& mensagem) {
    int quantidade;
    std::cout << mensagem << ": ";

    while (true) {
        if (std::cin >> quantidade && std::cin.peek() == '\n') {
            // A entrada é um número inteiro e não contém caracteres adicionais
            break;
        } else {
            std::cin.clear(); // Limpa o estado de erro
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora o restante da linha inválida
            std::cout << RED << "Entrada invalida. Digite um número inteiro: " << RESET;
        }
    }

    return quantidade;
}

double Interface::solicitarDouble(const std::string& mensagem) {
    double valor;

    std::cout << mensagem << ": ";

    while (true) {
        if (std::cin >> valor && std::cin.peek() == '\n') {
            // A entrada é um número double e não contém caracteres adicionais
            break;
        } else {
            std::cin.clear(); // Limpa o estado de erro
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora o restante da linha inválida
            std::cout << RED << "Entrada invalida. Digite um número decimal: " << RESET;
        }
    }

    // Modifica o valor para ter duas casas decimais se for um número inteiro
    if (std::floor(valor) == valor) {
        valor = std::floor(valor * 100) / 100; // Converte para dois decimais
    }

    return valor;
}

std::string Interface::solicitarString(const std::string& mensagem) {
    std::string nome;

    std::cout << mensagem << ": ";

    while (true) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::getline(std::cin, nome);

        // Verifica se a entrada não está vazia
        if (!nome.empty()) {
            break;
        } else {
            std::cout << RED << "Entrada invalida. Tente novamente: " << RESET;
        }
    }

    return nome;
}
