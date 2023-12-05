#ifndef MOVIMENTACAO_H
#define MOVIMENTACAO_H

#include <string>
#include <ctime>

/**
 * @brief Classe que representa a movimentação de itens.
 * 
 * Essa classe gerencia todas as movimentações de itens no estoque com data e quantidade.
 * 
 */
class Movimentacao {
public:
    /**
     * @brief Construtor para criar uma movimentação.
     *
     * @param n Nome do item movimentado.
     * @param t Tipo da movimentação (entrada ou saída).
     * @param q Quantidade da movimentação.
     */
    Movimentacao(const std::string& n, std::string& t, int q);

    /**
     * @brief Construtor para criar uma movimentação com data definida.
     *
     * @param n Nome do item movimentado.
     * @param t Tipo da movimentação (entrada ou saída).
     * @param q Quantidade da movimentação.
     * @param d Data da movimentação.
     */
    Movimentacao(const std::string& n, std::string& t, int q, int d);

    /**
     * @brief Construtor para criar uma movimentação a partir de uma string JSON.
     *
     * @param jsonString String JSON representando a movimentação.
     */
    Movimentacao(const std::string& jsonString);

    /**
    * @brief Obtém o nome do item.
    *
    * @return Uma string representando o nome do item.
    */
    std::string getNome() const;

    /**
    * @brief Obtém o tipo do item.
    *
    * @return Uma string representando o tipo do item.
    */
    std::string getTipo() const;

    /**
     * @brief Obtém a quantidade do item.
     *
     * @return A quantidade do item como um inteiro.
     */
    int getQuantidade() const;

    /**
     * @brief Obtém a data associada ao item.
     *
     * @return Um valor de tempo (std::time_t) representando a data associada ao item.
     */
    std::time_t getData() const;

    /**
     * @brief Converte a movimentação para uma string JSON.
     *
     * @return String JSON representando a movimentação.
     */
    std::string toJson() const;

private:
    std::string nome;
    std::string tipo;
    int quantidade;
    std::time_t data;
};



#endif 
