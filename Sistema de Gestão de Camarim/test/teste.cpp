/**
 * @file teste.cpp
 * @brief Testes unitários do sistema
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Implementa testes para todas as classes do sistema usando doctest.
 */

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "pessoa.h"
#include "usuario.h"
#include "artista.h"
#include "item.h"
#include "estoque.h"
#include "camarim.h"
#include "pedido.h"
#include "listacompras.h"
#include "excecoes.h"
#include <cstdlib>

int main(int argc, char** argv) {
    // Configurar codificação UTF-8 no Windows
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    
    int res = context.run();
    
    if(context.shouldExit())
        return res;
    
    return res;
}

// ==================== Testes da Classe Usuario ====================

TEST_CASE("Usuario - Criação e validação") {
    GerenciadorUsuarios gerenciador;
    
    SUBCASE("Cadastrar usuário com sucesso") {
        int id = gerenciador.cadastrar("João Silva", "joao", "senha123");
        CHECK(id == 1);
        
        Usuario* usuario = gerenciador.buscarPorId(id);
        REQUIRE(usuario != nullptr);
        CHECK(usuario->getNome() == "João Silva");
        CHECK(usuario->getLogin() == "joao");
    }
    
    SUBCASE("Login duplicado deve lançar exceção") {
        gerenciador.cadastrar("Usuario1", "login1", "senha1");
        CHECK_THROWS_AS(gerenciador.cadastrar("Usuario2", "login1", "senha2"), 
                        UsuarioJaExisteException);
    }
    
    SUBCASE("Validação de credenciais") {
        gerenciador.cadastrar("Teste", "teste", "senha123");
        Usuario* usuario = gerenciador.buscarPorLogin("teste");
        REQUIRE(usuario != nullptr);
        CHECK(usuario->validarCredenciais("teste", "senha123") == true);
        CHECK(usuario->validarCredenciais("teste", "senhaErrada") == false);
    }
}

TEST_CASE("Usuario - Operações CRUD") {
    GerenciadorUsuarios gerenciador;
    
    SUBCASE("Listar usuários") {
        gerenciador.cadastrar("Usuario1", "user1", "pass1");
        gerenciador.cadastrar("Usuario2", "user2", "pass2");
        
        auto lista = gerenciador.listar();
        CHECK(lista.size() == 2);
    }
    
    SUBCASE("Remover usuário") {
        int id = gerenciador.cadastrar("Usuario", "user", "pass");
        CHECK(gerenciador.remover(id) == true);
        CHECK(gerenciador.buscarPorId(id) == nullptr);
    }
    
    SUBCASE("Atualizar usuário") {
        int id = gerenciador.cadastrar("Nome Antigo", "login", "senha");
        CHECK_NOTHROW(gerenciador.atualizar(id, "Nome Novo", "novoLogin", "novaSenha"));
        
        Usuario* usuario = gerenciador.buscarPorId(id);
        CHECK(usuario->getNome() == "Nome Novo");
        CHECK(usuario->getLogin() == "novoLogin");
    }
}

// ==================== Testes da Classe Artista ====================

TEST_CASE("Artista - Criação e validação") {
    GerenciadorArtistas gerenciador;
    
    SUBCASE("Cadastrar artista com sucesso") {
        int id = gerenciador.cadastrar("Madonna", 1);
        CHECK(id == 1);
        
        Artista* artista = gerenciador.buscarPorId(id);
        REQUIRE(artista != nullptr);
        CHECK(artista->getNome() == "Madonna");
        CHECK(artista->getCamarimId() == 1);
    }
    
    SUBCASE("Nome vazio deve lançar exceção") {
        CHECK_THROWS_AS(gerenciador.cadastrar("", 1), ValidacaoException);
    }
}

// ==================== Testes da Classe Item ====================

