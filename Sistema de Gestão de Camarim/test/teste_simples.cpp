/**
 * @file teste_simples.cpp
 * @brief Testes simples sem framework externo
 * @authors Fábio Augusto Vieira de Sales Vila
 *          Jerônimo Rafael Bezerra Filho
 *          Yuri Wendel do Nascimento
 */

#include <iostream>
#include <cassert>
#include "pessoa.h"
#include "usuario.h"
#include "artista.h"
#include "item.h"
#include "estoque.h"
#include "camarim.h"
#include "pedido.h"
#include "listacompras.h"
#include "excecoes.h"

using namespace std;

int testesExecutados = 0;
int testesSucesso = 0;

void testar(const string& nome, bool condicao) {
    testesExecutados++;
    if (condicao) {
        testesSucesso++;
        cout << "[OK] " << nome << endl;
    } else {
        cout << "[FALHA] " << nome << endl;
    }
}

void testeUsuario() {
    cout << "\n=== Testes de Usuário ===" << endl;
    
    GerenciadorUsuarios gerenciador;
    
    // Teste 1: Cadastrar usuário
    int id = gerenciador.cadastrar("João Silva", "joao", "senha123");
    testar("Cadastrar usuário", id == 1);
    
    // Teste 2: Buscar por ID
    Usuario* usuario = gerenciador.buscarPorId(id);
    testar("Buscar usuário por ID", usuario != nullptr);
    testar("Nome do usuário correto", usuario->getNome() == "João Silva");
    
    // Teste 3: Validar credenciais
    testar("Validar credenciais corretas", 
           usuario->validarCredenciais("joao", "senha123"));
    testar("Rejeitar credenciais incorretas", 
           !usuario->validarCredenciais("joao", "senhaErrada"));
    
    // Teste 4: Login duplicado
    bool excecaoLancada = false;
    try {
        gerenciador.cadastrar("Outro Usuario", "joao", "outraSenha");
    } catch (const UsuarioJaExisteException& e) {
        excecaoLancada = true;
    }
    testar("Exceção para login duplicado", excecaoLancada);
    
    // Teste 5: Listar usuários
    gerenciador.cadastrar("Maria", "maria", "senha456");
    testar("Listar 2 usuários", gerenciador.listar().size() == 2);
    
    // Teste 6: Remover usuário
    testar("Remover usuário", gerenciador.remover(id));
    testar("Usuário removido não existe", gerenciador.buscarPorId(id) == nullptr);
}

void testeArtista() {
    cout << "\n=== Testes de Artista ===" << endl;
    
    GerenciadorArtistas gerenciador;
    
    // Teste 1: Cadastrar artista
    int id = gerenciador.cadastrar("Madonna", 1);
    testar("Cadastrar artista", id == 1);
    
    // Teste 2: Buscar por ID
    Artista* artista = gerenciador.buscarPorId(id);
    testar("Buscar artista por ID", artista != nullptr);
    testar("Nome do artista correto", artista->getNome() == "Madonna");
    testar("Camarim ID correto", artista->getCamarimId() == 1);
    
    // Teste 3: Buscar por camarim
    gerenciador.cadastrar("Michael Jackson", 2);
    auto artistas = gerenciador.buscarPorCamarim(1);
    testar("Buscar artistas por camarim", artistas.size() == 1);
}

void testeItem() {
    cout << "\n=== Testes de Item ===" << endl;
    
    GerenciadorItens gerenciador;
    
    // Teste 1: Cadastrar item
    int id = gerenciador.cadastrar("Água Mineral", 2.50);
    testar("Cadastrar item", id == 1);
    
    // Teste 2: Buscar por ID
    Item* item = gerenciador.buscarPorId(id);
    testar("Buscar item por ID", item != nullptr);
    testar("Nome do item correto", item->getNome() == "Água Mineral");
    testar("Preço do item correto", item->getPreco() == 2.50);
    
    // Teste 3: Item duplicado
    bool excecaoLancada = false;
    try {
        gerenciador.cadastrar("Água Mineral", 3.00);
    } catch (const ItemException& e) {
        excecaoLancada = true;
    }
    testar("Exceção para item duplicado", excecaoLancada);
}

