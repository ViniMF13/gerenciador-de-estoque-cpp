#include "Item.hpp"
#include "Inventario.hpp"

#include "Interface.hpp"
#include "Movimentacao.hpp"
#include "Include/JSON/json.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>  // Para std::setw


bool Inventario::itemExiste(std::string& nome){
    // Itera pelo map e verifica se existe algum item com o nome passado
    for (const auto& par : estoque) {
        const Item& item = par.second;
        if (item.getNome() == nome) {
            return true;
        }
    }
    return false;
}

Item& Inventario::getItem(std::string& nome){
  // Itera pelo map e verifica se existe algum item com o nome passado
  for (auto& par : estoque) {
    Item& item = par.second;
    if (item.getNome() == nome) {
        return item;
    }
  }
  // Se o item não foi encontrado, lança uma exceção
  throw std::runtime_error("Item não encontrado no inventário: " + nome);
}

void Inventario::adicionarItens(){
  std::string nome = Interface::requisitarInfo<std::string>("Digite o nome do item que deseja adicionar");

  // Verifica se o item está no inventário -------= = = = = = 
  if (Inventario::itemExiste(nome)) {
    // se o item está no inventário -------= = = = = = 

    int quantidade = -1;
    while(quantidade < 0){
        quantidade = Interface::requisitarInfo<int>("Digite a quantidade de itens");    
        if(quantidade < 0)
            Interface::exibirMensagem("Valor invalido. ");
    }


    int qtd = Inventario::getItem(nome).getQuantidade();
    
    int sum = qtd + quantidade;
    

    Inventario::getItem(nome).setQuantidade(sum);
    
    Inventario::adicionarMovimentacao(nome, "entrada", quantidade);

    Interface::exibirMensagem("A quantidade de itens foi atualizada");
  } else {
    Interface::exibirMensagem("O item não existe no inventário");
  }
}

void Inventario::retirarItens(){
  std::string nome = Interface::requisitarInfo<std::string>("Digite o nome do item que deseja retirar");

  // Verifica se o item está no inventário -------= = = = = = 
  if (Inventario::itemExiste(nome)) {
  //se o item está no inventário -------= = = = = = 
    int quantidade = -1;
    while(quantidade < 0){
        quantidade = Interface::requisitarInfo<int>("Digite a quantidade de itens");    
        if(quantidade < 0)
            Interface::exibirMensagem("Valor invalido. ");
    } 

    
    int dif = Inventario::getItem(nome).getQuantidade() - quantidade;

    if(dif < 0){
        Interface::exibirMensagem("ERRO: Retirada nao realizada, estoque insuficiente de itens.");
    } else {
        if(dif == 0){
          Interface::exibirMensagem("Atencao!! Todas as unidades foram retiradas");
        }
        Inventario::getItem(nome).setQuantidade(dif);
        Interface::exibirMensagem("itens retirados.");
        Inventario::adicionarMovimentacao(nome, "saida", quantidade);
    }
  } else {
    Interface::exibirMensagem("O item nao existe no inventario");
  }
}

double Inventario::calcularValorTotal(){
    double total;
    try {
        // Itera sobre cada par (id do item, objeto Item) no inventário
        for (const auto& par : estoque) {
            const Item& item = par.second;

            // Verifica se o valor do item é válido (não é negativo)
            if (item.getValor() < 0.0) {
                throw std::invalid_argument("Valor do item não pode ser negativo.");
            }

            // Verifica se a quantidade do item é válida (não é negativa)
            if (item.getQuantidade() < 0) {
                throw std::invalid_argument("Quantidade do item não pode ser negativa.");
            }

            // Calcula o valor total para o item e soma ao total geral
            total += (item.getValor() * item.getQuantidade());
        }

        return total;
    } catch (const std::exception& e) {
        // Captura exceções padrão do C++ e imprime a mensagem de erro
        std::cerr << "Erro ao calcular o valor total: " << e.what() << std::endl;
        return -1.0; // Retorna um valor inválido para indicar erro
    }
}

void Inventario::adicionarMovimentacao(const std::string& nome, std::string tipo, int quantidade) {
     Movimentacao movimentacao(nome, tipo, quantidade);
     historico.push_back(movimentacao);
}

