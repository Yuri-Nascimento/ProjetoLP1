/**
 * @file pessoa.cpp
 * @brief Implementação da classe Pessoa
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

#include "pessoa.h"

// Construtor padrão
Pessoa::Pessoa() : id(0), nome("") {}

// Construtor parametrizado
Pessoa::Pessoa(int id, const string& nome) : id(id), nome(nome) {}

// Destrutor virtual
Pessoa::~Pessoa() {}

// Getters
int Pessoa::getId() const {
    return id;
}

string Pessoa::getNome() const {
    return nome;
}

// Setters
void Pessoa::setId(int id) {
    this->id = id;
}

void Pessoa::setNome(const string& nome) {
    this->nome = nome;
}

// Sobrecarga do operador <<
ostream& operator<<(ostream& os, const Pessoa& pessoa) {
    os << pessoa.exibir();
    return os;
}