void testeEstoque() {
    cout << "\n=== Testes de Estoque ===" << endl;
    
    Estoque estoque;
    
    // Teste 1: Adicionar item
    estoque.adicionarItem(1, "Água", 100);
    testar("Adicionar item ao estoque", estoque.obterQuantidade(1) == 100);
    
    // Teste 2: Verificar disponibilidade
    testar("Verificar disponibilidade suficiente", 
           estoque.verificarDisponibilidade(1, 50));
    testar("Verificar disponibilidade insuficiente", 
           !estoque.verificarDisponibilidade(1, 200));
    
    // Teste 3: Remover item
    estoque.removerItem(1, 30);
    testar("Remover item do estoque", estoque.obterQuantidade(1) == 70);
    
    // Teste 4: Estoque insuficiente
    bool excecaoLancada = false;
    try {
        estoque.removerItem(1, 100);
    } catch (const EstoqueInsuficienteException& e) {
        excecaoLancada = true;
    }
    testar("Exceção para estoque insuficiente", excecaoLancada);
}

void testeCamarim() {
    cout << "\n=== Testes de Camarim ===" << endl;
    
    Camarim camarim(1, "Camarim VIP", 1);
    
    // Teste 1: Inserir item
    camarim.inserirItem(1, "Água", 10);
    testar("Inserir item no camarim", camarim.obterQuantidadeItem(1) == 10);
    testar("Verificar se contém item", camarim.contemItem(1));
    
    // Teste 2: Remover item
    camarim.removerItem(1, 5);
    testar("Remover item do camarim", camarim.obterQuantidadeItem(1) == 5);
    
    // Teste 3: Calcular total
    camarim.inserirItem(2, "Refrigerante", 15);
    testar("Calcular total de itens", camarim.calcularTotalItens() == 20);
    
    // Teste 4: Gerenciador
    GerenciadorCamarins gerenciador;
    int id = gerenciador.cadastrar("Camarim A", 1);
    testar("Cadastrar camarim", id == 1);
}

void testePedido() {
    cout << "\n=== Testes de Pedido ===" << endl;
    
    GerenciadorPedidos gerenciador;
    
    // Teste 1: Criar pedido
    int id = gerenciador.criar(1, "Madonna");
    testar("Criar pedido", id == 1);
    
    Pedido* pedido = gerenciador.buscarPorId(id);
    testar("Buscar pedido por ID", pedido != nullptr);
    testar("Pedido inicialmente não atendido", !pedido->isAtendido());
    
    // Teste 2: Adicionar itens
    pedido->adicionarItem(1, "Água", 10);
    pedido->adicionarItem(2, "Refrigerante", 5);
    testar("Adicionar 2 itens ao pedido", pedido->listarItens().size() == 2);
    
    // Teste 3: Marcar como atendido
    pedido->marcarAtendido();
    testar("Marcar pedido como atendido", pedido->isAtendido());
    
    // Teste 4: Não pode adicionar a pedido atendido
    bool excecaoLancada = false;
    try {
        pedido->adicionarItem(3, "Suco", 1);
    } catch (const PedidoException& e) {
        excecaoLancada = true;
    }
    testar("Exceção ao adicionar em pedido atendido", excecaoLancada);
}

