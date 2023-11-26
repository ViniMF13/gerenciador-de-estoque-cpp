#ifndef INVENTARIO_H
#define INVENTARIO_H

class Item;

#include "Movimentacao.hpp"
#include <map>
#include <vector>


class Inventario {
public:
  /// @brief verifica se o item existe no inventário
  ///
  bool itemExiste(std::string& nome);

  /// @brief retorna um item presente no inventario
  ///
  Item& getItem(std::string& nome);

  /// @brief Adiciona uma quantiade de itens ao estoque
  ///
  void adicionarItens();

  /// @brief Retira uma quantiade de itens do estoque
  ///
  void retirarItens();

  void adicionarMovimentacao(const std::string& nome, std::string tipo, int quantidade);

  void salvarDados(const std::string& nomeArquivo1, const std::string& nomeArquivo2);

  void carregarDados(const std::string& nomeArquivo1, const std::string& nomeArquivo2);

  double calcularValorTotal() const;
  
  /// @brief retorna o inventário
  ///
  std::map<int, Item>& obterEstoque();

  const std::vector<Movimentacao>& obterHistorico() const;


private:
  std::map<int, Item> estoque;   
  std::vector<Movimentacao> historico;    
};

#endif