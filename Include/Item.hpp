#ifndef ITEM_H
#define ITEM_H

#include <string>

class Inventario;

class Item {
public:
    Item(const std::string& nome, double valor, int quantidade);
    Item(const std::string& nome, double valor);

    Item(const std::string& jsonString); 

    // Adicione um método à classe Item para serialização
    std::string toJson() const;

    // Métodos getters e setters para os atributos do Item
    /// @brief Retorna a quantidade de itens
    ///
    int getId() const;

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
    
    static int gerarId();

    static void cadastrarItem(Inventario& inventario);

    static void removerItem(Inventario& inventario);

    static void atualizarValor(Inventario& inventario);

private:
    int id;
    std::string nome;
    double valor;
    int quantidade;

};


#endif // ITEM_H