void testeListaCompras() {
    cout << "\n=== Testes de Lista de Compras ===" << endl;
    
    GerenciadorListaCompras gerenciador;
    
    // Teste 1: Criar lista
    int id = gerenciador.criar("Compras Semanal");
    testar("Criar lista de compras", id == 1);
    
    ListaCompras* lista = gerenciador.buscarPorId(id);
    testar("Buscar lista por ID", lista != nullptr);
    
    // Teste 2: Adicionar itens
    lista->adicionarItem(1, "Água", 10, 2.50);
    lista->adicionarItem(2, "Refrigerante", 5, 5.00);
    testar("Adicionar 2 itens à lista", lista->listarItens().size() == 2);
    
    // Teste 3: Calcular total
    double total = lista->calcularTotal();
    testar("Calcular total correto", total == 50.00);  // 10*2.50 + 5*5.00
    
    // Teste 4: Atualizar quantidade
    lista->atualizarQuantidade(1, 20);
    total = lista->calcularTotal();
    testar("Atualizar quantidade e recalcular", total == 75.00);  // 20*2.50 + 5*5.00
}

void testePolimorfismo() {
    cout << "\n=== Testes de Polimorfismo ===" << endl;
    
    // Teste 1: Usuario como Pessoa
    Pessoa* pessoa1 = new Usuario(1, "João", "joao", "senha");
    string info = pessoa1->exibir();
    testar("Usuario exibe como Pessoa", info.find("Usuario") != string::npos);
    delete pessoa1;
    
    // Teste 2: Artista como Pessoa
    Pessoa* pessoa2 = new Artista(2, "Madonna", 1);
    info = pessoa2->exibir();
    testar("Artista exibe como Pessoa", info.find("Artista") != string::npos);
    delete pessoa2;
}

void testeExcecoes() {
    cout << "\n=== Testes de Exceções ===" << endl;
    
    // Teste 1: ValidacaoException
    bool capturada = false;
    try {
        throw ValidacaoException("Teste");
    } catch (const ExcecaoBase& e) {
        capturada = true;
    }
    testar("Capturar ValidacaoException", capturada);
    
    // Teste 2: EstoqueInsuficienteException
    capturada = false;
    Estoque estoque;
    estoque.adicionarItem(1, "Item", 5);
    try {
        estoque.removerItem(1, 10);
    } catch (const EstoqueInsuficienteException& e) {
        capturada = true;
    }
    testar("Capturar EstoqueInsuficienteException", capturada);
}

int main() {
    // Configurar codificação UTF-8 no Windows
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    
    cout << "\n╔═══════════════════════════════════════════════╗" << endl;
    cout << "║  SISTEMA DE TESTES - GESTÃO DE CAMARIM      ║" << endl;
    cout << "╚═══════════════════════════════════════════════╝\n" << endl;
    
    try {
        testeUsuario();
        testeArtista();
        testeItem();
        testeEstoque();
        testeCamarim();
        testePedido();
        testeListaCompras();
        testePolimorfismo();
        testeExcecoes();
        
        cout << "\n╔═══════════════════════════════════════════════╗" << endl;
        cout << "║              RESUMO DOS TESTES                ║" << endl;
        cout << "╠═══════════════════════════════════════════════╣" << endl;
        cout << "║  Executados: " << testesExecutados << " testes" << string(27 - to_string(testesExecutados).length(), ' ') << "║" << endl;
        cout << "║  Sucesso:    " << testesSucesso << " testes" << string(27 - to_string(testesSucesso).length(), ' ') << "║" << endl;
        cout << "║  Falhas:     " << (testesExecutados - testesSucesso) << " testes" << string(27 - to_string(testesExecutados - testesSucesso).length(), ' ') << "║" << endl;
        
        if (testesSucesso == testesExecutados) {
            cout << "╠═══════════════════════════════════════════════╣" << endl;
            cout << "║          ✓ TODOS OS TESTES PASSARAM!         ║" << endl;
        }
        cout << "╚═══════════════════════════════════════════════╝\n" << endl;
        
        return (testesSucesso == testesExecutados) ? 0 : 1;
        
    } catch (const exception& e) {
        cerr << "\n✗ Erro durante execução dos testes: " << e.what() << endl;
        return 1;
    }
}
