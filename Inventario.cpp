#include "Item.hpp"
#include "Inventario.hpp"

#include "Interface.hpp"
#include "Movimentacao.hpp"
#include "Include/json.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>  // Para std::setw


bool Inventario::itemExiste(std::string nome){
    // Itera pelo map e verifica se existe algum item com o nome passado
    auto it = estoque.find(nome);
    if(it == estoque.end()){
      return false;  
    } else {
      return true; 
    }
}

Item& Inventario::getItem(std::string& nome){
    auto it = estoque.find(nome);
      return it->second;
}


void Inventario::adicionarItens(){
  std::string nome = Interface::lerValor<std::string>("Digite o nome do item que deseja adicionar");

  // Verifica se o item está no inventário -------= = = = = = 
  if (Inventario::itemExiste(nome)) {
    // se o item está no inventário -------= = = = = = 
    int quantidade = Interface::lerValor<int>("Digite a quantidade de itens");    

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
  std::string nome = Interface::lerValor<std::string>("Digite o nome do item que deseja retirar");

  // Verifica se o item está no inventário -------= = = = = = 
  if (Inventario::itemExiste(nome)) {
  //se o item está no inventário -------= = = = = = 
    int quantidade = Interface::lerValor<int>("Digite a quantidade de itens"); 
    
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

void Inventario::adicionarMovimentacao(const std::string& nome, std::string tipo, int quantidade) {
     Movimentacao movimentacao(nome, tipo, quantidade);
     historico.push_back(movimentacao);
}

void Inventario::salvarDados(const std::string& nomeArquivo1, const std::string& nomeArquivo2) {
    nlohmann::json jsonInventario;  // Cria um objeto JSON para representar o inventário
    nlohmann::json jsonHistorico;  // Cria um objeto JSON para representar o historico

    // Itera sobre cada par (nome do item, objeto Item) no inventário
    for (const auto& par : estoque) {
      const Item& item = par.second;  // Obtém uma referência constante ao objeto Item
      nlohmann::json jsonItem = item.toJson();  // Cria um objeto JSON para representar um item
      
      // Adiciona o objeto JSON do Item ao inventário JSON usando o nome como chave
      jsonInventario[item.getNome()] = jsonItem;
    }

     // Itera sobre cada item no historico
    for (const auto& mov : historico) {
      const Movimentacao& movimentacao = mov;  // Obtém uma referência constante ao objeto movimentacao
      nlohmann::json jsonMov = movimentacao.toJson();  // Cria um objeto JSON para representar uma movimetação 
            
      // Adiciona o objeto JSON do Item ao inventário JSON usando o nome como chave
      jsonHistorico.push_back(jsonMov);
    }

    // Cria os arquivos e grava os dados 
    std::ofstream arquivo1(nomeArquivo1);
    std::ofstream arquivo2(nomeArquivo2);
    
    arquivo1 << std::setw(4) << jsonInventario;
    arquivo2 << std::setw(4) << jsonHistorico;

}

void Inventario::carregarDados(const std::string& nomeArquivo1, const std::string& nomeArquivo2) {
  std::ifstream arquivo(nomeArquivo1);
  std::ifstream arquivo2(nomeArquivo2);

  if (!arquivo.is_open() && !arquivo2.is_open()) {
      // Lidar com a falha ao abrir o arquivo, se necessário
      std::cerr << "Erro ao abrir o arquivo JSON para leitura." << std::endl;
      return;
  }
  
  nlohmann::json jsonInventario;
  nlohmann::json jsonHistorico;
  arquivo >> jsonInventario;
  arquivo2 >> jsonHistorico;

  for (const auto& par : jsonInventario.items()) {
    const nlohmann::json& jsonItem = par.value() ;

    // Cria um novo Item e adiciona ao inventário
    Item item = Item(jsonItem);
    estoque.insert(std::make_pair(item.getNome(), item));
  }

  for (const auto& mov : jsonHistorico.items()) {
    const nlohmann::json& jsonMov = mov.value();

    // Cria um novo Item e adiciona ao inventário
    Movimentacao movimentacao = Movimentacao(jsonMov);

    // std::string tipo = jsonMov["tipo"];
    // std::string nome = jsonMov["nome"]; 
    // int quantidade = jsonMov["quantidade"];
    // int data = jsonMov["data"];
    
    historico.push_back(movimentacao);
  }
    Interface::exibirMensagem("Dados do inventario carregados com sucesso");
}

std::map<std::string, Item>& Inventario::obterEstoque() {
      return estoque;
}

const std::vector<Movimentacao>& Inventario::obterHistorico() const {
      return historico;
}

