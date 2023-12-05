#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "../Include/Item.hpp"
#include "../Include/Movimentacao.hpp"

#include <map>
#include <vector>


class Inventario {
public:
  /**
  * @brief Verifica se um item com o nome especificado existe.
  *
  * @param nome O nome do item a ser verificado.
  * @return true se o item com o nome fornecido existir, false caso contrário.
  */
  bool itemExiste(std::string& nome);

  /**
   * @brief Retorna uma referência para o item no inventário pelo nome.
   *
   * @param nome Nome do item a ser retornado.
   * @return Referência para o item correspondente ao nome fornecido.
   */
  Item& getItem(std::string& nome);

  /**
   * @brief Adiciona uma quantidade de itens ao estoque.
   */
  void adicionarItens();

  /**
   * @brief Retira uma quantidade de itens do estoque.
   */
  void retirarItens();

  /**
   * @brief Adiciona uma movimentação ao histórico.
   *
   * @param nome Nome do item movimentado.
   * @param tipo Tipo de movimentação (entrada ou saída).
   * @param quantidade Quantidade movimentada.
   */
  void adicionarMovimentacao(const std::string& nome, std::string tipo, int quantidade);

  /**
   * @brief Salva os dados do inventário em arquivos JSON.
   *
   * @param nomeArquivo1 Nome do arquivo para o estoque.
   * @param nomeArquivo2 Nome do arquivo para o histórico.
   */
  void salvarDados(const std::string& nomeArquivo1, const std::string& nomeArquivo2);

  /**
   * @brief Carrega os dados do inventário a partir de arquivos JSON.
   *
   * @param nomeArquivo1 Nome do arquivo para o estoque.
   * @param nomeArquivo2 Nome do arquivo para o histórico.
   */
  void carregarDados(const std::string& nomeArquivo1, const std::string& nomeArquivo2);

  /**
   * @brief Calcula o valor total dos itens no inventário.
   * 
   * @return Valor total do inventário.
   */
  double calcularValorTotal() const;
  
  /**
   * @brief Retorna o estoque atual.
   *
   * @return Mapa contendo o estoque atual.
   */
  std::map<int, Item>& obterEstoque();

  /**
   * @brief Retorna o histórico de movimentações do inventário.
   * 
   * @return Vetor contendo as movimentações.
   */
  const std::vector<Movimentacao>& obterHistorico() const;


private:
  std::map<int, Item> estoque;   
  std::vector<Movimentacao> historico;    
};

#endif
