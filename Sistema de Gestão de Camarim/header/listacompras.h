/**
 * @file listacompras.h
 * @brief Definição da classe ListaCompras
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Gerencia lista de compras consolidada de itens necessários.
 */

#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

/**
 * @struct ItemCompra
 * @brief Representa um item na lista de compras
 */
struct ItemCompra {
    int itemId;        ///< ID do item
    string nomeItem;   ///< Nome do item
    int quantidade;    ///< Quantidade necessária
    double preco;      ///< Preço unitário
    double subtotal;   ///< Subtotal (quantidade * preço)
    
    ItemCompra() : itemId(0), nomeItem(""), quantidade(0), preco(0.0), subtotal(0.0) {}
    ItemCompra(int id, const string& nome, int qtd, double preco) 
        : itemId(id), nomeItem(nome), quantidade(qtd), preco(preco), 
          subtotal(qtd * preco) {}
};

/**
 * @class ListaCompras
 * @brief Gerencia lista de compras consolidada
 */
class ListaCompras {
private:
    int id;                         ///< ID da lista
    string descricao;               ///< Descrição da lista
    map<int, ItemCompra> itens;    ///< Map de itemId -> ItemCompra
    
public:
    /**
     * @brief Construtor padrão
     */
    ListaCompras();
    
    /**
     * @brief Construtor parametrizado
     * @param id ID da lista
     * @param descricao Descrição da lista
     */
    ListaCompras(int id, const string& descricao);
    
    /**
     * @brief Destrutor
     */
    ~ListaCompras();
    
    // Getters
    int getId() const;
    string getDescricao() const;
    
    // Setters
    void setId(int id);
    void setDescricao(const string& descricao);
    
    /**
     * @brief Adiciona item à lista
     * @param itemId ID do item
     * @param nomeItem Nome do item
     * @param quantidade Quantidade
     * @param preco Preço unitário
     */
    void adicionarItem(int itemId, const string& nomeItem, int quantidade, double preco);
    
    /**
     * @brief Remove item da lista
     * @param itemId ID do item
     * @return true se removido
     */
    bool removerItem(int itemId);
    
    /**
     * @brief Atualiza quantidade de um item
     * @param itemId ID do item
     * @param quantidade Nova quantidade
     */
    void atualizarQuantidade(int itemId, int quantidade);
    
    /**
     * @brief Lista itens da compra
     * @return Vector com itens
     */
    vector<ItemCompra> listarItens() const;
    
    /**
     * @brief Calcula total da lista de compras
     * @return Valor total
     */
    double calcularTotal() const;
    
    /**
     * @brief Limpa toda a lista
     */
    void limpar();
    
    /**
     * @brief Exibe informações da lista
     * @return String formatada
     */
    string exibir() const;
    
    /**
     * @brief Sobrecarga do operador <<
     */
    friend ostream& operator<<(ostream& os, const ListaCompras& lista);
};

/**
 * @class GerenciadorListaCompras
 * @brief Gerencia operações CRUD de listas de compras
 */
class GerenciadorListaCompras {
private:
    vector<ListaCompras> listas;  ///< Lista de listas de compras
    int proximoId;                ///< Próximo ID disponível
    
public:
    /**
     * @brief Construtor
     */
    GerenciadorListaCompras();
    
    /**
     * @brief Cria nova lista de compras
     * @param descricao Descrição da lista
     * @return ID da lista criada
     */
    int criar(const string& descricao);
    
    /**
     * @brief Busca lista por ID
     * @param id ID da lista
     * @return Ponteiro para a lista ou nullptr
     */
    ListaCompras* buscarPorId(int id);
    
    /**
     * @brief Remove lista
     * @param id ID da lista
     * @return true se removido
     */
    bool remover(int id);
    
    /**
     * @brief Lista todas as listas de compras
     * @return Vector com listas
     */
    vector<ListaCompras> listar() const;
};

#endif // LISTACOMPRAS_H
