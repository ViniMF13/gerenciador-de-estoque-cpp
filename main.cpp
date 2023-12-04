#include "Item.cpp"
#include "Inventario.cpp"
#include "Interface.cpp"
#include "Movimentacao.cpp"
#include <iostream>


int main() {
    Inventario meuInventario;
    meuInventario.carregarDados("output/Inventario.json", "output/Historico.json");
    Interface::limparTela();
    while (true) {
        // Interface::exibirMensagem("\n");
        Interface::exibirMenu();
        // Leitura da escolha do usuário

        int n = Interface::requisitarInfo<int>("Opcao");


        if (n == 1) {
            Item::cadastrarItem(meuInventario);
            // Cadastrar item();
        } else if (n == 2) {
            // remover itens do inventario
            Item::removerItem(meuInventario);
        } else if (n == 3) {
            // atualizar valor itens do inventario
            Interface::limparTela();
            Item::atualizarValor(meuInventario);
        } else if (n == 4) {
            // Adicionar itens ao inventario
            Interface::limparTela();
            meuInventario.adicionarItens();
        } else if (n == 5) {
            // Retirar itens do inventário
            Interface::limparTela();
            meuInventario.retirarItens();
        } else if (n == 6) {
            // Listar Itens
            Interface::limparTela();
            Interface::exibirItens(meuInventario);
            
        } else if (n == 7) {
            // exibe o valor total do inventario
            Interface::limparTela();
            Interface::verValorTotal(meuInventario);

        } else if (n == 8) {
            // exibe historico de movimentações feitas no inventario
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