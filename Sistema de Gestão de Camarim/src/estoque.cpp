/**
 * @file estoque.cpp
 * @brief Implementação da classe Estoque
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

#include "estoque.h"
#include "excecoes.h"
#include <sstream>
#include <iomanip>

// Construtor
Estoque::Estoque() {}

// Destrutor
Estoque::~Estoque() {}

// Adiciona item ao estoque
void Estoque::adicionarItem(int itemId, const string& nomeItem, int quantidade) {
    if (itemId < 0) {
        throw ValidacaoException("ID do item inválido");
    }
    
    if (nomeItem.empty()) {
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    
    if (quantidade < 0) {
        throw ValidacaoException("Quantidade não pode ser negativa");
    }
    
    // Se item já existe, adiciona à quantidade
    if (itens.find(itemId) != itens.end()) {
        itens[itemId].quantidade += quantidade;
    } else {
        itens[itemId] = ItemEstoque(itemId, nomeItem, quantidade);
    }
}

// Remove quantidade de um item do estoque
bool Estoque::removerItem(int itemId, int quantidade) {
    if (itens.find(itemId) == itens.end()) {
        throw EstoqueException("Item não encontrado no estoque (ID: " + to_string(itemId) + ")");
    }
    
    if (quantidade < 0) {
        throw ValidacaoException("Quantidade não pode ser negativa");
    }
    
    if (itens[itemId].quantidade < quantidade) {
        throw EstoqueInsuficienteException(
            "Quantidade insuficiente. Disponível: " + to_string(itens[itemId].quantidade) +
            ", Solicitado: " + to_string(quantidade)
        );
    }
    
    itens[itemId].quantidade -= quantidade;
    
    // Remove item se quantidade chegar a zero
    if (itens[itemId].quantidade == 0) {
        itens.erase(itemId);
    }
    
    return true;
}

// Verifica se há quantidade suficiente
bool Estoque::verificarDisponibilidade(int itemId, int quantidade) const {
    auto it = itens.find(itemId);
    
    if (it == itens.end()) {
        return false;
    }
    
    return it->second.quantidade >= quantidade;
}

// Obtém quantidade de um item
int Estoque::obterQuantidade(int itemId) const {
    auto it = itens.find(itemId);
    
    if (it == itens.end()) {
        return 0;
    }
    
    return it->second.quantidade;
}

// Remove completamente um item do estoque
bool Estoque::removerItemCompleto(int itemId) {
    auto it = itens.find(itemId);
    
    if (it == itens.end()) {
        return false;
    }
    
    itens.erase(itemId);
    return true;
}

// Lista todos os itens em estoque
vector<ItemEstoque> Estoque::listar() const {
    vector<ItemEstoque> lista;
    
    for (const auto& par : itens) {
        lista.push_back(par.second);
    }
    
    return lista;
}

// Atualiza quantidade de um item
void Estoque::atualizarQuantidade(int itemId, int novaQuantidade) {
    if (itens.find(itemId) == itens.end()) {
        throw EstoqueException("Item não encontrado no estoque");
    }
    
    if (novaQuantidade < 0) {
        throw ValidacaoException("Quantidade não pode ser negativa");
    }
    
    itens[itemId].quantidade = novaQuantidade;
    
    // Remove se quantidade for zero
    if (novaQuantidade == 0) {
        itens.erase(itemId);
    }
}

// Exibe informações do estoque
string Estoque::exibir() const {
    stringstream ss;
    ss << "=== ESTOQUE ===" << endl;
    
    if (itens.empty()) {
        ss << "Estoque vazio" << endl;
    } else {
        ss << left << setw(5) << "ID" << setw(30) << "Nome" 
           << setw(10) << "Quantidade" << endl;
        ss << string(45, '-') << endl;
        
        for (const auto& par : itens) {
            const ItemEstoque& item = par.second;
            ss << left << setw(5) << item.itemId 
               << setw(30) << item.nomeItem
               << setw(10) << item.quantidade << endl;
        }
    }
    
    return ss.str();
}

// Sobrecarga do operador <<
ostream& operator<<(ostream& os, const Estoque& estoque) {
    os << estoque.exibir();
    return os;
}
