/**
 * @file pedido.h
 * @brief Definição da classe Pedido
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Gerencia pedidos de itens para camarins.
 */

#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

/**
 * @struct ItemPedido
 * @brief Representa um item em um pedido
 */
struct ItemPedido {
    int itemId;        ///< ID do item
    string nomeItem;   ///< Nome do item
    int quantidade;    ///< Quantidade solicitada
    
    ItemPedido() : itemId(0), nomeItem(""), quantidade(0) {}
    ItemPedido(int id, const string& nome, int qtd) 
        : itemId(id), nomeItem(nome), quantidade(qtd) {}
};

/**
 * @class Pedido
 * @brief Representa um pedido de itens para um camarim
 */
class Pedido {
private:
    int id;                         ///< ID do pedido
    int camarimId;                  ///< ID do camarim solicitante
    string nomeArtista;             ///< Nome do artista
    map<int, ItemPedido> itens;    ///< Map de itemId -> ItemPedido
    bool atendido;                  ///< Status do pedido
    
public:
    /**
     * @brief Construtor padrão
     */
    Pedido();
    
    /**
     * @brief Construtor parametrizado
     * @param id ID do pedido
     * @param camarimId ID do camarim
     * @param nomeArtista Nome do artista
     */
    Pedido(int id, int camarimId, const string& nomeArtista);
    
    /**
     * @brief Destrutor
     */
    ~Pedido();
    
    // Getters
    int getId() const;
    int getCamarimId() const;
    string getNomeArtista() const;
    bool isAtendido() const;
    
    // Setters
    void setId(int id);
    void setCamarimId(int camarimId);
    void setNomeArtista(const string& nomeArtista);
    void setAtendido(bool atendido);
    
    /**
     * @brief Adiciona item ao pedido
     * @param itemId ID do item
     * @param nomeItem Nome do item
     * @param quantidade Quantidade
     */
    void adicionarItem(int itemId, const string& nomeItem, int quantidade);
    
    /**
     * @brief Remove item do pedido
     * @param itemId ID do item
     * @return true se removido
     */
    bool removerItem(int itemId);
    
    /**
     * @brief Marca pedido como atendido
     */
    void marcarAtendido();
    
    /**
     * @brief Exibe informações do pedido
     * @return String formatada
     */
    string exibir() const;
    
    /**
     * @brief Sobrecarga do operador <<
     */
    friend ostream& operator<<(ostream& os, const Pedido& pedido);
};

/**
 * @class GerenciadorPedidos
 * @brief Gerencia operações CRUD de pedidos
 */
class GerenciadorPedidos {
private:
    vector<Pedido> pedidos;  ///< Lista de pedidos
    int proximoId;           ///< Próximo ID disponível
    
public:
    /**
     * @brief Construtor
     */
    GerenciadorPedidos();
    
    /**
     * @brief Cria novo pedido
     * @param camarimId ID do camarim
     * @param nomeArtista Nome do artista
     * @return ID do pedido criado
     */
    int criar(int camarimId, const string& nomeArtista);
    
    /**
     * @brief Busca pedido por ID
     * @param id ID do pedido
     * @return Ponteiro para o pedido ou nullptr
     */
    Pedido* buscarPorId(int id);
    
    /**
     * @brief Busca pedidos por camarim
     * @param camarimId ID do camarim
     * @return Vector com pedidos
     */
    vector<Pedido> buscarPorCamarim(int camarimId) const;
    
    /**
     * @brief Lista pedidos pendentes
     * @return Vector com pedidos não atendidos
     */
    vector<Pedido> listarPendentes() const;
    
    /**
     * @brief Remove pedido
     * @param id ID do pedido
     * @return true se removido
     */
    bool remover(int id);
    
    /**
     * @brief Lista todos os pedidos
     * @return Vector com todos os pedidos
     */
    vector<Pedido> listar() const;
};

#endif // PEDIDO_H
