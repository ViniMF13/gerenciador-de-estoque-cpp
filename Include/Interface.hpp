#ifndef INTERFACE_H
#define INTERFACE_H

#include "../Include/Inventario.hpp"
#include "../Include/Item.hpp"

#include <iostream>

/**
 * @brief Classe que representa a interface do sistema.
 * 
 * Essa classe gerencia a interação do usuário com o sistema.
 * 
 */
class Interface {
public:
    /**
     * @brief Exibe o menu principal na tela.
     */
    static void exibirMenu();

    /**
     * @brief Exibe uma mensagem na tela.
     *
     * @param mensagem A mensagem a ser exibida.
     */
    static void exibirMensagem(const std::string& mensagem);

    /**
     * @brief Limpa a tela do console.
     */
    static void limparTela();

    /**
     * @brief Exibe a lista de itens presentes no inventário na tela.
     *
     * @param inventario O inventário a ser exibido.
     */
    static void exibirItens(Inventario& inventario);

    /**
     * @brief Exibe o histórico de movimentações do inventário.
     *
     * @param inventario O inventário do histórico que será exibido.
     */
    static void exibirHistorico(const Inventario& inventario);

    /**
     * @brief Exibe o valor total dos itens no inventário.
     *
     * @param inventario O inventário para calcular o valor total.
     */
    static void verValorTotal(const Inventario& inventario);


    /**
    * @brief Solicita um valor inteiro do usuário.
    *
    * @param mensagem A mensagem a ser exibida como prompt para o usuário.
    * @return O valor inteiro inserido pelo usuário.
    */
    static int solicitarInt(const std::string& mensagem);

    /**
    * @brief Solicita um valor de ponto flutuante do usuário.
    *
    * @param mensagem A mensagem a ser exibida como prompt para o usuário.
    * @return O valor de ponto flutuante inserido pelo usuário.
     */
    static double solicitarDouble(const std::string& mensagem);

    /**
    * @brief Solicita uma string do usuário.
    *
    * @param mensagem A mensagem a ser exibida como prompt para o usuário.
    * @return A string inserida pelo usuário.
    */
    static std::string solicitarString(const std::string& mensagem);


};


#endif
