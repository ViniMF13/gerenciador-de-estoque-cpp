// Interface.cpp
#include "Interface.hpp"
#include <chrono>
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
    std::cout << "| 1 - Cadastrar novo item           |" << std::endl;
    std::cout << "| 2 - Remover um item               |" << std::endl;
    std::cout << "| 3 - Atualizar Valor do item       |" << std::endl;
    std::cout << " =================================== " << std::endl;
         //Inventário
    std::cout << "|           | Iventario |           |" << std::endl;
    std::cout << "| 4 - Adicionar itens               |" << std::endl;
    std::cout << "| 5 - Retirar itens                |" << std::endl;
    std::cout << "| 6 - Listar itens                  |" << std::endl;
    std::cout << "| 7 - Ver Historico de movimentacao |" << std::endl;
        //Historicos
        //  std::cout << ": histórico de entradas" << std::endl;
        //  std::cout << ": Histórico de saidas" << std::endl;
        //Configurações
        //  std::cout << ": Idioma" << std::endl;
        //  std::cout << ": Moeda" << std::endl;
    std::cout << "| 10 - Salvar e Sair                |" << std::endl;
    std::cout << " =================================== " << RESET << std::endl;
    std::cout << std::endl;
}

void Interface::exibirMensagem(const std::string& mensagem) {
    std::cout << mensagem << std::endl;
}

void Interface::exibirItens(Inventario& inventario) {
    std::cout << "Itens no inventário: " << std::endl;
    std::cout << "ID" << "\t" << "NOME" << "\t" << "VALOR" << "\t" << "QUANTIDADE" << std::endl; 
    for (auto& par : inventario.obterEstoque()) {
        std::cout << par.first << "\t" << par.second.getNome() << "\t" << par.second.getValor() << " \t" << par.second.getQuantidade() << std::endl;
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