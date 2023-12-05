#ifndef ITEM_H
#define ITEM_H

#include <string>

class Inventario;

/**
 * @brief Classe que representa os itens.
 * 
 * Essa classe gerencia a criação de itens com nome, valor e quantidade.
 * 
 */
class Item {
public:
    /**
     * @brief Construtor para criar um item com quantidade definida.
     *
     * @param nome Nome do item.
     * @param valor Valor do item.
     * @param quantidade Quantidade inicial do item.
     */
    Item(const std::string& nome, double valor, int quantidade);

        /**
     * @brief Construtor para criar um item com quantidade padrão de 0.
     *
     * @param nome Nome do item.
     * @param valor Valor do item.
     */
    Item(const std::string& nome, double valor);

    /**
     * @brief Construtor para criar um item a partir de uma string JSON.
     *
     * @param jsonString String JSON representando o item.
     */
    Item(const std::string& jsonString); 

    /**
     * @brief Serializa o item em uma string JSON.
     *
     * @return String JSON representando o item.
     */
    std::string toJson() const;

    /**
     * @brief Retorna o ID do item.
     *
     * @return ID do item.
     */
    int getId() const;

    /**
     * @brief Retorna o nome do item.
     * 
     * @return Nome do item.
     */ 
    std::string getNome() const;
    
    /**
     * @brief Retorna o valor do item.
     * 
     * @return Valor do item.
     */
    double getValor() const;

    /**
     * @brief Retorna a quantidade de itens.
     * 
     * @return Quantidade de itens.
     */
    int getQuantidade() const;
    
    /**
     * @brief Define o valor do item.
     *
     * @param valor Novo valor do item.
     */
    void setValor(double valor);

    /**
     * @brief Define a quantidade de itens no estoque.
     *
     * @param quantidade Nova quantidade de itens no estoque.
     */
    void setQuantidade(int quantidade);
    
    /**
     * @brief Gera um ID único para o item.
     *
     * @return ID gerado.
     */
    static int gerarId();

    /**
     * @brief Cadastra um novo item no inventário.
     *
     * @param inventario Referência para o inventário onde o item será cadastrado.
     */
    static void cadastrarItem(Inventario& inventario);

    /**
     * @brief Remove um item do inventário.
     *
     * @param inventario Referência para o inventário de onde o item será removido.
     */
    static void removerItem(Inventario& inventario);

    /**
     * @brief Atualiza o valor de um item no inventário.
     *
     * @param inventario Referência para o inventário onde o valor será atualizado.
     */
    static void atualizarValor(Inventario& inventario);

private:
    int id;
    std::string nome;
    double valor;
    int quantidade;

};


#endif // ITEM_H
