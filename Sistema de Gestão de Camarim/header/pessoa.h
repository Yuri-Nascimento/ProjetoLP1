/**
 * @file pessoa.h
 * @brief Definição da classe base Pessoa
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Esta classe serve como base para Usuario e Artista, implementando
 * herança e polimorfismo conforme requisitos do projeto.
 */

#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>

using namespace std;

/**
 * @class Pessoa
 * @brief Classe base abstrata que representa uma pessoa no sistema
 * 
 * Implementa conceitos de POO:
 * - Encapsulamento: atributos privados com getters/setters
 * - Herança: classe base para Usuario e Artista
 * - Polimorfismo: método virtual exibir()
 */
class Pessoa {
protected:
    int id;           ///< Identificador único da pessoa
    string nome;      ///< Nome completo da pessoa
    
public:
    /**
     * @brief Construtor padrão
     */
    Pessoa();
    
    /**
     * @brief Construtor parametrizado
     * @param id Identificador da pessoa
     * @param nome Nome da pessoa
     */
    Pessoa(int id, const string& nome);
    
    /**
     * @brief Destrutor virtual para suportar polimorfismo
     */
    virtual ~Pessoa();
    
    // Getters
    int getId() const;
    string getNome() const;
    
    // Setters
    void setId(int id);
    void setNome(const string& nome);
    
    /**
     * @brief Método virtual puro para exibir informações (polimorfismo)
     * @return String formatada com informações da pessoa
     */
    virtual string exibir() const = 0;
    
    /**
     * @brief Sobrecarga do operador << para exibição
     * @param os Stream de saída
     * @param pessoa Objeto Pessoa a ser exibido
     * @return Stream de saída
     */
    friend ostream& operator<<(ostream& os, const Pessoa& pessoa);
};

#endif // PESSOA_H
