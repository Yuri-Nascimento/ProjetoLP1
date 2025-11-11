/**
 * @file estoque.h
 * @brief Definição da classe Estoque
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Gerencia o estoque de itens no sistema.
 */

#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "item.h"
#include <map>
#include <vector>

/**
 * @struct ItemEstoque
 * @brief Estrutura que representa um item no estoque
 */
struct ItemEstoque {
    int itemId;        ///< ID do item
    string nomeItem;   ///< Nome do item
    int quantidade;    ///< Quantidade em estoque
    
    ItemEstoque() : itemId(0), nomeItem(""), quantidade(0) {}
    ItemEstoque(int id, const string& nome, int qtd) 
        : itemId(id), nomeItem(nome), quantidade(qtd) {}
};

/**
 * @class Estoque
 * @brief Gerencia o estoque de itens
 */
class Estoque {
private:
    map<int, ItemEstoque> itens;  ///< Map de itemId -> ItemEstoque
    
public:
    /**
     * @brief Construtor
     */
    Estoque();
    
    /**
     * @brief Destrutor
     */
    ~Estoque();
    
    /**
     * @brief Adiciona item ao estoque
     * @param itemId ID do item
     * @param nomeItem Nome do item
     * @param quantidade Quantidade a adicionar
     */
    void adicionarItem(int itemId, const string& nomeItem, int quantidade);
    
    /**
     * @brief Remove quantidade de um item do estoque
     * @param itemId ID do item
     * @param quantidade Quantidade a remover
     * @return true se removido com sucesso
     */
    bool removerItem(int itemId, int quantidade);
    
    /**
     * @brief Verifica se há quantidade suficiente de um item
     * @param itemId ID do item
     * @param quantidade Quantidade desejada
     * @return true se há quantidade suficiente
     */
    bool verificarDisponibilidade(int itemId, int quantidade) const;
    
    /**
     * @brief Obtém quantidade de um item em estoque
     * @param itemId ID do item
     * @return Quantidade disponível
     */
    int obterQuantidade(int itemId) const;
    
    /**
     * @brief Lista todos os itens em estoque
     * @return Vector com itens do estoque
     */
    vector<ItemEstoque> listar() const;
    
    /**
     * @brief Atualiza quantidade de um item
     * @param itemId ID do item
     * @param novaQuantidade Nova quantidade
     */
    void atualizarQuantidade(int itemId, int novaQuantidade);
    
    /**
     * @brief Exibe informações do estoque
     * @return String formatada
     */
    string exibir() const;
    
    /**
     * @brief Sobrecarga do operador <<
     */
    friend ostream& operator<<(ostream& os, const Estoque& estoque);
};

#endif // ESTOQUE_H
