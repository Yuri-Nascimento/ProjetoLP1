/**
 * @file camarim.cpp
 * @brief Implementação da classe Camarim e GerenciadorCamarins
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

#include "camarim.h"
#include "excecoes.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

// ==================== Classe Camarim ====================

// Construtor padrão
Camarim::Camarim() : id(0), nome(""), artistaId(0) {}

// Construtor parametrizado
Camarim::Camarim(int id, const string& nome, int artistaId)
    : id(id), nome(nome), artistaId(artistaId) {}

// Destrutor
Camarim::~Camarim() {}

// Getters
int Camarim::getId() const {
    return id;
}

string Camarim::getNome() const {
    return nome;
}

int Camarim::getArtistaId() const {
    return artistaId;
}

// Setters
void Camarim::setId(int id) {
    if (id < 0) {
        throw ValidacaoException("ID do camarim inválido");
    }
    this->id = id;
}

void Camarim::setNome(const string& nome) {
    if (nome.empty()) {
        throw ValidacaoException("Nome do camarim não pode ser vazio");
    }
    this->nome = nome;
}

void Camarim::setArtistaId(int artistaId) {
    this->artistaId = artistaId;
}

// Adiciona item ao camarim
void Camarim::inserirItem(int itemId, const string& nomeItem, int quantidade) {
    if (itemId < 0) {
        throw ValidacaoException("ID do item inválido");
    }
    
    if (nomeItem.empty()) {
        throw ValidacaoException("Nome do item não pode ser vazio");
    }
    
    if (quantidade <= 0) {
        throw ValidacaoException("Quantidade deve ser maior que zero");
    }
    
    // Se item já existe, adiciona à quantidade
    if (itens.find(itemId) != itens.end()) {
        itens[itemId].quantidade += quantidade;
    } else {
        itens[itemId] = ItemCamarim(itemId, nomeItem, quantidade);
    }
}

// Remove item do camarim
bool Camarim::removerItem(int itemId, int quantidade) {
    if (itens.find(itemId) == itens.end()) {
        throw CamarimException("Item não encontrado no camarim");
    }
    
    if (quantidade <= 0) {
        throw ValidacaoException("Quantidade deve ser maior que zero");
    }
    
    if (itens[itemId].quantidade < quantidade) {
        throw CamarimException("Quantidade insuficiente no camarim");
    }
    
    itens[itemId].quantidade -= quantidade;
    
    // Remove item se quantidade chegar a zero
    if (itens[itemId].quantidade == 0) {
        itens.erase(itemId);
    }
    
    return true;
}

// Verifica se item existe no camarim
bool Camarim::contemItem(int itemId) const {
    return itens.find(itemId) != itens.end();
}

// Obtém quantidade de um item
int Camarim::obterQuantidadeItem(int itemId) const {
    auto it = itens.find(itemId);
    
    if (it == itens.end()) {
        return 0;
    }
    
    return it->second.quantidade;
}

// Lista todos os itens do camarim
vector<ItemCamarim> Camarim::listarItens() const {
    vector<ItemCamarim> lista;
    
    for (const auto& par : itens) {
        lista.push_back(par.second);
    }
    
    return lista;
}

// Calcula total de itens
int Camarim::calcularTotalItens() const {
    int total = 0;
    
    for (const auto& par : itens) {
        total += par.second.quantidade;
    }
    
    return total;
}

// Exibe informações do camarim
string Camarim::exibir() const {
    stringstream ss;
    ss << "=== CAMARIM ===" << endl;
    ss << "ID: " << id << endl;
    ss << "Nome: " << nome << endl;
    ss << "Artista ID: " << artistaId << endl;
    ss << "Total de itens: " << calcularTotalItens() << endl;
    ss << "\nItens:" << endl;
    
    if (itens.empty()) {
        ss << "  Nenhum item no camarim" << endl;
    } else {
        ss << left << setw(5) << "  ID" << setw(30) << "Nome" 
           << setw(10) << "Quantidade" << endl;
        ss << "  " << string(42, '-') << endl;
        
        for (const auto& par : itens) {
            const ItemCamarim& item = par.second;
            ss << left << setw(5) << "  " + to_string(item.itemId)
               << setw(30) << item.nomeItem
               << setw(10) << item.quantidade << endl;
        }
    }
    
    return ss.str();
}

// Sobrecarga do operador <<
ostream& operator<<(ostream& os, const Camarim& camarim) {
    os << camarim.exibir();
    return os;
}

// ==================== Classe GerenciadorCamarins ====================

// Construtor
GerenciadorCamarins::GerenciadorCamarins() : proximoId(1) {}

// Cadastra novo camarim
int GerenciadorCamarins::cadastrar(const string& nome, int artistaId) {
    if (nome.empty()) {
        throw ValidacaoException("Nome do camarim não pode ser vazio");
    }
    
    Camarim novoCamarim(proximoId, nome, artistaId);
    camarins.push_back(novoCamarim);
    
    return proximoId++;
}

// Busca camarim por ID
Camarim* GerenciadorCamarins::buscarPorId(int id) {
    for (auto& camarim : camarins) {
        if (camarim.getId() == id) {
            return &camarim;
        }
    }
    return nullptr;
}

// Busca camarim por artista
Camarim* GerenciadorCamarins::buscarPorArtista(int artistaId) {
    for (auto& camarim : camarins) {
        if (camarim.getArtistaId() == artistaId) {
            return &camarim;
        }
    }
    return nullptr;
}

// Remove camarim
bool GerenciadorCamarins::remover(int id) {
    auto it = remove_if(camarins.begin(), camarins.end(),
                       [id](const Camarim& c) { return c.getId() == id; });
    
    if (it != camarins.end()) {
        camarins.erase(it, camarins.end());
        return true;
    }
    return false;
}

// Lista todos os camarins
vector<Camarim> GerenciadorCamarins::listar() const {
    return camarins;
}

// Atualiza camarim
bool GerenciadorCamarins::atualizar(int id, const string& nome, int artistaId) {
    Camarim* camarim = buscarPorId(id);
    
    if (camarim == nullptr) {
        throw CamarimException("Camarim com ID " + to_string(id) + " não encontrado");
    }
    
    camarim->setNome(nome);
    camarim->setArtistaId(artistaId);
    
    return true;
}
