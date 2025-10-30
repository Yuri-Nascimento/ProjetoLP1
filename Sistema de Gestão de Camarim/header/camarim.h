/**
 * @file camarim.h
 * @brief Definição da classe Camarim
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Gerencia os camarins e seus itens associados.
 */

#ifndef CAMARIM_H
#define CAMARIM_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

/**
 * @struct ItemCamarim
 * @brief Representa um item dentro de um camarim
 */
struct ItemCamarim {
    int itemId;        ///< ID do item
    string nomeItem;   ///< Nome do item
    int quantidade;    ///< Quantidade no camarim
    
    ItemCamarim() : itemId(0), nomeItem(""), quantidade(0) {}
    ItemCamarim(int id, const string& nome, int qtd) 
        : itemId(id), nomeItem(nome), quantidade(qtd) {}
};

/**
 * @class Camarim
 * @brief Representa um camarim com seus itens
 */
class Camarim {
private:
    int id;                          ///< ID do camarim
    string nome;                     ///< Nome do camarim
    int artistaId;                   ///< ID do artista associado
    map<int, ItemCamarim> itens;    ///< Map de itemId -> ItemCamarim
    
public:
    /**
     * @brief Construtor padrão
     */
    Camarim();
    
    /**
     * @brief Construtor parametrizado
     * @param id ID do camarim
     * @param nome Nome do camarim
     * @param artistaId ID do artista
     */
    Camarim(int id, const string& nome, int artistaId);
    
    /**
     * @brief Destrutor
     */
    ~Camarim();
    
    // Getters
    int getId() const;
    string getNome() const;
    int getArtistaId() const;
    
    // Setters
    void setId(int id);
    void setNome(const string& nome);
    void setArtistaId(int artistaId);
    
    /**
     * @brief Adiciona item ao camarim
     * @param itemId ID do item
     * @param nomeItem Nome do item
     * @param quantidade Quantidade
     */
    void inserirItem(int itemId, const string& nomeItem, int quantidade);
    
    /**
     * @brief Remove item do camarim
     * @param itemId ID do item
     * @param quantidade Quantidade a remover
     * @return true se removido com sucesso
     */
    bool removerItem(int itemId, int quantidade);
    
    /**
     * @brief Verifica se item existe no camarim
     * @param itemId ID do item
     * @return true se existe
     */
    bool contemItem(int itemId) const;
    
    /**
     * @brief Obtém quantidade de um item no camarim
     * @param itemId ID do item
     * @return Quantidade
     */
    int obterQuantidadeItem(int itemId) const;
    
    /**
     * @brief Lista todos os itens do camarim
     * @return Vector com itens
     */
    vector<ItemCamarim> listarItens() const;
    
    /**
     * @brief Calcula total de itens no camarim
     * @return Total de itens
     */
    int calcularTotalItens() const;
    
    /**
     * @brief Exibe informações do camarim
     * @return String formatada
     */
    string exibir() const;
    
    /**
     * @brief Sobrecarga do operador <<
     */
    friend ostream& operator<<(ostream& os, const Camarim& camarim);
};

/**
 * @class GerenciadorCamarins
 * @brief Gerencia operações CRUD de camarins
 */
class GerenciadorCamarins {
private:
    vector<Camarim> camarins;  ///< Lista de camarins
    int proximoId;             ///< Próximo ID disponível
    
public:
    /**
     * @brief Construtor
     */
    GerenciadorCamarins();
    
    /**
     * @brief Cadastra novo camarim
     * @param nome Nome do camarim
     * @param artistaId ID do artista
     * @return ID do camarim cadastrado
     */
    int cadastrar(const string& nome, int artistaId);
    
    /**
     * @brief Busca camarim por ID
     * @param id ID do camarim
     * @return Ponteiro para o camarim ou nullptr
     */
    Camarim* buscarPorId(int id);
    
    /**
     * @brief Busca camarim por artista
     * @param artistaId ID do artista
     * @return Ponteiro para o camarim ou nullptr
     */
    Camarim* buscarPorArtista(int artistaId);
    
    /**
     * @brief Remove camarim
     * @param id ID do camarim
     * @return true se removido
     */
    bool remover(int id);
    
    /**
     * @brief Lista todos os camarins
     * @return Vector com camarins
     */
    vector<Camarim> listar() const;
    
    /**
     * @brief Atualiza camarim
     * @param id ID do camarim
     * @param nome Novo nome
     * @param artistaId Novo ID de artista
     * @return true se atualizado
     */
    bool atualizar(int id, const string& nome, int artistaId);
};

#endif // CAMARIM_H