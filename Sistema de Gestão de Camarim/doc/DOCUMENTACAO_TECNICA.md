# Documentação Técnica - Sistema de Gestão de Camarim

## 📚 Índice
1. [Visão Geral](#visão-geral)
2. [Arquitetura do Sistema](#arquitetura-do-sistema)
3. [Classes e Hierarquia](#classes-e-hierarquia)
4. [Funcionalidades Implementadas](#funcionalidades-implementadas)
5. [Tratamento de Exceções](#tratamento-de-exceções)
6. [Exemplos de Uso](#exemplos-de-uso)

---

## 🎯 Visão Geral

Sistema completo de gestão de camarins desenvolvido em C++ com aplicação de conceitos avançados de Programação Orientada a Objetos (POO).

### Requisitos Atendidos
- ✅ **8+ Classes**: 8 classes principais + 11 gerenciadoras + 11 exceções
- ✅ **Encapsulamento Total**: Atributos privados/protected
- ✅ **Herança**: 2 hierarquias (Pessoa e ExcecaoBase)
- ✅ **Polimorfismo**: Métodos virtuais sobrescritos
- ✅ **CRUD Completo**: Para 7 entidades principais
- ✅ **Sobrecarga de Operadores**: `<<` implementado
- ✅ **Exceções Personalizadas**: 11 classes de exceção
- ✅ **Validação com Exceções**: Todas as operações validadas
- ✅ **Testes Automatizados**: Framework doctest

---

## 🏗️ Arquitetura do Sistema

### Camadas da Aplicação

```
┌─────────────────────────────────────┐
│     Interface do Usuário (main.cpp) │
├─────────────────────────────────────┤
│   Camada de Negócio (Gerenciadores) │
├─────────────────────────────────────┤
│      Camada de Entidades (Models)   │
├─────────────────────────────────────┤
│    Camada de Exceções (Validação)   │
└─────────────────────────────────────┘
```

### Estrutura de Diretórios

```
Sistema de Gestão de Camarim/
├── header/          # Arquivos .h (interfaces)
│   ├── pessoa.h
│   ├── usuario.h
│   ├── artista.h
│   ├── item.h
│   ├── estoque.h
│   ├── camarim.h
│   ├── pedido.h
│   ├── listacompras.h
│   └── excecoes.h
├── src/             # Arquivos .cpp (implementações)
│   ├── pessoa.cpp
│   ├── usuario.cpp
│   ├── artista.cpp
│   ├── item.cpp
│   ├── estoque.cpp
│   ├── camarim.cpp
│   ├── pedido.cpp
│   ├── listacompras.cpp
│   └── main.cpp
├── test/            # Testes unitários
│   └── teste.cpp
├── lib/             # Bibliotecas externas
│   └── doctest.h
├── bin/             # Executáveis compilados
├── doc/             # Documentação adicional
├── diagrama.md      # Diagrama UML
├── makefile         # Build script (Linux/Mac)
├── compile.ps1      # Build script (Windows)
└── test.ps1         # Test script (Windows)
```

---

## 📦 Classes e Hierarquia

### 1. Hierarquia de Pessoa (Polimorfismo)

```cpp
/**
 * Classe Base Abstrata
 */
class Pessoa {
protected:
    int id;
    string nome;
    
public:
    virtual string exibir() const = 0;  // Método virtual puro
    virtual ~Pessoa();
    // Getters e Setters...
};

/**
 * Classe Derivada 1
 */
class Usuario : public Pessoa {
private:
    string login;
    string senha;
    
public:
    string exibir() const override;  // Implementação polimórfica
    bool validarCredenciais(const string& login, const string& senha) const;
    // Métodos específicos...
};

/**
 * Classe Derivada 2
 */
class Artista : public Pessoa {
private:
    int camarimId;
    
public:
    string exibir() const override;  // Implementação polimórfica
    // Métodos específicos...
};
```

#### Demonstração de Polimorfismo:
```cpp
// Polimorfismo em ação
Pessoa* pessoa1 = new Usuario(1, "João", "joao", "senha");
Pessoa* pessoa2 = new Artista(2, "Madonna", 1);

cout << pessoa1->exibir();  // Chama Usuario::exibir()
cout << pessoa2->exibir();  // Chama Artista::exibir()

delete pessoa1;
delete pessoa2;
```

### 2. Hierarquia de Exceções

```cpp
/**
 * Classe Base de Exceções
 */
class ExcecaoBase : public exception {
protected:
    string mensagem;
    
public:
    virtual const char* what() const noexcept override;
};

// Exceções Derivadas
class ValidacaoException : public ExcecaoBase { /* ... */ };
class UsuarioNaoEncontradoException : public ExcecaoBase { /* ... */ };
class EstoqueInsuficienteException : public EstoqueException { /* ... */ };
// ... outras exceções
```

### 3. Classes de Entidades

#### Item
```cpp
class Item {
private:
    int id;
    string nome;
    double preco;
    
public:
    // CRUD através de GerenciadorItens
    // Sobrecarga de operador <<
    friend ostream& operator<<(ostream& os, const Item& item);
};
```

#### Estoque
```cpp
class Estoque {
private:
    map<int, ItemEstoque> itens;
    
public:
    void adicionarItem(int itemId, const string& nomeItem, int quantidade);
    bool removerItem(int itemId, int quantidade);
    bool verificarDisponibilidade(int itemId, int quantidade) const;
    // Validações lançam exceções
};
```

#### Camarim
```cpp
class Camarim {
private:
    int id;
    string nome;
    int artistaId;
    map<int, ItemCamarim> itens;
    
public:
    void inserirItem(int itemId, const string& nomeItem, int quantidade);
    bool removerItem(int itemId, int quantidade);
    int calcularTotalItens() const;
};
```

### 4. Classes Gerenciadoras (CRUD)

Todas as entidades possuem uma classe gerenciadora:

```cpp
class GerenciadorUsuarios {
private:
    vector<Usuario> usuarios;
    int proximoId;
    
public:
    int cadastrar(const string& nome, const string& login, const string& senha);
    Usuario* buscarPorId(int id);
    bool remover(int id);
    vector<Usuario> listar() const;
    bool atualizar(int id, const string& nome, const string& login, const string& senha);
};
```

**Gerenciadores implementados:**
- GerenciadorUsuarios
- GerenciadorArtistas
- GerenciadorItens
- GerenciadorCamarins
- GerenciadorPedidos
- GerenciadorListaCompras

---

## ⚡ Funcionalidades Implementadas

### 1. Gestão de Usuários
- ✅ Cadastrar usuário com validação de login único
- ✅ Autenticação de credenciais
- ✅ Buscar por ID ou login
- ✅ Atualizar dados
- ✅ Remover usuário
- ✅ Listar todos os usuários

### 2. Gestão de Artistas
- ✅ Cadastrar artista vinculado a camarim
- ✅ Buscar por ID ou por camarim
- ✅ Atualizar dados
- ✅ Remover artista
- ✅ Listar todos os artistas

### 3. Gestão de Itens
- ✅ Cadastrar item com preço
- ✅ Buscar por ID ou nome
- ✅ Validação de nome único
- ✅ Atualizar dados
- ✅ Remover item
- ✅ Listar todos os itens

### 4. Gestão de Estoque
- ✅ Adicionar itens ao estoque
- ✅ Remover itens com validação de quantidade
- ✅ Verificar disponibilidade
- ✅ Consultar quantidade
- ✅ Atualizar quantidades
- ✅ Listar estoque completo

### 5. Gestão de Camarins
- ✅ Criar camarim para artista
- ✅ Adicionar itens ao camarim
- ✅ Remover itens
- ✅ Calcular total de itens
- ✅ Listar itens do camarim
- ✅ Buscar por artista

### 6. Gestão de Pedidos
- ✅ Criar pedido para camarim
- ✅ Adicionar itens ao pedido
- ✅ Remover itens
- ✅ Marcar pedido como atendido
- ✅ Listar pedidos pendentes
- ✅ Buscar por camarim

### 7. Lista de Compras
- ✅ Criar lista de compras
- ✅ Adicionar itens com preço
- ✅ Calcular total automaticamente
- ✅ Atualizar quantidades
- ✅ Remover itens
- ✅ Limpar lista

---

## 🛡️ Tratamento de Exceções

### Sistema de Validação

Todas as operações críticas possuem validação com exceções:

```cpp
// Exemplo 1: Validação de entrada
void Usuario::setLogin(const string& login) {
    if (login.empty()) {
        throw ValidacaoException("Login não pode ser vazio");
    }
    if (login.length() < 3) {
        throw ValidacaoException("Login deve ter pelo menos 3 caracteres");
    }
    this->login = login;
}

// Exemplo 2: Validação de negócio
bool Estoque::removerItem(int itemId, int quantidade) {
    if (itens.find(itemId) == itens.end()) {
        throw EstoqueException("Item não encontrado no estoque");
    }
    
    if (itens[itemId].quantidade < quantidade) {
        throw EstoqueInsuficienteException(
            "Quantidade insuficiente. Disponível: " + 
            to_string(itens[itemId].quantidade)
        );
    }
    
    // Operação segura...
}
```

### Hierarquia de Exceções

```
ExcecaoBase
├── ValidacaoException          (Erros de validação de dados)
├── UsuarioNaoEncontradoException
├── UsuarioJaExisteException
├── ArtistaException
├── ItemException
├── EstoqueException
│   └── EstoqueInsuficienteException
├── CamarimException
├── PedidoException
└── ListaComprasException
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Cadastrar e Autenticar Usuário

```cpp
try {
    GerenciadorUsuarios gerenciador;
    
    // Cadastrar usuário
    int id = gerenciador.cadastrar("João Silva", "joao", "senha123");
    cout << "Usuário cadastrado com ID: " << id << endl;
    
    // Buscar e autenticar
    Usuario* usuario = gerenciador.buscarPorLogin("joao");
    if (usuario && usuario->validarCredenciais("joao", "senha123")) {
        cout << "Autenticação bem-sucedida!" << endl;
        cout << *usuario << endl;  // Sobrecarga do operador <<
    }
    
} catch (const UsuarioJaExisteException& e) {
    cerr << "Erro: " << e.what() << endl;
} catch (const ValidacaoException& e) {
    cerr << "Erro de validação: " << e.what() << endl;
} catch (const ExcecaoBase& e) {
    cerr << "Erro: " << e.what() << endl;
}
```

### Exemplo 2: Gerenciar Estoque

```cpp
try {
    Estoque estoque;
    
    // Adicionar itens
    estoque.adicionarItem(1, "Água Mineral", 100);
    estoque.adicionarItem(2, "Refrigerante", 50);
    
    // Verificar disponibilidade
    if (estoque.verificarDisponibilidade(1, 20)) {
        estoque.removerItem(1, 20);
        cout << "20 águas removidas do estoque" << endl;
    }
    
    // Exibir estoque
    cout << estoque << endl;  // Sobrecarga do operador <<
    
} catch (const EstoqueInsuficienteException& e) {
    cerr << "Estoque insuficiente: " << e.what() << endl;
} catch (const EstoqueException& e) {
    cerr << "Erro no estoque: " << e.what() << endl;
}
```

### Exemplo 3: Criar Pedido e Lista de Compras

```cpp
try {
    GerenciadorPedidos gerPedidos;
    GerenciadorListaCompras gerLista;
    
    // Criar pedido
    int pedidoId = gerPedidos.criar(1, "Madonna");
    Pedido* pedido = gerPedidos.buscarPorId(pedidoId);
    
    // Adicionar itens ao pedido
    pedido->adicionarItem(1, "Água", 50);
    pedido->adicionarItem(2, "Champagne", 10);
    
    // Criar lista de compras
    int listaId = gerLista.criar("Compras para Show");
    ListaCompras* lista = gerLista.buscarPorId(listaId);
    
    // Adicionar itens com preços
    lista->adicionarItem(1, "Água", 50, 2.50);
    lista->adicionarItem(2, "Champagne", 10, 150.00);
    
    // Calcular total
    double total = lista->calcularTotal();
    cout << "Total da compra: R$ " << total << endl;
    
    // Marcar pedido como atendido
    pedido->marcarAtendido();
    
} catch (const PedidoException& e) {
    cerr << "Erro no pedido: " << e.what() << endl;
} catch (const ValidacaoException& e) {
    cerr << "Erro de validação: " << e.what() << endl;
}
```

### Exemplo 4: Polimorfismo com Pessoa

```cpp
void exibirPessoa(const Pessoa& pessoa) {
    // Polimorfismo: chama o método apropriado
    cout << pessoa.exibir() << endl;
}

int main() {
    Usuario usuario(1, "João", "joao", "senha");
    Artista artista(2, "Madonna", 1);
    
    // Polimorfismo em ação
    exibirPessoa(usuario);  // Chama Usuario::exibir()
    exibirPessoa(artista);  // Chama Artista::exibir()
    
    // Sobrecarga de operador
    cout << usuario << endl;
    cout << artista << endl;
    
    return 0;
}
```

---

## 🧪 Testes Automatizados

O sistema possui cobertura de testes usando doctest:

```bash
# Executar testes
.\test.ps1  # Windows
make run-test  # Linux/Mac
```

**Categorias de testes:**
- ✅ Testes de criação e inicialização
- ✅ Testes de validação e exceções
- ✅ Testes de operações CRUD
- ✅ Testes de polimorfismo
- ✅ Testes de sobrecarga de operadores
- ✅ Testes de regras de negócio

---

## 📝 Conclusão

Este sistema demonstra a aplicação completa dos conceitos de POO:

1. **Encapsulamento**: Proteção e validação de dados
2. **Herança**: Reutilização de código e hierarquias
3. **Polimorfismo**: Flexibilidade e extensibilidade
4. **Abstração**: Classes base abstratas
5. **Tratamento de Exceções**: Robustez e confiabilidade
6. **SOLID Principles**: Design orientado a objetos
7. **Clean Code**: Documentação e organização

**Desenvolvido para LP1 - IMD/UFRN**

**Autores:**
- Fábio Augusto Vieira de Sales Vila
- Jerônimo Rafael Bezerra Filho
- Yuri Wendel do Nascimento
