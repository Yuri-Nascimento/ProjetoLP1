classDiagram
      class Pessoa {
        <<abstract>>
        #string nome
        #string email
        #string telefone
        +string exibir()* abstract
        +getNome() string
        +setNome(string nome) void
    }

    class Usuario {
        -string login
        -string senha
        +string exibir() override
        +getLogin() string
        +setLogin(string login) void
    }

    class Artista {
        -string especialidade
        -double cache
        +string exibir() override
        +getEspecialidade() string
        +setEspecialidade(string esp) void
    }

    class Item {
        -int id
        -string nome
        -string categoria
        -double preco
        +getId() int
        +setId(int id) void
    }

    class Estoque {
        -vector~ItemEstoque~ itens
        -int capacidadeMaxima
        +adicionarItem(ItemEstoque item) void
        +removerItem(int id) bool
        +verificarDisponibilidade(int id) int
    }

    class Camarim {
        -int numero
        -string localizacao
        -bool ocupado
        -vector~ItemCamarim~ itens
        +getNumero() int
        +setNumero(int num) void
    }

    class Pedido {
        -int id
        -string data
        -string status
        -vector~ItemPedido~ itens
        +calcularTotal() double
        +adicionarItem(ItemPedido item) void
    }

    class ListaCompras {
        -int id
        -string nome
        -vector~ItemCompra~ itens
        +calcularTotal() double
        +adicionarItem(ItemCompra item) void
    }

    class GerenciadorUsuarios {
        -vector~Usuario~ usuarios
        +adicionarUsuario(Usuario user) void
        +removerUsuario(string login) bool
        +buscarUsuario(string login) Usuario*
    }

    class GerenciadorArtistas {
        -vector~Artista~ artistas
        +adicionarArtista(Artista art) void
        +removerArtista(string nome) bool
        +buscarArtista(string nome) Artista*
    }

    class GerenciadorItens {
        -vector~Item~ itens
        +adicionarItem(Item item) void
        +removerItem(int id) bool
        +buscarItem(int id) Item*
    }

    class GerenciadorCamarins {
        -vector~Camarim~ camarins
        +alocarCamarim(Artista artista) Camarim*
        +liberarCamarim(int numero) bool
    }

    class GerenciadorPedidos {
        -vector~Pedido~ pedidos
        +criarPedido() Pedido*
        +processarPedido(int id) bool
        +cancelarPedido(int id) bool
    }

    class GerenciadorListaCompras {
        -vector~ListaCompras~ listas
        +criarLista(string nome) ListaCompras*
        +adicionarItemLista(int listaId, ItemCompra item) bool
    }

    class ExcecaoBase {
        <<abstract>>
        #string mensagem
        #string timestamp
        +const char* what()* abstract
        +getMensagem() string
        +getTimestamp() string
    }

    class ValidacaoException {
        -string campo
        +const char* what() override
    }

    class UsuarioNaoEncontradoException {
        -string login
        +const char* what() override
    }

    class UsuarioJaExisteException {
        -string login
        +const char* what() override
    }

    class ArtistaException {
        -string artistaNome
        +const char* what() override
    }

    class ItemException {
        -int itemId
        +const char* what() override
    }

    class EstoqueException {
        -int itemId
        +const char* what() override
    }

    class EstoqueInsuficienteException {
        -int itemId
        -int quantidadeRequisitada
        -int quantidadeDisponivel
        +const char* what() override
    }

    class CamarimException {
        -int camarimNumero
        +const char* what() override
    }

    class PedidoException {
        -int pedidoId
        +const char* what() override
    }

    class ListaComprasException {
        -int listaId
        +const char* what() override
    }

    class ItemEstoque {
        +int itemId
        +int quantidade
        +string localizacao
        +int getQuantidade() int
        +void setQuantidade(int qtd) void
    }

    class ItemCamarim {
        +int itemId
        +int quantidade
        +string observacao
    }

    class ItemPedido {
        +int itemId
        +int quantidade
        +double precoUnitario
        +double calcularSubtotal() double
    }

    class ItemCompra {
        +int itemId
        +int quantidade
        +bool comprado
        +marcarComoComprado() void
    }

    Pessoa <|-- Usuario
    Pessoa <|-- Artista
    ExcecaoBase <|-- ValidacaoException
    ExcecaoBase <|-- UsuarioNaoEncontradoException
    ExcecaoBase <|-- UsuarioJaExisteException
    ExcecaoBase <|-- ArtistaException
    ExcecaoBase <|-- ItemException
    ExcecaoBase <|-- EstoqueException
    EstoqueException <|-- EstoqueInsuficienteException
    ExcecaoBase <|-- CamarimException
    ExcecaoBase <|-- PedidoException
    ExcecaoBase <|-- ListaComprasException

    Estoque "1" *-- "0..*" ItemEstoque
    Camarim "1" *-- "0..*" ItemCamarim
    Pedido "1" *-- "0..*" ItemPedido
    ListaCompras "1" *-- "0..*" ItemCompra
    
    GerenciadorUsuarios "1" --> "0..*" Usuario
    GerenciadorArtistas "1" --> "0..*" Artista
    GerenciadorItens "1" --> "0..*" Item
    GerenciadorCamarins "1" --> "0..*" Camarim
    GerenciadorPedidos "1" --> "0..*" Pedido
    GerenciadorListaCompras "1" --> "0..*" ListaCompras

    Pedido --> Item : utiliza
    ListaCompras --> Item : referencia
    Camarim --> Artista : alocado para
    Estoque --> Item : contém