void Inventario::salvarDados(const std::string& nomeArquivo1, const std::string& nomeArquivo2) {
    try {
        nlohmann::json jsonInventario;  // Cria um objeto JSON para representar o inventário
        nlohmann::json jsonHistorico;   // Cria um objeto JSON para representar o histórico

        // Limpa o JSON do inventário
        jsonInventario.clear();

        // Itera sobre cada par (id do item, objeto Item) no inventário
        for (const auto& par : estoque) {
            const Item& item = par.second;  // Obtém uma referência constante ao objeto Item
            nlohmann::json jsonItem = item.toJson();  // Cria um objeto JSON para representar um item

            // Adiciona o objeto JSON do Item ao inventário JSON usando a id como chave
            std::string idItem = std::to_string(item.getId());
            jsonInventario[idItem] = jsonItem;
        }

        // Itera sobre cada item no histórico
        for (const auto& mov : historico) {
            const Movimentacao& movimentacao = mov;  // Obtém uma referência constante ao objeto movimentacao
            nlohmann::json jsonMov = movimentacao.toJson();  // Cria um objeto JSON para representar uma movimentação

            // Adiciona o objeto JSON da Movimentacao ao histórico JSON
            jsonHistorico.push_back(jsonMov);
        }

        // Cria os arquivos e grava os dados
        std::ofstream arquivo1(nomeArquivo1);
        std::ofstream arquivo2(nomeArquivo2);

        if (!arquivo1.is_open() || !arquivo2.is_open()) {
            throw std::runtime_error("Erro ao abrir arquivo para escrita.");
        }

        // Grava os dados no arquivo de inventario
        arquivo1 << std::setw(4) << jsonInventario;
        // Grava os dados no arquivo de historico
        arquivo2 << std::setw(4) << jsonHistorico;

        // Fechando os arquivos
        arquivo1.close();
        arquivo2.close();

        Interface::exibirMensagem("Dados salvos com sucesso!");
    } catch (const std::exception& e) {
        // Captura e trata exceções padrão
        std::cerr << "Erro durante a operação de salvar dados: " << e.what() << std::endl;
        Interface::exibirMensagem("Erro ao salvar dados. Consulte o console para mais informações.");
    } catch (...) {
        // Captura exceções desconhecidas
        std::cerr << "Erro desconhecido durante a operação de salvar dados." << std::endl;
        Interface::exibirMensagem("Erro desconhecido ao salvar dados. Consulte o console para obter mais informações.");
    }
}

void Inventario::carregarDados(const std::string& nomeArquivo1, const std::string& nomeArquivo2) {
  std::ifstream arquivo(nomeArquivo1);
  std::ifstream arquivo2(nomeArquivo2);

  try {
      if (!arquivo.is_open() || !arquivo2.is_open()) {
          throw std::runtime_error("Erro ao abrir o arquivo JSON para leitura.");
      }

      nlohmann::json jsonInventario;
      nlohmann::json jsonHistorico;

      arquivo >> jsonInventario;
      arquivo2 >> jsonHistorico;

      for (const auto& par : jsonInventario.items()) {
          const nlohmann::json& jsonItem = par.value();

          try {
              // Cria um novo Item e adiciona ao inventário
              Item item = Item(jsonItem);
              estoque.insert(std::make_pair(item.getId(), item));
          } catch (const nlohmann::json::exception& e) {
              std::cerr << "Erro ao processar item do inventário: " << e.what() << std::endl;
          }
      }

      for (const auto& mov : jsonHistorico.items()) {
          const nlohmann::json& jsonMov = mov.value();

          try {
              // Cria uma nova movimentação e adiciona ao histórico
              Movimentacao movimentacao = Movimentacao(jsonMov);
              historico.push_back(movimentacao);
          } catch (const nlohmann::json::exception& e) {
              std::cerr << "Erro ao processar movimentação do histórico: " << e.what() << std::endl;
          }
      }

      Interface::exibirMensagem("Dados do inventário carregados com sucesso");
  } catch (const std::exception& e) {
      std::cerr << "Erro ao carregar dados: " << e.what() << std::endl;
  }
}

std::map<int, Item>& Inventario::obterEstoque() {
      return estoque;
}

const std::vector<Movimentacao>& Inventario::obterHistorico() const {
      return historico;
}

