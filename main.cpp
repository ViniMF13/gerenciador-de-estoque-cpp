#include "./Include/Inventario.hpp"
#include "./Include/Interface.hpp"
//#include "./src/Interface.cpp"
#include "./Include/Item.hpp"
#include "./Include/Movimentacao.hpp"

#include <iostream>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"


int main() {
    Inventario meuInventario;
    meuInventario.carregarDados("output/Inventario.json", "output/Historico.json");
    Interface::limparTela();
    while (true) {
        Interface::exibirMenu();
        // Leitura da escolha do usuário
        int n = Interface::solicitarInt("Escolha uma opcao");

        if (n == 1) {
            Item::cadastrarItem(meuInventario);
        } else if (n == 2) {
            Item::removerItem(meuInventario);
        } else if (n == 3) {
            Interface::limparTela();
            Item::atualizarValor(meuInventario);
        } else if (n == 4) {
            Interface::limparTela();
            meuInventario.adicionarItens();
        } else if (n == 5) {
            Interface::limparTela();
            meuInventario.retirarItens();
        } else if (n == 6) {
            Interface::limparTela();
            Interface::exibirItens(meuInventario);
            
        } else if (n == 7) {
            Interface::limparTela();
            Interface::verValorTotal(meuInventario);

        } else if (n == 8) {
            // 
            Interface::limparTela();
            Interface::exibirHistorico(meuInventario);
            
        } else if (n == 9){
            meuInventario.salvarDados("output/Inventario.json", "output/Historico.json"); 
            break;  // Sai do loop para encerrar o programa
        } else {
            Interface::limparTela();
            std::cout << RED ;
            Interface::exibirMensagem("Erro: Escolha invalida");
            std::cout << RESET;
        }

    }
    return 0;
}