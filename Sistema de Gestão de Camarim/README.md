# Informações do Projeto

- **Instituição:** IMD
- **Disciplina:** LP1
- **Professor:** Prof. Jerffeson Gomes Dutra

  
## Atividade LP1 - Desenvolver uma aplicação funcional, utilizando os principais conceitos da programação orientada a objetos (POO). A aplicação deve conter um conjunto mínimo de funcionalidades que envolvam cadastro, consulta, alteração e remoção de dados (CRUD).

### ✅ **Requisitos Mínimos**
1. **8 Classes ✅**
   - Pessoa (classe base abstrata)
   - Usuario (herda de Pessoa)
   - Artista (herda de Pessoa)
   - Item
   - Estoque
   - Camarim
   - Pedido
   - ListaCompras
   - **+11 Classes Gerenciadoras** (GerenciadorUsuarios, GerenciadorArtistas, etc.)
   - **+11 Classes de Exceção** (ExcecaoBase, ValidacaoException, etc.)

2. **Encapsulamento de todas as entidades ✅**
   - Todos os atributos são privados/protected
   - Acesso via getters e setters com validação

3. **2 Heranças ✅**
   - Usuario herda de Pessoa
   - Artista herda de Pessoa
   - Todas as exceções herdam de ExcecaoBase

4. **Classes Bases Diferentes ✅**
   - Pessoa (base para Usuario e Artista)
   - ExcecaoBase (base para todas as exceções personalizadas)

5. **Min 2 Polimorfismos ✅**
   - Método virtual puro `exibir()` em Pessoa
   - Sobrescrito em Usuario e Artista
   - Método virtual `what()` nas exceções

6. **Criar, ler, atualizar e remover registros de 6 entidades ✅**
   - Usuario: CRUD completo
   - Artista: CRUD completo
   - Item: CRUD completo
   - Estoque: CRUD completo
   - Camarim: CRUD completo
   - Pedido: CRUD completo
   - ListaCompras: CRUD completo

7. **Implementar a sobrecarga do operador << ✅**
   - Pessoa (e suas derivadas)
   - Item
   - Estoque
   - Camarim
   - Pedido
   - ListaCompras

8. **Tratamento de exceções ✅**
   - Try-catch em todas as operações críticas
   - Validações lançam exceções específicas

9. **Exceções personalizadas ✅**
   - 11 classes de exceções customizadas
   - Hierarquia de herança de exceções

10. **Tratar validação de dados com exceções ✅**
    - Validações em setters
    - Verificações em operações de negócio

11. **Diagrama de Classes – UML ✅**
    - Arquivo diagrama.md com todas as relações

12. **Funcionamento do Sistema ✅**
    - Interação com usuário via menus
    - Sistema modular e extensível


### ✅ **Observações**
1. Todas as heranças, implementações e polimorfismo devem ser de classes próprias. Herança e implementação de classes oriundas de bibliotecas, frameworks e afins não serão consideradas.


### 📂 **Estrutura de Diretórios**

Link do repositório:
https://github.com/Yuri-Nascimento/ProjetoLP1.git


```
.
├── bin/         # Executáveis gerados após a compilação
├── doc/         # Documentação do projeto
├── header/      # Arquivos de cabeçalho (.h) 
├── lib/         # Bibliotecas externas (ex: doctest.h)
├── src/         # Implementação das classes (.cpp)
├── test/        # Arquivos de teste (usando doctest)
├── .gitignore   # Arquivos/diretórios ignorados pelo Git
├── makefile     # Automação da compilação e execução
├── diagrama.md  # Diagrama UML das classes
└── README.md    # Este arquivo
```

---

### 🛠️ **Implementação das Operações do Sistema**

#### 📌 **Arquivos de Interface (header/):**
Define a estrutura de todas as classes e suas operações públicas:

- **`pessoa.h`**: Classe base abstrata com polimorfismo
- **`usuario.h`**: Classe Usuario (herda de Pessoa) + GerenciadorUsuarios
- **`artista.h`**: Classe Artista (herda de Pessoa) + GerenciadorArtistas
- **`item.h`**: Classe Item + GerenciadorItens
- **`estoque.h`**: Classe Estoque para gerenciar inventário
- **`camarim.h`**: Classe Camarim + GerenciadorCamarins
- **`pedido.h`**: Classe Pedido + GerenciadorPedidos
- **`listacompras.h`**: Classe ListaCompras + GerenciadorListaCompras
- **`excecoes.h`**: Hierarquia de exceções personalizadas

#### 📌 **Arquivo de Implementação (src/):**
Contém a lógica completa de todas as operações CRUD e validações:

- `pessoa.cpp`: Implementação da classe base
- `usuario.cpp`: Lógica de autenticação e CRUD de usuários
- `artista.cpp`: Gerenciamento de artistas e camarins
- `item.cpp`: Operações com itens/produtos
- `estoque.cpp`: Controle de estoque com validações
- `camarim.cpp`: Gerenciamento de camarins e seus itens
- `pedido.cpp`: Sistema de pedidos
- `listacompras.cpp`: Lista de compras com cálculo de totais
- `main.cpp`: Interface do usuário e integração

#### 📌 **Testes Automatizados (test/teste.cpp):**
Os testes são escritos utilizando o framework **doctest**, garantindo a validação automática de todas as operações:

- ✅ Testes de criação e validação
- ✅ Testes de operações CRUD
- ✅ Testes de exceções
- ✅ Testes de polimorfismo
- ✅ Testes de sobrecarga de operadores

---

### 📦 **Como Compilar e Executar**

O projeto pode ser compilado usando **make** (Linux/Mac) ou scripts PowerShell (Windows).

#### 🪟 **Windows (PowerShell):**

```powershell
# Compilar e executar o programa principal
.\compile.ps1

# Compilar e executar os testes
.\test.ps1
```

#### � **Linux/Mac (Makefile):**

| Comando        | Descrição                                   |
|----------------|---------------------------------------------|
| `make` ou `make all`  | Compila o programa principal e os testes. |
| `make run`     | Executa o programa principal (`bin/main`).  |
| `make test`    | Compila apenas os testes.                   |
| `make run-test`| Executa os testes (`bin/test`).             |
| `make clean`   | Remove arquivos objeto e executáveis.       |

#### 📌 **Exemplos de Uso:**

```bash
# Linux/Mac
make clean    # Limpar compilações anteriores
make          # Compilar tudo
make run      # Executar programa principal
make run-test # Executar testes

# Windows PowerShell
.\compile.ps1  # Compilar e executar
.\test.ps1     # Compilar e executar testes
```

#### ⚙️ **Requisitos:**
- **Compilador:** g++ com suporte a C++17
- **Sistema:** Windows, Linux ou macOS
- **Frameworks:** doctest.h (incluído em `lib/`)

---

### 📊 **Estrutura do Código**

```
Pessoa (classe base abstrata)
├── Usuario (herda de Pessoa)
└── Artista (herda de Pessoa)

ExcecaoBase (classe base de exceções)
├── ValidacaoException
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

### 🎯 **Conceitos de POO Implementados:**

1. **Encapsulamento**: Atributos privados com getters/setters validados
2. **Herança**: Pessoa → Usuario/Artista, ExcecaoBase → Exceções
3. **Polimorfismo**: Métodos virtuais sobrescritos (`exibir()`)
4. **Abstração**: Classes base abstratas (Pessoa)
5. **Sobrecarga de Operadores**: `<<` para todas as classes principais
6. **Tratamento de Exceções**: Sistema robusto com exceções personalizadas
