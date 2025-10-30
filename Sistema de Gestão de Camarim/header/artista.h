/**
 * @file artista.h
 * @brief Definição da classe Artista (herda de Pessoa)
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Implementa herança da classe base Pessoa e adiciona
 * funcionalidades específicas para artistas.
 */

#ifndef ARTISTA_H
#define ARTISTA_H

#include "pessoa.h"
#include <vector>

/**
 * @class Artista
 * @brief Representa um artista com camarim associado
 * 
 * Herda de Pessoa e adiciona funcionalidades específicas para artistas.
 */
class Artista : public Pessoa {
private:
    int camarimId;    ///< ID do camarim associado ao artista
    
public:
    /**
     * @brief Construtor padrão
     */
    Artista();
    
    /**
     * @brief Construtor parametrizado
     * @param id Identificador do artista
     * @param nome Nome do artista
     * @param camarimId ID do camarim associado
     */
    Artista(int id, const string& nome, int camarimId);
    
    /**
     * @brief Destrutor
     */
    ~Artista();
    
    // Getters
    int getCamarimId() const;
    
    // Setters
    void setCamarimId(int camarimId);
    
    /**
     * @brief Implementação do método virtual exibir (polimorfismo)
     * @return String formatada com informações do artista
     */
    string exibir() const override;
};

/**
 * @class GerenciadorArtistas
 * @brief Gerencia operações CRUD de artistas
 */
class GerenciadorArtistas {
private:
    vector<Artista> artistas;  ///< Lista de artistas cadastrados
    int proximoId;             ///< Próximo ID disponível
    
public:
    /**
     * @brief Construtor
     */
    GerenciadorArtistas();
    
    /**
     * @brief Cadastra novo artista
     * @param nome Nome do artista
     * @param camarimId ID do camarim
     * @return ID do artista cadastrado
     */
    int cadastrar(const string& nome, int camarimId);
    
    /**
     * @brief Busca artista por ID
     * @param id ID do artista
     * @return Ponteiro para o artista ou nullptr se não encontrado
     */
    Artista* buscarPorId(int id);
    
    /**
     * @brief Busca artistas por camarim
     * @param camarimId ID do camarim
     * @return Vector com artistas do camarim
     */
    vector<Artista> buscarPorCamarim(int camarimId) const;
    
    /**
     * @brief Remove artista por ID
     * @param id ID do artista
     * @return true se removido com sucesso
     */
    bool remover(int id);
    
    /**
     * @brief Lista todos os artistas
     * @return Vector com todos os artistas
     */
    vector<Artista> listar() const;
    
    /**
     * @brief Atualiza dados de um artista
     * @param id ID do artista
     * @param nome Novo nome
     * @param camarimId Novo ID de camarim
     * @return true se atualizado com sucesso
     */
    bool atualizar(int id, const string& nome, int camarimId);
};

#endif // ARTISTA_H
