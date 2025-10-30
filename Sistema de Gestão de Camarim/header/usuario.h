/**
 * @file usuario.h
 * @brief Definição da classe Usuario (herda de Pessoa)
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Implementa herança da classe base Pessoa e adiciona
 * funcionalidades específicas para usuários do sistema.
 */

#ifndef USUARIO_H
#define USUARIO_H

#include "pessoa.h"
#include <vector>

/**
 * @class Usuario
 * @brief Representa um usuário do sistema com credenciais de acesso
 * 
 * Herda de Pessoa e adiciona funcionalidades de autenticação.
 */
class Usuario : public Pessoa {
private:
    string login;     ///< Login de acesso ao sistema
    string senha;     ///< Senha do usuário (idealmente seria hash)
    
public:
    /**
     * @brief Construtor padrão
     */
    Usuario();
    
    /**
     * @brief Construtor parametrizado completo
     * @param id Identificador do usuário
     * @param nome Nome completo do usuário
     * @param login Login de acesso
     * @param senha Senha de acesso
     */
    Usuario(int id, const string& nome, const string& login, const string& senha);
    
    /**
     * @brief Destrutor
     */
    ~Usuario();
    
    // Getters
    string getLogin() const;
    string getSenha() const;
    
    // Setters com validação
    void setLogin(const string& login);
    void setSenha(const string& senha);
    
    /**
     * @brief Valida credenciais do usuário
     * @param login Login a validar
     * @param senha Senha a validar
     * @return true se credenciais válidas, false caso contrário
     */
    bool validarCredenciais(const string& login, const string& senha) const;
    
    /**
     * @brief Implementação do método virtual exibir (polimorfismo)
     * @return String formatada com informações do usuário
     */
    string exibir() const override;
};

/**
 * @class GerenciadorUsuarios
 * @brief Gerencia operações CRUD de usuários
 */
class GerenciadorUsuarios {
private:
    vector<Usuario> usuarios;  ///< Lista de usuários cadastrados
    int proximoId;             ///< Próximo ID disponível
    
public:
    /**
     * @brief Construtor
     */
    GerenciadorUsuarios();
    
    /**
     * @brief Cadastra novo usuário
     * @param nome Nome do usuário
     * @param login Login do usuário
     * @param senha Senha do usuário
     * @return ID do usuário cadastrado
     */
    int cadastrar(const string& nome, const string& login, const string& senha);
    
    /**
     * @brief Busca usuário por ID
     * @param id ID do usuário
     * @return Ponteiro para o usuário ou nullptr se não encontrado
     */
    Usuario* buscarPorId(int id);
    
    /**
     * @brief Busca usuário por login
     * @param login Login do usuário
     * @return Ponteiro para o usuário ou nullptr se não encontrado
     */
    Usuario* buscarPorLogin(const string& login);
    
    /**
     * @brief Remove usuário por ID
     * @param id ID do usuário
     * @return true se removido com sucesso, false caso contrário
     */
    bool remover(int id);
    
    /**
     * @brief Lista todos os usuários
     * @return Vector com todos os usuários
     */
    vector<Usuario> listar() const;
    
    /**
     * @brief Atualiza dados de um usuário
     * @param id ID do usuário
     * @param nome Novo nome
     * @param login Novo login
     * @param senha Nova senha
     * @return true se atualizado com sucesso
     */
    bool atualizar(int id, const string& nome, const string& login, const string& senha);
};

#endif // USUARIO_H
