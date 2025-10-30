/**
 * @file item.h
 * @brief Definição da classe Item
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Classe que representa itens do sistema (produtos)
 * com encapsulamento completo e sobrecarga de operadores.
 */

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @class Item
 * @brief Representa um item/produto no sistema
 * 
 * Implementa encapsulamento completo com atributos privados,
 * getters/setters e sobrecarga do operador <<.
 */
class Item {
private:
    int id;           ///< Identificador único do item
    string nome;      ///< Nome do item
    double preco;     ///< Preço unitário do item
    
public:
    /**
     * @brief Construtor padrão
     */
    Item();
    
    /**
     * @brief Construtor parametrizado
     * @param id Identificador do item
     * @param nome Nome do item
     * @param preco Preço do item
     */
    Item(int id, const string& nome, double preco);
    
    /**
     * @brief Destrutor
     */
    ~Item();
    
    // Getters
    int getId() const;
    string getNome() const;
    double getPreco() const;
    
    // Setters com validação
    void setId(int id);
    void setNome(const string& nome);
    void setPreco(double preco);
    
    /**
     * @brief Exibe informações do item
     * @return String formatada com informações do item
     */
    string exibir() const;
    
    /**
     * @brief Sobrecarga do operador << para exibição
     * @param os Stream de saída
     * @param item Item a ser exibido
     * @return Stream de saída
     */
    friend ostream& operator<<(ostream& os, const Item& item);
    
    /**
     * @brief Sobrecarga do operador == para comparação
     * @param outro Item a comparar
     * @return true se itens são iguais
     */
    bool operator==(const Item& outro) const;
};

/**
 * @class GerenciadorItens
 * @brief Gerencia operações CRUD de itens
 */
class GerenciadorItens {
private:
    vector<Item> itens;    ///< Lista de itens cadastrados
    int proximoId;         ///< Próximo ID disponível
    
public:
    /**
     * @brief Construtor
     */
    GerenciadorItens();
    
    /**
     * @brief Cadastra novo item
     * @param nome Nome do item
     * @param preco Preço do item
     * @return ID do item cadastrado
     */
    int cadastrar(const string& nome, double preco);
    
    /**
     * @brief Busca item por ID
     * @param id ID do item
     * @return Ponteiro para o item ou nullptr se não encontrado
     */
    Item* buscarPorId(int id);
    
    /**
     * @brief Busca item por nome
     * @param nome Nome do item
     * @return Ponteiro para o item ou nullptr se não encontrado
     */
    Item* buscarPorNome(const string& nome);
    
    /**
     * @brief Remove item por ID
     * @param id ID do item
     * @return true se removido com sucesso
     */
    bool remover(int id);
    
    /**
     * @brief Lista todos os itens
     * @return Vector com todos os itens
     */
    vector<Item> listar() const;
    
    /**
     * @brief Atualiza dados de um item
     * @param id ID do item
     * @param nome Novo nome
     * @param preco Novo preço
     * @return true se atualizado com sucesso
     */
    bool atualizar(int id, const string& nome, double preco);
};

#endif // ITEM_H
