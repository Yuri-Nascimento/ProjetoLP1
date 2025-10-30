/**
 * @file pedido.cpp
 * @brief Implementação da classe Pedido e GerenciadorPedidos
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

#include "pedido.h"
#include "excecoes.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

// ==================== Classe Pedido ====================

// Construtor padrão
Pedido::Pedido() : id(0), camarimId(0), nomeArtista(""), atendido(false) {}

// Construtor parametrizado
Pedido::Pedido(int id, int camarimId, const string& nomeArtista)
    : id(id), camarimId(camarimId), nomeArtista(nomeArtista), atendido(false) {}

// Destrutor
Pedido::~Pedido() {}

// Getters
int Pedido::getId() const {
    return id;
}

int Pedido::getCamarimId() const {
    return camarimId;
}

string Pedido::getNomeArtista() const {
    return nomeArtista;
}

bool Pedido::isAtendido() const {
    return atendido;
}

// Setters
void Pedido::setId(int id) {
    if (id < 0) {
        throw ValidacaoException("ID do pedido inválido");
    }
    this->id = id;
}

void Pedido::setCamarimId(int camarimId) {
    if (camarimId < 0) {
        throw ValidacaoException("ID do camarim inválido");
    }
    this->camarimId = camarimId;
}

void Pedido::setNomeArtista(const string& nomeArtista) {
    if (nomeArtista.empty()) {
        throw ValidacaoException("Nome do artista não pode ser vazio");
    }
    this->nomeArtista = nomeArtista;
}

void Pedido::setAtendido(bool atendido) {
    this->atendido = atendido;
}

// Adiciona item ao pedido
void Pedido::adicionarItem(int itemId, const string& nomeItem, int quantidade) {
    if (atendido) {
        throw PedidoException("Não é possível adicionar itens a um pedido já atendido");
    }
    
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
        itens[itemId] = ItemPedido(itemId, nomeItem, quantidade);
    }
}

// Remove item do pedido
bool Pedido::removerItem(int itemId) {
    if (atendido) {
        throw PedidoException("Não é possível remover itens de um pedido já atendido");
    }
    
    auto it = itens.find(itemId);
    
    if (it == itens.end()) {
        return false;
    }
    
    itens.erase(itemId);
    return true;
}

// Lista itens do pedido
vector<ItemPedido> Pedido::listarItens() const {
    vector<ItemPedido> lista;
    
    for (const auto& par : itens) {
        lista.push_back(par.second);
    }
    
    return lista;
}

// Marca pedido como atendido
void Pedido::marcarAtendido() {
    atendido = true;
}

// Exibe informações do pedido
string Pedido::exibir() const {
    stringstream ss;
    ss << "=== PEDIDO ===" << endl;
    ss << "ID: " << id << endl;
    ss << "Camarim ID: " << camarimId << endl;
    ss << "Artista: " << nomeArtista << endl;
    ss << "Status: " << (atendido ? "ATENDIDO" : "PENDENTE") << endl;
    ss << "\nItens:" << endl;
    
    if (itens.empty()) {
        ss << "  Nenhum item no pedido" << endl;
    } else {
        ss << left << setw(5) << "  ID" << setw(30) << "Nome" 
           << setw(10) << "Quantidade" << endl;
        ss << "  " << string(42, '-') << endl;
        
        for (const auto& par : itens) {
            const ItemPedido& item = par.second;
            ss << left << setw(5) << "  " + to_string(item.itemId)
               << setw(30) << item.nomeItem
               << setw(10) << item.quantidade << endl;
        }
    }
    
    return ss.str();
}

// Sobrecarga do operador <<
ostream& operator<<(ostream& os, const Pedido& pedido) {
    os << pedido.exibir();
    return os;
}

// ==================== Classe GerenciadorPedidos ====================

// Construtor
GerenciadorPedidos::GerenciadorPedidos() : proximoId(1) {}

// Cria novo pedido
int GerenciadorPedidos::criar(int camarimId, const string& nomeArtista) {
    if (camarimId < 0) {
        throw ValidacaoException("ID do camarim inválido");
    }
    
    if (nomeArtista.empty()) {
        throw ValidacaoException("Nome do artista não pode ser vazio");
    }
    
    Pedido novoPedido(proximoId, camarimId, nomeArtista);
    pedidos.push_back(novoPedido);
    
    return proximoId++;
}

// Busca pedido por ID
Pedido* GerenciadorPedidos::buscarPorId(int id) {
    for (auto& pedido : pedidos) {
        if (pedido.getId() == id) {
            return &pedido;
        }
    }
    return nullptr;
}

// Busca pedidos por camarim
vector<Pedido> GerenciadorPedidos::buscarPorCamarim(int camarimId) const {
    vector<Pedido> resultado;
    
    for (const auto& pedido : pedidos) {
        if (pedido.getCamarimId() == camarimId) {
            resultado.push_back(pedido);
        }
    }
    
    return resultado;
}

// Lista pedidos pendentes
vector<Pedido> GerenciadorPedidos::listarPendentes() const {
    vector<Pedido> pendentes;
    
    for (const auto& pedido : pedidos) {
        if (!pedido.isAtendido()) {
            pendentes.push_back(pedido);
        }
    }
    
    return pendentes;
}

// Remove pedido
bool GerenciadorPedidos::remover(int id) {
    auto it = remove_if(pedidos.begin(), pedidos.end(),
                       [id](const Pedido& p) { return p.getId() == id; });
    
    if (it != pedidos.end()) {
        pedidos.erase(it, pedidos.end());
        return true;
    }
    return false;
}

// Lista todos os pedidos
vector<Pedido> GerenciadorPedidos::listar() const {
    return pedidos;
}