TEST_CASE("Item - Criação e validação") {
    GerenciadorItens gerenciador;
    
    SUBCASE("Cadastrar item com sucesso") {
        int id = gerenciador.cadastrar("Água Mineral", 2.50);
        CHECK(id == 1);
        
        Item* item = gerenciador.buscarPorId(id);
        REQUIRE(item != nullptr);
        CHECK(item->getNome() == "Água Mineral");
        CHECK(item->getPreco() == doctest::Approx(2.50));
    }
    
    SUBCASE("Preço negativo deve lançar exceção") {
        CHECK_THROWS_AS(gerenciador.cadastrar("Item", -5.0), ValidacaoException);
    }
    
    SUBCASE("Operador << deve funcionar") {
        Item item(1, "Teste", 10.0);
        stringstream ss;
        ss << item;
        CHECK(ss.str().find("Teste") != string::npos);
    }
}

// ==================== Testes da Classe Estoque ====================

TEST_CASE("Estoque - Operações básicas") {
    Estoque estoque;
    
    SUBCASE("Adicionar item ao estoque") {
        CHECK_NOTHROW(estoque.adicionarItem(1, "Água", 100));
        CHECK(estoque.obterQuantidade(1) == 100);
    }
    
    SUBCASE("Remover item do estoque") {
        estoque.adicionarItem(1, "Água", 100);
        CHECK_NOTHROW(estoque.removerItem(1, 30));
        CHECK(estoque.obterQuantidade(1) == 70);
    }
    
    SUBCASE("Estoque insuficiente deve lançar exceção") {
        estoque.adicionarItem(1, "Água", 10);
        CHECK_THROWS_AS(estoque.removerItem(1, 20), EstoqueInsuficienteException);
    }
    
    SUBCASE("Verificar disponibilidade") {
        estoque.adicionarItem(1, "Água", 50);
        CHECK(estoque.verificarDisponibilidade(1, 30) == true);
        CHECK(estoque.verificarDisponibilidade(1, 100) == false);
    }
}

// ==================== Testes da Classe Camarim ====================

TEST_CASE("Camarim - Gerenciamento de itens") {
    Camarim camarim(1, "Camarim VIP", 1);
    
    SUBCASE("Inserir item no camarim") {
        CHECK_NOTHROW(camarim.inserirItem(1, "Água", 10));
        CHECK(camarim.obterQuantidadeItem(1) == 10);
        CHECK(camarim.contemItem(1) == true);
    }
    
    SUBCASE("Remover item do camarim") {
        camarim.inserirItem(1, "Água", 10);
        CHECK_NOTHROW(camarim.removerItem(1, 5));
        CHECK(camarim.obterQuantidadeItem(1) == 5);
    }
    
    SUBCASE("Calcular total de itens") {
        camarim.inserirItem(1, "Água", 10);
        camarim.inserirItem(2, "Refrigerante", 5);
        CHECK(camarim.calcularTotalItens() == 15);
    }
}

TEST_CASE("GerenciadorCamarins - Operações CRUD") {
    GerenciadorCamarins gerenciador;
    
    SUBCASE("Cadastrar camarim") {
        int id = gerenciador.cadastrar("Camarim A", 1);
        CHECK(id == 1);
        
        Camarim* camarim = gerenciador.buscarPorId(id);
        REQUIRE(camarim != nullptr);
        CHECK(camarim->getNome() == "Camarim A");
    }
    
    SUBCASE("Buscar por artista") {
        gerenciador.cadastrar("Camarim 1", 10);
        Camarim* camarim = gerenciador.buscarPorArtista(10);
        REQUIRE(camarim != nullptr);
        CHECK(camarim->getArtistaId() == 10);
    }
}

// ==================== Testes da Classe Pedido ====================

