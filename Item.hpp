#ifndef ITEM_H
#define ITEM_H

#include "Inventario.hpp"
#include <string>

class Item {
public:
    Item(const std::string& nome, double valor, int quantidade);
    Item(const std::string& nome, double valor);
    Item(const std::string& jsonString); 
    
    // Métodos getters e setters para os atributos do Item
    /// @brief Retorna o nome do item
    ///
    std::string getNome() const;
    /// @brief Retorna o valor do item
    ///
    double getValor() const;
    /// @brief Retorna a quantidade de itens
    ///
    int getQuantidade() const;
    
    /// @brief Retorna a quantidade de itens
    ///
    void setValor(double valor);

    /// @brief 
    ///
    void setQuantidade(int quantidade);

    // Adicione um método à classe Item para serialização
    std::string toJson() const;

    static void cadastrarItem(Inventario& inventario);

private:
    std::string nome;
    double valor;
    int quantidade;
    
};


#endif // ITEM_H