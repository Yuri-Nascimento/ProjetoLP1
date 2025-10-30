/**
 * @file artista.cpp
 * @brief Implementação da classe Artista e GerenciadorArtistas
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

#include "artista.h"
#include "excecoes.h"
#include <algorithm>
#include <sstream>

// ==================== Classe Artista ====================

// Construtor padrão
Artista::Artista() : Pessoa(), camarimId(0) {}

// Construtor parametrizado
Artista::Artista(int id, const string& nome, int camarimId)
    : Pessoa(id, nome), camarimId(camarimId) {}

// Destrutor
Artista::~Artista() {}

// Getters
int Artista::getCamarimId() const {
    return camarimId;
}

// Setters
void Artista::setCamarimId(int camarimId) {
    if (camarimId < 0) {
        throw ValidacaoException("ID de camarim inválido");
    }
    this->camarimId = camarimId;
}

// Implementação do método virtual exibir (polimorfismo)
string Artista::exibir() const {
    stringstream ss;
    ss << "Artista [ID: " << id << ", Nome: " << nome 
       << ", Camarim ID: " << camarimId << "]";
    return ss.str();
}

// ==================== Classe GerenciadorArtistas ====================

// Construtor
GerenciadorArtistas::GerenciadorArtistas() : proximoId(1) {}

// Cadastra novo artista
int GerenciadorArtistas::cadastrar(const string& nome, int camarimId) {
    // Validações
    if (nome.empty()) {
        throw ValidacaoException("Nome do artista não pode ser vazio");
    }
    
    if (camarimId < 0) {
        throw ValidacaoException("ID de camarim inválido");
    }
    
    Artista novoArtista(proximoId, nome, camarimId);
    artistas.push_back(novoArtista);
    
    return proximoId++;
}

// Busca artista por ID
Artista* GerenciadorArtistas::buscarPorId(int id) {
    for (auto& artista : artistas) {
        if (artista.getId() == id) {
            return &artista;
        }
    }
    return nullptr;
}

// Busca artistas por camarim
vector<Artista> GerenciadorArtistas::buscarPorCamarim(int camarimId) const {
    vector<Artista> resultado;
    
    for (const auto& artista : artistas) {
        if (artista.getCamarimId() == camarimId) {
            resultado.push_back(artista);
        }
    }
    
    return resultado;
}

// Remove artista por ID
bool GerenciadorArtistas::remover(int id) {
    auto it = remove_if(artistas.begin(), artistas.end(),
                       [id](const Artista& a) { return a.getId() == id; });
    
    if (it != artistas.end()) {
        artistas.erase(it, artistas.end());
        return true;
    }
    return false;
}

// Lista todos os artistas
vector<Artista> GerenciadorArtistas::listar() const {
    return artistas;
}

// Atualiza dados de um artista
bool GerenciadorArtistas::atualizar(int id, const string& nome, int camarimId) {
    Artista* artista = buscarPorId(id);
    
    if (artista == nullptr) {
        throw ArtistaException("Artista com ID " + to_string(id) + " não encontrado");
    }
    
    artista->setNome(nome);
    artista->setCamarimId(camarimId);
    
    return true;
}