TEST_CASE("Pedido - Gerenciamento") {
    GerenciadorPedidos gerenciador;
    
    SUBCASE("Criar pedido") {
        int id = gerenciador.criar(1, "Artista X");
        CHECK(id == 1);
        
        Pedido* pedido = gerenciador.buscarPorId(id);
        REQUIRE(pedido != nullptr);
        CHECK(pedido->getNomeArtista() == "Artista X");
        CHECK(pedido->isAtendido() == false);
    }
    
    SUBCASE("Adicionar itens ao pedido") {
        int id = gerenciador.criar(1, "Artista Y");
        Pedido* pedido = gerenciador.buscarPorId(id);
        
        CHECK_NOTHROW(pedido->adicionarItem(1, "Água", 10));
        CHECK_NOTHROW(pedido->adicionarItem(2, "Refrigerante", 5));
        
        auto itens = pedido->listarItens();
        CHECK(itens.size() == 2);
    }
    
    SUBCASE("Marcar pedido como atendido") {
        int id = gerenciador.criar(1, "Artista Z");
        Pedido* pedido = gerenciador.buscarPorId(id);
        
        pedido->marcarAtendido();
        CHECK(pedido->isAtendido() == true);
    }
    
    SUBCASE("Não pode adicionar item a pedido atendido") {
        int id = gerenciador.criar(1, "Artista W");
        Pedido* pedido = gerenciador.buscarPorId(id);
        pedido->marcarAtendido();
        
        CHECK_THROWS_AS(pedido->adicionarItem(1, "Água", 10), PedidoException);
    }
}

// ==================== Testes da Classe ListaCompras ====================

TEST_CASE("ListaCompras - Gerenciamento") {
    GerenciadorListaCompras gerenciador;
    
    SUBCASE("Criar lista de compras") {
        int id = gerenciador.criar("Compras Semanal");
        CHECK(id == 1);
        
        ListaCompras* lista = gerenciador.buscarPorId(id);
        REQUIRE(lista != nullptr);
        CHECK(lista->getDescricao() == "Compras Semanal");
    }
    
    SUBCASE("Adicionar itens e calcular total") {
        int id = gerenciador.criar("Lista Teste");
        ListaCompras* lista = gerenciador.buscarPorId(id);
        
        lista->adicionarItem(1, "Água", 10, 2.50);
        lista->adicionarItem(2, "Refrigerante", 5, 5.00);
        
        double total = lista->calcularTotal();
        CHECK(total == doctest::Approx(50.00)); // 10*2.50 + 5*5.00 = 25 + 25 = 50
    }
    
    SUBCASE("Atualizar quantidade") {
        int id = gerenciador.criar("Lista");
        ListaCompras* lista = gerenciador.buscarPorId(id);
        
        lista->adicionarItem(1, "Água", 10, 2.00);
        CHECK_NOTHROW(lista->atualizarQuantidade(1, 20));
        
        double total = lista->calcularTotal();
        CHECK(total == doctest::Approx(40.00)); // 20*2.00
    }
}

// ==================== Testes de Polimorfismo ====================

TEST_CASE("Polimorfismo - Pessoa base") {
    SUBCASE("Usuario como Pessoa") {
        Pessoa* pessoa = new Usuario(1, "João", "joao", "senha");
        
        string info = pessoa->exibir();
        CHECK(info.find("Usuario") != string::npos);
        CHECK(info.find("João") != string::npos);
        
        delete pessoa;
    }
    
    SUBCASE("Artista como Pessoa") {
        Pessoa* pessoa = new Artista(2, "Madonna", 1);
        
        string info = pessoa->exibir();
        CHECK(info.find("Artista") != string::npos);
        CHECK(info.find("Madonna") != string::npos);
        
        delete pessoa;
    }
}

// ==================== Testes de Exceções ====================

TEST_CASE("Exceções - Validação") {
    SUBCASE("ValidacaoException") {
        try {
            throw ValidacaoException("Teste de validação");
        } catch (const ExcecaoBase& e) {
            string msg(e.what());
            CHECK(msg.find("Teste de validação") != string::npos);
        }
    }
    
    SUBCASE("EstoqueInsuficienteException") {
        Estoque estoque;
        estoque.adicionarItem(1, "Item", 5);
        
        try {
            estoque.removerItem(1, 10);
            CHECK(false); // Não deveria chegar aqui
        } catch (const EstoqueInsuficienteException& e) {
            string msg(e.what());
            CHECK(msg.find("insuficiente") != string::npos);
        }
    }
}
