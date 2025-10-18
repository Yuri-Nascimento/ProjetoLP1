# Informações do Projeto

- **Instituição:** IMD
- **Disciplina:** LP1
- **Professor:** Prof. Jerffeson Gomes Dutra

  
## Atividade LP1 - Desenvolver uma aplicação funcional, utilizando os principais conceitos da programação orientada a objetos (POO). A aplicação deve conter um conjunto mínimo de funcionalidades que envolvam cadastro, consulta, alteração e remoção de dados (CRUD).

### ✅ **Requisitos Mínimos**
1. 8 Classes ✅
2. Encapsulamento de todas as entidades ✅❌
3. 2 Heranças ❌
a. Classes Bases Diferentes ❌
4. Min 2 Polimorfismo ❌
a. Classes Bases diferentes ✅
5. CRUD ✅
  a. Criar, ler, atualizar e remover registros de 6 entidades. ❌
  b. Implementar a sobrecarga do operador << para exibir as entidades no console ❌
6. Tratamento de exceções ❌
  a. Exceções personalizadas ❌
  b. Tratar validação de dados com exceções ❌
7. Diagrama de Classes – UML ✅
8. Funcionamento do Sistema ✅
  a. interação com usuário ✅


### ✅ **Observações**
1. Todas as heranças, implementações e polimorfismo devem ser de classes próprias. Herança e implementação de classes oriundas de bibliotecas, frameworks e afins não serão consideradas.


### 📂 **Estrutura de Diretórios**

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

### 🛠️ **Implementação das Operações do Camarim**

### 📌 **Arquivo de Interface (`header/camarim.h`):**
Define a estrutura da classe `Camarim` e suas operações públicas:

- `bool inserir(int elemento);`  
- `bool remover(int elemento);`  
- `bool contem(int elemento) const;`  
- `int tamanho() const;`  
- `void imprimir() const;`  

#### 📌 **Arquivo de Implementação (`src/camarim.cpp`):**
Contém a lógica completa de manipulação do conjunto e implementação dos métodos.

#### 📌 **Testes Automatizados (`test/teste.cpp`):**
Os testes são escritos utilizando o framework **doctest**, garantindo a validação automática de todas as operações da estrutura de dados.

---

### 📦 **Como Compilar e Executar Usando o Makefile**

O projeto inclui um `makefile` configurado para facilitar a compilação e execução. 

#### 🔧 **Comandos Disponíveis:**

| Comando        | Descrição                                   |
|----------------|---------------------------------------------|
| `make` ou `make all`  | Compila o programa principal e os testes. |
| `make run`     | Executa o programa principal (`bin/main`).  |
| `make test`    | Compila apenas os testes.                   |
| `make run-test`| Executa os testes (`bin/test`).             |
| `make clean`   | Remove arquivos objeto e executáveis.       |

#### 📌 **Exemplos de Uso:**

```bash
# Compilar o projeto
make

# Executar o programa principal
make run

# Compilar e rodar os testes
make test
make run-test

# Limpar os arquivos de build
make clean
```
