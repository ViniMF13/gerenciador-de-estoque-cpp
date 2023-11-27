// Interface.cpp
#include "Interface.hpp"
#include <chrono>
#include <type_traits>
#include <iostream>
#include <map>

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
    std::cout << "|             | Itens |             |" << std::endl;
    std::cout << "| 1 - Cadastrar                     |" << std::endl;
    std::cout << "| 2 - Remover                       |" << std::endl;
    std::cout << "| 3 - Atualizar Valor               |" << std::endl;
    std::cout << " =================================== " << std::endl;
         //Inventário
    std::cout << "|           | Iventario |           |" << std::endl;
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
    std::cout << BLUE << "NOME \t\t TIPO \t\t QUANTIDADE \t\t DATA" <<  RESET << std::endl;
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

std::string Interface::lerNome(const std::string& mensagem) {
    std::string nome;

    // Imprime o prompt
    std::cout << mensagem << ": ";

    // Lê toda a linha, incluindo espaços
    std::getline(std::cin, nome);
    // Verifica se a entrada está vazia
    while (nome.empty()) {
        std::cout << "Entrada inválida. Tente novamente: ";
        std::getline(std::cin, nome);
    }

    return nome;
}

// Função genérica para ler um valor do usuário
template <typename T>
T Interface::requisitarInfo(const std::string& mensagem) {

    T valor;
  
    do {
            std::cout << mensagem << ": ";

            // Verifica se o próximo input é do tipo correto
            while (!(std::cin >> valor) || std::cin.peek() != '\n') {
                std::cin.clear(); // Limpa o estado de erro
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora o restante da linha inválida
                std::cout << "Entrada inválida. Tente novamente: ";
            }

        } while (false); // Substitua false por uma condição que indica quando parar o loop

        return valor;
}

