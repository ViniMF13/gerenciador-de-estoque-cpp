#ifndef INTERFACE_H
#define INTERFACE_H

#include "../Include/Inventario.hpp"
#include "../Include/Item.hpp"

#include <iostream>


class Interface {
public:
   
    static void exibirMenu();
    static void exibirMensagem(const std::string& mensagem);
    static void limparTela();
    static void exibirItens(Inventario& inventario);
    static void exibirHistorico(const Inventario& inventario);
    static void verValorTotal(const Inventario& inventario);

    // Funções para leitura de dados do usuário
    static int solicitarInt(const std::string& mensagem);
    static double solicitarDouble(const std::string& mensagem);
    static std::string solicitarString(const std::string& mensagem);


};


#endif