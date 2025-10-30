/**
 * @file usuario.cpp
 * @brief Implementação da classe Usuario e GerenciadorUsuarios
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

#include "usuario.h"
#include "excecoes.h"
#include <algorithm>
#include <sstream>

// ==================== Classe Usuario ====================

// Construtor padrão
Usuario::Usuario() : Pessoa(), login(""), senha("") {}

// Construtor parametrizado
Usuario::Usuario(int id, const string& nome, const string& login, const string& senha)
    : Pessoa(id, nome), login(login), senha(senha) {}

// Destrutor
Usuario::~Usuario() {}

// Getters
string Usuario::getLogin() const {
    return login;
}

string Usuario::getSenha() const {
    return senha;
}

// Setters com validação
void Usuario::setLogin(const string& login) {
    if (login.empty()) {
        throw ValidacaoException("Login não pode ser vazio");
    }
    if (login.length() < 3) {
        throw ValidacaoException("Login deve ter pelo menos 3 caracteres");
    }
    this->login = login;
}

void Usuario::setSenha(const string& senha) {
    if (senha.empty()) {
        throw ValidacaoException("Senha não pode ser vazia");
    }
    if (senha.length() < 4) {
        throw ValidacaoException("Senha deve ter pelo menos 4 caracteres");
    }
    this->senha = senha;
}

// Valida credenciais
bool Usuario::validarCredenciais(const string& login, const string& senha) const {
    return (this->login == login && this->senha == senha);
}

// Implementação do método virtual exibir (polimorfismo)
string Usuario::exibir() const {
    stringstream ss;
    ss << "Usuario [ID: " << id << ", Nome: " << nome 
       << ", Login: " << login << "]";
    return ss.str();
}

// ==================== Classe GerenciadorUsuarios ====================

// Construtor
GerenciadorUsuarios::GerenciadorUsuarios() : proximoId(1) {}

// Cadastra novo usuário
int GerenciadorUsuarios::cadastrar(const string& nome, const string& login, const string& senha) {
    // Validações
    if (nome.empty()) {
        throw ValidacaoException("Nome não pode ser vazio");
    }
    
    // Verifica se login já existe
    if (buscarPorLogin(login) != nullptr) {
        throw UsuarioJaExisteException("Login já está em uso: " + login);
    }
    
    Usuario novoUsuario(proximoId, nome, login, senha);
    usuarios.push_back(novoUsuario);
    
    return proximoId++;
}

// Busca usuário por ID
Usuario* GerenciadorUsuarios::buscarPorId(int id) {
    for (auto& usuario : usuarios) {
        if (usuario.getId() == id) {
            return &usuario;
        }
    }
    return nullptr;
}

// Busca usuário por login
Usuario* GerenciadorUsuarios::buscarPorLogin(const string& login) {
    for (auto& usuario : usuarios) {
        if (usuario.getLogin() == login) {
            return &usuario;
        }
    }
    return nullptr;
}

// Remove usuário por ID
bool GerenciadorUsuarios::remover(int id) {
    auto it = remove_if(usuarios.begin(), usuarios.end(),
                       [id](const Usuario& u) { return u.getId() == id; });
    
    if (it != usuarios.end()) {
        usuarios.erase(it, usuarios.end());
        return true;
    }
    return false;
}

// Lista todos os usuários
vector<Usuario> GerenciadorUsuarios::listar() const {
    return usuarios;
}

// Atualiza dados de um usuário
bool GerenciadorUsuarios::atualizar(int id, const string& nome, const string& login, const string& senha) {
    Usuario* usuario = buscarPorId(id);
    
    if (usuario == nullptr) {
        throw UsuarioNaoEncontradoException("Usuário com ID " + to_string(id) + " não encontrado");
    }
    
    // Verifica se novo login já está em uso por outro usuário
    Usuario* usuarioComLogin = buscarPorLogin(login);
    if (usuarioComLogin != nullptr && usuarioComLogin->getId() != id) {
        throw UsuarioJaExisteException("Login já está em uso: " + login);
    }
    
    usuario->setNome(nome);
    usuario->setLogin(login);
    usuario->setSenha(senha);
    
    return true;
}
