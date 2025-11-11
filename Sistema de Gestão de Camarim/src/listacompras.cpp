/**
 * @file listacompras.cpp
 * @brief Implementação da classe ListaCompras e GerenciadorListaCompras
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

#include "listacompras.h"
#include "excecoes.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

// ==================== Classe ListaCompras ====================

// Construtor padrão
ListaCompras::ListaCompras() : id(0), descricao("") {}

// Construtor parametrizado
ListaCompras::ListaCompras(int id, const string& descricao)
    : id(id), descricao(descricao) {}

// Destrutor
ListaCompras::~ListaCompras() {}

// Getters
int ListaCompras::getId() const {
    return id;
}

string ListaCompras::getDescricao() const {
    return descricao;
}

// Setters
void ListaCompras::setId(int id) {
    if (id < 0) {
        throw ValidacaoException("ID da lista inválido");
    }
    this->id = id;
}

void ListaCompras::setDescricao(const string& descricao) {
    if (descricao.empty()) {
        throw ValidacaoException("Descrição não pode ser vazia");
    }
    this->descricao = descricao;
}

// Adiciona item à lista
void ListaCompras::adicionarItem(int itemId, const string& nomeItem, int quantidade, double preco) {
    if (itemId < 0) {
        throw ValidacaoException("ID do item inválido");
    }
    
    if (nomeItem.empty()) {
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    
    if (quantidade <= 0) {
        throw ValidacaoException("Quantidade deve ser maior que zero");
    }
    
    if (preco < 0) {
        throw ValidacaoException("Preço não pode ser negativo");
    }
    
    // Se item já existe, atualiza quantidade e recalcula subtotal
    if (itens.find(itemId) != itens.end()) {
        itens[itemId].quantidade += quantidade;
        itens[itemId].subtotal = itens[itemId].quantidade * itens[itemId].preco;
    } else {
        itens[itemId] = ItemCompra(itemId, nomeItem, quantidade, preco);
    }
}

// Remove item da lista
bool ListaCompras::removerItem(int itemId) {
    auto it = itens.find(itemId);
    
    if (it == itens.end()) {
        return false;
    }
    
    itens.erase(itemId);
    return true;
}

// Atualiza quantidade de um item
void ListaCompras::atualizarQuantidade(int itemId, int quantidade) {
    if (itens.find(itemId) == itens.end()) {
        throw ListaComprasException("Item não encontrado na lista");
    }
    
    if (quantidade <= 0) {
        throw ValidacaoException("Quantidade deve ser maior que zero");
    }
    
    itens[itemId].quantidade = quantidade;
    itens[itemId].subtotal = quantidade * itens[itemId].preco;
}

// Calcula total da lista de compras
double ListaCompras::calcularTotal() const {
    double total = 0.0;
    
    for (const auto& par : itens) {
        total += par.second.subtotal;
    }
    
    return total;
}

// Limpa toda a lista
void ListaCompras::limpar() {
    itens.clear();
}

// Exibe informações da lista
string ListaCompras::exibir() const {
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << "=== LISTA DE COMPRAS ===" << endl;
    ss << "ID: " << id << endl;
    ss << "Descrição: " << descricao << endl;
    ss << "\nItens:" << endl;
    
    if (itens.empty()) {
        ss << "  Lista vazia" << endl;
    } else {
        ss << left << setw(5) << "  ID" << setw(25) << "Nome" 
           << setw(8) << "Qtd" << setw(12) << "Preço Unit."
           << setw(12) << "Subtotal" << endl;
        ss << "  " << string(60, '-') << endl;
        
        for (const auto& par : itens) {
            const ItemCompra& item = par.second;
            ss << left << setw(5) << "  " + to_string(item.itemId)
               << setw(25) << item.nomeItem
               << setw(8) << item.quantidade
               << "R$ " << setw(9) << item.preco
               << "R$ " << setw(9) << item.subtotal << endl;
        }
        
        ss << "  " << string(60, '-') << endl;
        ss << right << setw(50) << "TOTAL: R$ " << setw(9) << calcularTotal() << endl;
    }
    
    return ss.str();
}

// Sobrecarga do operador <<
ostream& operator<<(ostream& os, const ListaCompras& lista) {
    os << lista.exibir();
    return os;
}

// ==================== Classe GerenciadorListaCompras ====================

// Construtor
GerenciadorListaCompras::GerenciadorListaCompras() : proximoId(1) {}

// Cria nova lista de compras
int GerenciadorListaCompras::criar(const string& descricao) {
    if (descricao.empty()) {
        throw ValidacaoException("Descrição não pode ser vazia");
    }
    
    ListaCompras novaLista(proximoId, descricao);
    listas.push_back(novaLista);
    
    return proximoId++;
}

// Busca lista por ID
ListaCompras* GerenciadorListaCompras::buscarPorId(int id) {
    for (auto& lista : listas) {
        if (lista.getId() == id) {
            return &lista;
        }
    }
    return nullptr;
}

// Remove lista
bool GerenciadorListaCompras::remover(int id) {
    auto it = remove_if(listas.begin(), listas.end(),
                       [id](const ListaCompras& l) { return l.getId() == id; });
    
    if (it != listas.end()) {
        listas.erase(it, listas.end());
        return true;
    }
    return false;
}

// Lista todas as listas de compras
vector<ListaCompras> GerenciadorListaCompras::listar() const {
    return listas;
}
