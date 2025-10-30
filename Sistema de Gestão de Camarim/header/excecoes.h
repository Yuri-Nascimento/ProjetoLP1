/**
 * @file excecoes.h
 * @brief Definição de exceções personalizadas do sistema
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Este arquivo contém todas as exceções personalizadas utilizadas
 * no sistema de gestão de camarim, implementando tratamento de erros
 * conforme requisitos do projeto.
 */

#ifndef EXCECOES_H
#define EXCECOES_H

#include <exception>
#include <string>

using namespace std;

/**
 * @class ExcecaoBase
 * @brief Classe base para todas as exceções do sistema
 */
class ExcecaoBase : public exception {
protected:
    string mensagem;  ///< Mensagem de erro
    
public:
    /**
     * @brief Construtor com mensagem
     * @param msg Mensagem de erro
     */
    explicit ExcecaoBase(const string& msg) : mensagem(msg) {}
    
    /**
     * @brief Retorna a mensagem de erro
     * @return Mensagem de erro
     */
    virtual const char* what() const noexcept override {
        return mensagem.c_str();
    }
    
    /**
     * @brief Destrutor virtual
     */
    virtual ~ExcecaoBase() noexcept {}
};

/**
 * @class ValidacaoException
 * @brief Exceção para erros de validação de dados
 */
class ValidacaoException : public ExcecaoBase {
public:
    explicit ValidacaoException(const string& msg) 
        : ExcecaoBase("Erro de Validação: " + msg) {}
};

/**
 * @class UsuarioNaoEncontradoException
 * @brief Exceção quando usuário não é encontrado
 */
class UsuarioNaoEncontradoException : public ExcecaoBase {
public:
    explicit UsuarioNaoEncontradoException(const string& msg)
        : ExcecaoBase("Usuário não encontrado: " + msg) {}
};

/**
 * @class UsuarioJaExisteException
 * @brief Exceção quando usuário já existe no sistema
 */
class UsuarioJaExisteException : public ExcecaoBase {
public:
    explicit UsuarioJaExisteException(const string& msg)
        : ExcecaoBase("Usuário já existe: " + msg) {}
};

/**
 * @class ArtistaException
 * @brief Exceção relacionada a operações com artistas
 */
class ArtistaException : public ExcecaoBase {
public:
    explicit ArtistaException(const string& msg)
        : ExcecaoBase("Erro com Artista: " + msg) {}
};

/**
 * @class ItemException
 * @brief Exceção relacionada a operações com itens
 */
class ItemException : public ExcecaoBase {
public:
    explicit ItemException(const string& msg)
        : ExcecaoBase("Erro com Item: " + msg) {}
};

/**
 * @class EstoqueException
 * @brief Exceção relacionada a operações de estoque
 */
class EstoqueException : public ExcecaoBase {
public:
    explicit EstoqueException(const string& msg)
        : ExcecaoBase("Erro de Estoque: " + msg) {}
};

/**
 * @class EstoqueInsuficienteException
 * @brief Exceção quando não há quantidade suficiente em estoque
 */
class EstoqueInsuficienteException : public EstoqueException {
public:
    explicit EstoqueInsuficienteException(const string& msg)
        : EstoqueException("Estoque insuficiente: " + msg) {}
};

/**
 * @class CamarimException
 * @brief Exceção relacionada a operações com camarins
 */
class CamarimException : public ExcecaoBase {
public:
    explicit CamarimException(const string& msg)
        : ExcecaoBase("Erro com Camarim: " + msg) {}
};

/**
 * @class PedidoException
 * @brief Exceção relacionada a operações com pedidos
 */
class PedidoException : public ExcecaoBase {
public:
    explicit PedidoException(const string& msg)
        : ExcecaoBase("Erro com Pedido: " + msg) {}
};

/**
 * @class ListaComprasException
 * @brief Exceção relacionada a operações com lista de compras
 */
class ListaComprasException : public ExcecaoBase {
public:
    explicit ListaComprasException(const string& msg)
        : ExcecaoBase("Erro com Lista de Compras: " + msg) {}
};

#endif // EXCECOES_H
