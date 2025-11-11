/**
 * @file teste.cpp
 * @brief Testes unitários completos do sistema
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 * 
 * Implementa testes para todas as classes do sistema usando doctest.
 * Testa sistema centralizado de catálogo de itens.
 */

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "pessoa.h"
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

// ==================== Testes do Catálogo de Itens (Sistema Centralizado) ====================

TEST_CASE("GerenciadorItens - CRUD Completo") {
    GerenciadorItens gerenciador;
    
    SUBCASE("Cadastrar item com sucesso") {
        int id = gerenciador.cadastrar("Água Mineral", 2.50);
        CHECK(id == 1);
        
        Item* item = gerenciador.buscarPorId(id);
        REQUIRE(item != nullptr);
        CHECK(item->getNome() == "Água Mineral");
        CHECK(item->getPreco() == doctest::Approx(2.50));
    }
    
    SUBCASE("Buscar item por nome") {
        gerenciador.cadastrar("Refrigerante", 5.00);
        Item* item = gerenciador.buscarPorNome("Refrigerante");
        REQUIRE(item != nullptr);
        CHECK(item->getPreco() == doctest::Approx(5.00));
    }
    
    SUBCASE("Atualizar item") {
        int id = gerenciador.cadastrar("Item Teste", 10.00);
        CHECK(gerenciador.atualizar(id, "Item Atualizado", 15.00) == true);
        
        Item* item = gerenciador.buscarPorId(id);
        CHECK(item->getNome() == "Item Atualizado");
        CHECK(item->getPreco() == doctest::Approx(15.00));
    }
    
    SUBCASE("Remover item") {
        int id = gerenciador.cadastrar("Item Temporário", 5.00);
        CHECK(gerenciador.remover(id) == true);
        CHECK(gerenciador.buscarPorId(id) == nullptr);
    }
    
    SUBCASE("Listar todos os itens") {
        gerenciador.cadastrar("Item 1", 1.00);
        gerenciador.cadastrar("Item 2", 2.00);
        gerenciador.cadastrar("Item 3", 3.00);
        
        auto lista = gerenciador.listar();
        CHECK(lista.size() == 3);
    }
    
    SUBCASE("Validações - Nome vazio") {
        CHECK_THROWS_AS(gerenciador.cadastrar("", 10.00), ValidacaoException);
    }
    
    SUBCASE("Validações - Preço negativo") {
        CHECK_THROWS_AS(gerenciador.cadastrar("Item", -5.00), ValidacaoException);
    }
    
    SUBCASE("Validações - Preço zero é permitido (item gratuito)") {
        CHECK_NOTHROW(gerenciador.cadastrar("Item Grátis", 0.00));
        Item* item = gerenciador.buscarPorNome("Item Grátis");
        REQUIRE(item != nullptr);
        CHECK(item->getPreco() == doctest::Approx(0.00));
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
    
    SUBCASE("Atualizar artista") {
        int id = gerenciador.cadastrar("Artista Antigo", 1);
        CHECK(gerenciador.atualizar(id, "Artista Novo", 2) == true);
        
        Artista* artista = gerenciador.buscarPorId(id);
        CHECK(artista->getNome() == "Artista Novo");
        CHECK(artista->getCamarimId() == 2);
    }
    
    SUBCASE("Buscar artistas por camarim") {
        gerenciador.cadastrar("Artista 1", 10);
        gerenciador.cadastrar("Artista 2", 10);
        gerenciador.cadastrar("Artista 3", 20);
        
        auto artistas = gerenciador.buscarPorCamarim(10);
        CHECK(artistas.size() == 2);
    }
    
    SUBCASE("Remover artista") {
        int id = gerenciador.cadastrar("Artista Temp", 1);
        CHECK(gerenciador.remover(id) == true);
        CHECK(gerenciador.buscarPorId(id) == nullptr);
    }
    
    SUBCASE("Listar todos os artistas") {
        gerenciador.cadastrar("Artista A", 1);
        gerenciador.cadastrar("Artista B", 2);
        
        auto lista = gerenciador.listar();
        CHECK(lista.size() == 2);
    }
}

TEST_CASE("Artista - Polimorfismo") {
    SUBCASE("Artista como Pessoa") {
        Pessoa* pessoa = new Artista(1, "Beyoncé", 5);
        
        string info = pessoa->exibir();
        CHECK(info.find("Artista") != string::npos);
        CHECK(info.find("Beyoncé") != string::npos);
        
        delete pessoa;
    }
}

// ==================== Testes da Classe Item ====================

TEST_CASE("Item - Operações básicas") {
    SUBCASE("Construtor e getters") {
        Item item(1, "Água Mineral", 2.50);
        
        CHECK(item.getId() == 1);
        CHECK(item.getNome() == "Água Mineral");
        CHECK(item.getPreco() == doctest::Approx(2.50));
    }
    
    SUBCASE("Setters") {
        Item item(1, "Item", 5.00);
        
        item.setId(10);
        item.setNome("Novo Nome");
        item.setPreco(7.50);
        
        CHECK(item.getId() == 10);
        CHECK(item.getNome() == "Novo Nome");
        CHECK(item.getPreco() == doctest::Approx(7.50));
    }
    
    SUBCASE("Operador de igualdade") {
        Item item1(1, "Item", 5.00);
        Item item2(1, "Outro", 10.00);
        Item item3(2, "Item", 5.00);
        
        CHECK(item1 == item2);  // Mesmo ID
        CHECK_FALSE(item1 == item3);  // IDs diferentes
    }
    
    SUBCASE("Exibir item") {
        Item item(5, "Refrigerante", 4.50);
        string info = item.exibir();
        
        CHECK(info.find("5") != string::npos);
        CHECK(info.find("Refrigerante") != string::npos);
        CHECK(info.find("4.50") != string::npos);
    }
    
    SUBCASE("Operador de stream") {
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
    
    SUBCASE("Adicionar mais quantidade a item existente") {
        estoque.adicionarItem(1, "Água", 50);
        estoque.adicionarItem(1, "Água", 30);
        CHECK(estoque.obterQuantidade(1) == 80);
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
        CHECK(estoque.verificarDisponibilidade(999, 1) == false); // Item inexistente
    }
    
    SUBCASE("Atualizar quantidade") {
        estoque.adicionarItem(1, "Água", 50);
        CHECK_NOTHROW(estoque.atualizarQuantidade(1, 100));
        CHECK(estoque.obterQuantidade(1) == 100);
    }
    
    SUBCASE("Listar itens do estoque") {
        estoque.adicionarItem(1, "Água", 50);
        estoque.adicionarItem(2, "Refrigerante", 30);
        
        auto lista = estoque.listar();
        CHECK(lista.size() == 2);
    }
    
    SUBCASE("Obter quantidade de item inexistente") {
        CHECK(estoque.obterQuantidade(999) == 0);
    }
    
    SUBCASE("Exibir estoque") {
        estoque.adicionarItem(1, "Água", 100);
        string info = estoque.exibir();
        CHECK(info.find("Água") != string::npos);
        CHECK(info.find("100") != string::npos);
    }
}

// ==================== Testes da Classe Camarim ====================

TEST_CASE("Camarim - Gerenciamento de itens") {
    Camarim camarim(1, "Camarim VIP", 1);
    
    SUBCASE("Inserir item no camarim") {
        CHECK_NOTHROW(camarim.inserirItem(1, "Água", 10));
        // Nota: funções contemplItem() e obterQuantidadeItem() foram removidas
        // pois são redundantes com o sistema centralizado
    }
    
    SUBCASE("Remover item do camarim") {
        camarim.inserirItem(1, "Água", 10);
        CHECK_NOTHROW(camarim.removerItem(1, 5));
        // Quantidade reduzida de 10 para 5
    }
    
    SUBCASE("Remover item completamente") {
        camarim.inserirItem(1, "Água", 10);
        CHECK(camarim.removerItem(1, 10) == true);
        // Remove toda a quantidade
    }
    
    SUBCASE("Quantidade insuficiente") {
        camarim.inserirItem(1, "Água", 5);
        CHECK_THROWS_AS(camarim.removerItem(1, 10), CamarimException);
    }
    
    SUBCASE("Exibir camarim") {
        camarim.inserirItem(1, "Água", 10);
        string info = camarim.exibir();
        CHECK(info.find("Camarim VIP") != string::npos);
        CHECK(info.find("Água") != string::npos);
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
        CHECK(camarim->getArtistaId() == 1);
    }
    
    SUBCASE("Buscar por artista") {
        gerenciador.cadastrar("Camarim 1", 10);
        gerenciador.cadastrar("Camarim 2", 20);
        
        Camarim* camarim = gerenciador.buscarPorArtista(10);
        REQUIRE(camarim != nullptr);
        CHECK(camarim->getArtistaId() == 10);
    }
    
    SUBCASE("Atualizar camarim") {
        int id = gerenciador.cadastrar("Nome Antigo", 1);
        CHECK(gerenciador.atualizar(id, "Nome Novo", 2) == true);
        
        Camarim* camarim = gerenciador.buscarPorId(id);
        CHECK(camarim->getNome() == "Nome Novo");
        CHECK(camarim->getArtistaId() == 2);
    }
    
    SUBCASE("Remover camarim") {
        int id = gerenciador.cadastrar("Camarim Temp", 1);
        CHECK(gerenciador.remover(id) == true);
        CHECK(gerenciador.buscarPorId(id) == nullptr);
    }
    
    SUBCASE("Listar camarins") {
        gerenciador.cadastrar("Camarim 1", 1);
        gerenciador.cadastrar("Camarim 2", 2);
        
        auto lista = gerenciador.listar();
        CHECK(lista.size() == 2);
    }
    
    SUBCASE("Validação - Nome vazio") {
        CHECK_THROWS_AS(gerenciador.cadastrar("", 1), ValidacaoException);
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
        CHECK(pedido->getCamarimId() == 1);
        CHECK(pedido->isAtendido() == false);
    }
    
    SUBCASE("Adicionar itens ao pedido") {
        int id = gerenciador.criar(1, "Artista Y");
        Pedido* pedido = gerenciador.buscarPorId(id);
        
        CHECK_NOTHROW(pedido->adicionarItem(1, "Água", 10));
        CHECK_NOTHROW(pedido->adicionarItem(2, "Refrigerante", 5));
        // Nota: listarItens() foi removida, use exibir() para verificar
    }
    
    SUBCASE("Remover item do pedido") {
        int id = gerenciador.criar(1, "Artista Z");
        Pedido* pedido = gerenciador.buscarPorId(id);
        
        pedido->adicionarItem(1, "Água", 10);
        CHECK(pedido->removerItem(1) == true);
        CHECK(pedido->removerItem(999) == false); // Item inexistente
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
    
    SUBCASE("Não pode remover item de pedido atendido") {
        int id = gerenciador.criar(1, "Artista V");
        Pedido* pedido = gerenciador.buscarPorId(id);
        pedido->adicionarItem(1, "Água", 10);
        pedido->marcarAtendido();
        
        CHECK_THROWS_AS(pedido->removerItem(1), PedidoException);
    }
    
    SUBCASE("Listar todos os pedidos") {
        gerenciador.criar(1, "Artista 1");
        gerenciador.criar(2, "Artista 2");
        
        auto lista = gerenciador.listar();
        CHECK(lista.size() == 2);
    }
    
    SUBCASE("Buscar pedidos por camarim") {
        gerenciador.criar(10, "Artista A");
        gerenciador.criar(10, "Artista B");
        gerenciador.criar(20, "Artista C");
        
        auto pedidos = gerenciador.buscarPorCamarim(10);
        CHECK(pedidos.size() == 2);
    }
    
    SUBCASE("Listar pedidos pendentes") {
        int id1 = gerenciador.criar(1, "Artista 1");
        gerenciador.criar(2, "Artista 2");
        
        Pedido* pedido1 = gerenciador.buscarPorId(id1);
        pedido1->marcarAtendido();
        
        auto pendentes = gerenciador.listarPendentes();
        CHECK(pendentes.size() == 1);
    }
    
    SUBCASE("Remover pedido") {
        int id = gerenciador.criar(1, "Artista Temp");
        CHECK(gerenciador.remover(id) == true);
        CHECK(gerenciador.buscarPorId(id) == nullptr);
    }
    
    SUBCASE("Exibir pedido") {
        int id = gerenciador.criar(1, "Madonna");
        Pedido* pedido = gerenciador.buscarPorId(id);
        pedido->adicionarItem(1, "Água", 5);
        
        string info = pedido->exibir();
        CHECK(info.find("Madonna") != string::npos);
        CHECK(info.find("Água") != string::npos);
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
    
    SUBCASE("Remover item") {
        int id = gerenciador.criar("Lista");
        ListaCompras* lista = gerenciador.buscarPorId(id);
        
        lista->adicionarItem(1, "Água", 10, 2.00);
        lista->adicionarItem(2, "Refrigerante", 5, 3.00);
        
        CHECK(lista->removerItem(1) == true);
        
        double total = lista->calcularTotal();
        CHECK(total == doctest::Approx(15.00)); // Apenas refrigerante
    }
    
    SUBCASE("Limpar lista") {
        int id = gerenciador.criar("Lista");
        ListaCompras* lista = gerenciador.buscarPorId(id);
        
        lista->adicionarItem(1, "Água", 10, 2.00);
        lista->adicionarItem(2, "Refrigerante", 5, 3.00);
        
        CHECK_NOTHROW(lista->limpar());
        CHECK(lista->calcularTotal() == doctest::Approx(0.00));
    }
    
    SUBCASE("Listar todas as listas") {
        gerenciador.criar("Lista 1");
        gerenciador.criar("Lista 2");
        
        auto listas = gerenciador.listar();
        CHECK(listas.size() == 2);
    }
    
    SUBCASE("Remover lista") {
        int id = gerenciador.criar("Lista Temp");
        CHECK(gerenciador.remover(id) == true);
        CHECK(gerenciador.buscarPorId(id) == nullptr);
    }
    
    SUBCASE("Exibir lista") {
        int id = gerenciador.criar("Compras Mensais");
        ListaCompras* lista = gerenciador.buscarPorId(id);
        lista->adicionarItem(1, "Água", 50, 2.50);
        
        string info = lista->exibir();
        CHECK(info.find("Compras Mensais") != string::npos);
        CHECK(info.find("Água") != string::npos);
        CHECK(info.find("125") != string::npos); // 50 * 2.50
    }
    
    SUBCASE("Validação - Quantidade negativa") {
        int id = gerenciador.criar("Lista");
        ListaCompras* lista = gerenciador.buscarPorId(id);
        
        CHECK_THROWS_AS(lista->adicionarItem(1, "Item", -5, 10.00), ValidacaoException);
    }
    
    SUBCASE("Validação - Preço negativo") {
        int id = gerenciador.criar("Lista");
        ListaCompras* lista = gerenciador.buscarPorId(id);
        
        CHECK_THROWS_AS(lista->adicionarItem(1, "Item", 10, -5.00), ValidacaoException);
    }
}

// ==================== Testes de Integração (Sistema Centralizado) ====================

TEST_CASE("Integração - Sistema Centralizado de Catálogo") {
    GerenciadorItens catalogo;
    Estoque estoque;
    
    SUBCASE("Fluxo completo: Catálogo -> Estoque") {
        // 1. Cadastrar item no catálogo
        int itemId = catalogo.cadastrar("Água Mineral", 2.50);
        
        // 2. Adicionar ao estoque usando dados do catálogo
        Item* item = catalogo.buscarPorId(itemId);
        REQUIRE(item != nullptr);
        estoque.adicionarItem(item->getId(), item->getNome(), 100);
        
        // 3. Verificar disponibilidade
        CHECK(estoque.verificarDisponibilidade(itemId, 50) == true);
        CHECK(estoque.obterQuantidade(itemId) == 100);
    }
    
    SUBCASE("Fluxo completo: Catálogo -> Camarim") {
        GerenciadorCamarins gerenciadorCamarins;
        
        // 1. Cadastrar item no catálogo
        int itemId = catalogo.cadastrar("Toalha", 15.00);
        
        // 2. Criar camarim
        int camarimId = gerenciadorCamarins.cadastrar("Camarim VIP", 1);
        Camarim* camarim = gerenciadorCamarins.buscarPorId(camarimId);
        
        // 3. Adicionar item do catálogo ao camarim
        Item* item = catalogo.buscarPorId(itemId);
        REQUIRE(item != nullptr);
        CHECK_NOTHROW(camarim->inserirItem(item->getId(), item->getNome(), 5));
    }
    
    SUBCASE("Fluxo completo: Catálogo -> Pedido") {
        GerenciadorPedidos gerenciadorPedidos;
        
        // 1. Cadastrar item no catálogo
        int itemId = catalogo.cadastrar("Água", 2.00);
        
        // 2. Criar pedido
        int pedidoId = gerenciadorPedidos.criar(1, "Beyoncé");
        Pedido* pedido = gerenciadorPedidos.buscarPorId(pedidoId);
        
        // 3. Adicionar item do catálogo ao pedido
        Item* item = catalogo.buscarPorId(itemId);
        REQUIRE(item != nullptr);
        CHECK_NOTHROW(pedido->adicionarItem(item->getId(), item->getNome(), 10));
    }
    
    SUBCASE("Fluxo completo: Catálogo -> Lista de Compras") {
        GerenciadorListaCompras gerenciadorListas;
        
        // 1. Cadastrar item no catálogo
        int itemId = catalogo.cadastrar("Refrigerante", 5.00);
        
        // 2. Criar lista de compras
        int listaId = gerenciadorListas.criar("Compras Semanais");
        ListaCompras* lista = gerenciadorListas.buscarPorId(listaId);
        
        // 3. Adicionar item do catálogo à lista (preço vem do catálogo)
        Item* item = catalogo.buscarPorId(itemId);
        REQUIRE(item != nullptr);
        CHECK_NOTHROW(lista->adicionarItem(item->getId(), item->getNome(), 20, item->getPreco()));
        
        // 4. Verificar total
        double total = lista->calcularTotal();
        CHECK(total == doctest::Approx(100.00)); // 20 * 5.00
    }
}

// ==================== Testes de Exceções ====================

TEST_CASE("Exceções - Validação completa") {
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
    
    SUBCASE("CamarimException") {
        Camarim camarim(1, "Camarim", 1);
        camarim.inserirItem(1, "Água", 5);
        
        try {
            camarim.removerItem(1, 10);
            CHECK(false);
        } catch (const CamarimException& e) {
            string msg(e.what());
            CHECK(msg.length() > 0);
        }
    }
    
    SUBCASE("PedidoException - Pedido já atendido") {
        GerenciadorPedidos gerenciador;
        int id = gerenciador.criar(1, "Artista");
        Pedido* pedido = gerenciador.buscarPorId(id);
        
        pedido->marcarAtendido();
        
        try {
            pedido->adicionarItem(1, "Água", 10);
            CHECK(false);
        } catch (const PedidoException& e) {
            string msg(e.what());
            CHECK(msg.find("atendido") != string::npos);
        }
    }
    
    SUBCASE("ListaComprasException") {
        GerenciadorListaCompras gerenciador;
        int id = gerenciador.criar("Lista");
        ListaCompras* lista = gerenciador.buscarPorId(id);
        
        try {
            lista->adicionarItem(1, "Item", -5, 10.00);
            CHECK(false);
        } catch (const ValidacaoException& e) {
            string msg(e.what());
            CHECK(msg.length() > 0);
        }
    }
    
    SUBCASE("ArtistaException") {
        GerenciadorArtistas gerenciador;
        
        try {
            gerenciador.cadastrar("", 1);
            CHECK(false);
        } catch (const ValidacaoException& e) {
            string msg(e.what());
            CHECK(msg.find("vazio") != string::npos);
        }
    }
}

// ==================== Testes de Cenários Reais ====================

TEST_CASE("Cenário Real - Show Completo") {
    GerenciadorItens catalogo;
    GerenciadorArtistas gerenciadorArtistas;
    GerenciadorCamarins gerenciadorCamarins;
    GerenciadorPedidos gerenciadorPedidos;
    Estoque estoque;
    
    SUBCASE("Preparação completa de show") {
        // 1. Cadastrar itens no catálogo
        int aguaId = catalogo.cadastrar("Água Mineral", 2.50);
        int refriId = catalogo.cadastrar("Refrigerante", 5.00);
        int toalhaId = catalogo.cadastrar("Toalha", 15.00);
        
        // 2. Adicionar ao estoque
        estoque.adicionarItem(aguaId, "Água Mineral", 200);
        estoque.adicionarItem(refriId, "Refrigerante", 100);
        estoque.adicionarItem(toalhaId, "Toalha", 50);
        
        // 3. Cadastrar artista e camarim
        int artistaId = gerenciadorArtistas.cadastrar("Madonna", 0);
        int camarimId = gerenciadorCamarins.cadastrar("Camarim Principal", artistaId);
        
        // 4. Atualizar artista com camarim
        gerenciadorArtistas.atualizar(artistaId, "Madonna", camarimId);
        
        // 5. Preparar camarim
        Camarim* camarim = gerenciadorCamarins.buscarPorId(camarimId);
        camarim->inserirItem(aguaId, "Água Mineral", 20);
        camarim->inserirItem(toalhaId, "Toalha", 5);
        
        // 6. Criar pedido
        int pedidoId = gerenciadorPedidos.criar(camarimId, "Madonna");
        Pedido* pedido = gerenciadorPedidos.buscarPorId(pedidoId);
        pedido->adicionarItem(refriId, "Refrigerante", 10);
        
        // Verificações
        CHECK(estoque.verificarDisponibilidade(aguaId, 20) == true);
        CHECK(gerenciadorArtistas.buscarPorCamarim(camarimId).size() == 1);
        CHECK(gerenciadorPedidos.listarPendentes().size() == 1);
    }
}

// ==================== Estatísticas dos Testes ====================

TEST_CASE("Sistema - Contadores e estatísticas") {
    SUBCASE("Verificar geração de IDs únicos") {
        GerenciadorItens catalogo;
        
        int id1 = catalogo.cadastrar("Item 1", 10.00);
        int id2 = catalogo.cadastrar("Item 2", 20.00);
        int id3 = catalogo.cadastrar("Item 3", 30.00);
        
        CHECK(id1 == 1);
        CHECK(id2 == 2);
        CHECK(id3 == 3);
    }
    
    SUBCASE("Contagem de elementos em gerenciadores") {
        GerenciadorArtistas gerenciador;
        
        gerenciador.cadastrar("Artista 1", 1);
        gerenciador.cadastrar("Artista 2", 2);
        gerenciador.cadastrar("Artista 3", 3);
        
        auto lista = gerenciador.listar();
        CHECK(lista.size() == 3);
    }
}
