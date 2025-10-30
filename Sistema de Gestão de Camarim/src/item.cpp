/**
 * @file item.cpp
 * @brief Implementação da classe Item e GerenciadorItens
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

#include "item.h"
#include "excecoes.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

// ==================== Classe Item ====================

// Construtor padrão
Item::Item() : id(0), nome(""), preco(0.0) {}

// Construtor parametrizado
Item::Item(int id, const string& nome, double preco)
    : id(id), nome(nome), preco(preco) {}

// Destrutor
Item::~Item() {}

// Getters
int Item::getId() const {
    return id;
}

string Item::getNome() const {
    return nome;
}

double Item::getPreco() const {
    return preco;
}

// Setters com validação
void Item::setId(int id) {
    if (id < 0) {
        throw ValidacaoException("ID do item não pode ser negativo");
    }
    this->id = id;
}

void Item::setNome(const string& nome) {
    if (nome.empty()) {
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    this->nome = nome;
}

void Item::setPreco(double preco) {
    if (preco < 0) {
        throw ValidacaoException("Preço do item não pode ser negativo");
    }
    this->preco = preco;
}

// Exibe informações do item
string Item::exibir() const {
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << "Item [ID: " << id << ", Nome: " << nome 
       << ", Preço: R$ " << preco << "]";
    return ss.str();
}

// Sobrecarga do operador <<
ostream& operator<<(ostream& os, const Item& item) {
    os << item.exibir();
    return os;
}

// Sobrecarga do operador ==
bool Item::operator==(const Item& outro) const {
    return this->id == outro.id;
}

// ==================== Classe GerenciadorItens ====================

// Construtor
GerenciadorItens::GerenciadorItens() : proximoId(1) {}

// Cadastra novo item
int GerenciadorItens::cadastrar(const string& nome, double preco) {
    // Validações
    if (nome.empty()) {
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    
    if (preco < 0) {
        throw ValidacaoException("Preço do item não pode ser negativo");
    }
    
    // Verifica se item já existe
    if (buscarPorNome(nome) != nullptr) {
        throw ItemException("Item já existe com este nome: " + nome);
    }
    
    Item novoItem(proximoId, nome, preco);
    itens.push_back(novoItem);
    
    return proximoId++;
}

// Busca item por ID
Item* GerenciadorItens::buscarPorId(int id) {
    for (auto& item : itens) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

// Busca item por nome
Item* GerenciadorItens::buscarPorNome(const string& nome) {
    for (auto& item : itens) {
        if (item.getNome() == nome) {
            return &item;
        }
    }
    return nullptr;
}

// Remove item por ID
bool GerenciadorItens::remover(int id) {
    auto it = remove_if(itens.begin(), itens.end(),
                       [id](const Item& i) { return i.getId() == id; });
    
    if (it != itens.end()) {
        itens.erase(it, itens.end());
        return true;
    }
    return false;
}

// Lista todos os itens
vector<Item> GerenciadorItens::listar() const {
    return itens;
}

// Atualiza dados de um item
bool GerenciadorItens::atualizar(int id, const string& nome, double preco) {
    Item* item = buscarPorId(id);
    
    if (item == nullptr) {
        throw ItemException("Item com ID " + to_string(id) + " não encontrado");
    }
    
    // Verifica se novo nome já está em uso por outro item
    Item* itemComNome = buscarPorNome(nome);
    if (itemComNome != nullptr && itemComNome->getId() != id) {
        throw ItemException("Já existe outro item com este nome: " + nome);
    }
    
    item->setNome(nome);
    item->setPreco(preco);
    
    return true;
}
