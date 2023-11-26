#ifndef INTERFACE_H
#define INTERFACE_H


#include <iostream>
#include "Inventario.hpp"
#include "Item.hpp"

class Interface {
public:
    // Tipo estático para não precisar criar uma instância da classe antes de chamar um método
    static void exibirMenu();
    static void exibirMensagem(const std::string& mensagem);
    static void limparTela();
    static void exibirItens(Inventario& inventario);
    static void exibirHistorico(const Inventario& inventario);
    static void verValorTotal(const Inventario& inventario);

    static std::string lerNome(const std::string& mensagem);

    template <typename T>
    static T requisitarInfo(const std::string& mensagem);
};


#endif