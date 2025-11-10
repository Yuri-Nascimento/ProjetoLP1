#include <iostream>
#include <string>
#include <limits>
#include "usuario.h"
#include "artista.h"
#include "item.h"
#include "estoque.h"
#include "camarim.h"
#include "pedido.h"
#include "listacompras.h"
#include "excecoes.h"

using namespace std;

// Gerenciadores globais
GerenciadorUsuarios gerenciadorUsuarios;
GerenciadorArtistas gerenciadorArtistas;
GerenciadorItens gerenciadorItens;
Estoque estoque;
GerenciadorCamarins gerenciadorCamarins;
GerenciadorPedidos gerenciadorPedidos;
GerenciadorListaCompras gerenciadorListaCompras;

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ==================== Funções de Usuário ====================

void exibirUsuarios() {
    vector<Usuario> usuarios = gerenciadorUsuarios.listar();
    if (usuarios.empty()) {
        cout << "\nNenhum usuário cadastrado.\n" << endl;
        return;
    }
    
    cout << "\n=== Lista de Usuários ===" << endl;
    for (const auto& usuario : usuarios) {
        cout << usuario.exibir() << endl;
    }
}

void cadastrarUsuario() {
    string nome, login, senha;
    
    cout << "\n=== Cadastrar Usuário ===" << endl;
    limparBuffer();
    
    cout << "Nome: ";
    getline(cin, nome);
    
    cout << "Login: ";
    getline(cin, login);
    
    cout << "Senha: ";
    getline(cin, senha);
    
    try {
        int id = gerenciadorUsuarios.cadastrar(nome, login, senha);
        cout << "\n[OK] Usuário cadastrado com ID: " << id << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerUsuario() {
    int id;
    cout << "\n=== Remover Usuário ===" << endl;
    cout << "Digite o ID do usuário: ";
    cin >> id;
    
    try {
        gerenciadorUsuarios.remover(id);
        cout << "\n[OK] Usuário removido com sucesso!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

// ==================== Funções de Artista ====================

void exibirArtistas() {
    vector<Artista> artistas = gerenciadorArtistas.listar();
    if (artistas.empty()) {
        cout << "\nNenhum artista cadastrado.\n" << endl;
        return;
    }
    
    cout << "\n=== Lista de Artistas ===" << endl;
    for (const auto& artista : artistas) {
        cout << artista.exibir() << endl;
    }
}

void cadastrarArtista() {
    string nome;
    int camarimId;
    
    cout << "\n=== Cadastrar Artista ===" << endl;
    limparBuffer();
    
    cout << "Nome: ";
    getline(cin, nome);
    
    cout << "ID do Camarim: ";
    cin >> camarimId;
    
    try {
        int id = gerenciadorArtistas.cadastrar(nome, camarimId);
        cout << "\n[OK] Artista cadastrado com ID: " << id << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerArtista() {
    int id;
    cout << "\n=== Remover Artista ===" << endl;
    cout << "Digite o ID do artista: ";
    cin >> id;
    
    try {
        gerenciadorArtistas.remover(id);
        cout << "\n[OK] Artista removido com sucesso!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

// ==================== Funções de Estoque ====================

void exibirEstoque() {
    auto itens = estoque.listar();
    if (itens.empty()) {
        cout << "\nEstoque vazio.\n" << endl;
        return;
    }
    
    cout << "\n=== Estoque ===" << endl;
    cout << estoque << endl;
}

void cadastrarItemEstoque() {
    int itemId, quantidade;
    string nome;
    
    cout << "\n=== Adicionar Item ao Estoque ===" << endl;
    cout << "ID do Item: ";
    cin >> itemId;
    limparBuffer();
    
    cout << "Nome do Item: ";
    getline(cin, nome);
    
    cout << "Quantidade: ";
    cin >> quantidade;
    
    try {
        estoque.adicionarItem(itemId, nome, quantidade);
        cout << "\n[OK] Item adicionado ao estoque!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerItemEstoque() {
    int itemId, quantidade;
    
    cout << "\n=== Remover Item do Estoque ===" << endl;
    cout << "ID do Item: ";
    cin >> itemId;
    
    cout << "Quantidade a remover: ";
    cin >> quantidade;
    
    try {
        estoque.removerItem(itemId, quantidade);
        cout << "\n[OK] Item removido do estoque!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

// ==================== Funções de Camarim ====================

void exibirCamarins() {
    vector<Camarim> camarins = gerenciadorCamarins.listar();
    if (camarins.empty()) {
        cout << "\nNenhum camarim cadastrado.\n" << endl;
        return;
    }
    
    cout << "\n=== Lista de Camarins ===" << endl;
    for (const auto& camarim : camarins) {
        cout << camarim << endl;
    }
}

void cadastrarItemCamarim() {
    int camarimId, itemId, quantidade;
    string nome;
    
    cout << "\n=== Adicionar Item ao Camarim ===" << endl;
    cout << "ID do Camarim: ";
    cin >> camarimId;
    
    Camarim* camarim = gerenciadorCamarins.buscarPorId(camarimId);
    if (!camarim) {
        cout << "\n[ERRO] Camarim não encontrado!" << endl;
        return;
    }
    
    cout << "ID do Item: ";
    cin >> itemId;
    limparBuffer();
    
    cout << "Nome do Item: ";
    getline(cin, nome);
    
    cout << "Quantidade: ";
    cin >> quantidade;
    
    try {
        camarim->inserirItem(itemId, nome, quantidade);
        cout << "\n[OK] Item adicionado ao camarim!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerItemCamarim() {
    int camarimId, itemId, quantidade;
    
    cout << "\n=== Remover Item do Camarim ===" << endl;
    cout << "ID do Camarim: ";
    cin >> camarimId;
    
    Camarim* camarim = gerenciadorCamarins.buscarPorId(camarimId);
    if (!camarim) {
        cout << "\n[ERRO] Camarim não encontrado!" << endl;
        return;
    }
    
    cout << "ID do Item: ";
    cin >> itemId;
    
    cout << "Quantidade a remover: ";
    cin >> quantidade;
    
    try {
        camarim->removerItem(itemId, quantidade);
        cout << "\n[OK] Item removido do camarim!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

// ==================== Funções de Pedidos ====================

void exibirPedidos() {
    vector<Pedido> pedidos = gerenciadorPedidos.listar();
    if (pedidos.empty()) {
        cout << "\nNenhum pedido cadastrado.\n" << endl;
        return;
    }
    
    cout << "\n=== Lista de Pedidos ===" << endl;
    for (const auto& pedido : pedidos) {
        cout << pedido << endl;
    }
}

void cadastrarPedido() {
    int camarimId;
    string nomeArtista;
    
    cout << "\n=== Criar Pedido ===" << endl;
    cout << "ID do Camarim: ";
    cin >> camarimId;
    limparBuffer();
    
    cout << "Nome do Artista: ";
    getline(cin, nomeArtista);
    
    try {
        int id = gerenciadorPedidos.criar(camarimId, nomeArtista);
        cout << "\n[OK] Pedido criado com ID: " << id << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerPedido() {
    int id;
    cout << "\n=== Remover Pedido ===" << endl;
    cout << "Digite o ID do pedido: ";
    cin >> id;
    
    try {
        gerenciadorPedidos.remover(id);
        cout << "\n[OK] Pedido removido com sucesso!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

// ==================== Funções de Lista de Compras ====================

void exibirListasCompras() {
    vector<ListaCompras> listas = gerenciadorListaCompras.listar();
    if (listas.empty()) {
        cout << "\nNenhuma lista de compras cadastrada.\n" << endl;
        return;
    }
    
    cout << "\n=== Listas de Compras ===" << endl;
    for (const auto& lista : listas) {
        cout << lista << endl;
    }
}

void cadastrarListaCompras() {
    string descricao;
    
    cout << "\n=== Criar Lista de Compras ===" << endl;
    limparBuffer();
    
    cout << "Descrição: ";
    getline(cin, descricao);
    
    try {
        int id = gerenciadorListaCompras.criar(descricao);
        cout << "\n[OK] Lista de compras criada com ID: " << id << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}

void removerListaCompras() {
    int id;
    cout << "\n=== Remover Lista de Compras ===" << endl;
    cout << "Digite o ID da lista: ";
    cin >> id;
    
    try {
        gerenciadorListaCompras.remover(id);
        cout << "\n[OK] Lista de compras removida com sucesso!" << endl;
    } catch (const ExcecaoBase& e) {
        cout << "\n[ERRO] " << e.what() << endl;
    }
}


void menuPrincipal(){
    cout << "____Menu de Principal___" << endl;
    cout << "1. Usuários" << endl;
    cout << "2. Estoque" << endl;
    cout << "3. Camarim" << endl;
    cout << "4. Artista" << endl;
    cout << "5. Lista de Pedidos" << endl;
    cout << "6. Lista de Compras" << endl;
    cout << "0. Finalizar" << endl;
}

void menuSub(){
    cout << "1. Exibir" << endl;
    cout << "2. Cadastrar" << endl;
    cout << "3. Remover" << endl;
    cout << "0. Retornar" << endl;
}




int main(){
    // Configurar codificação UTF-8 no Windows
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    
    int opcao1, opcao2;
    
    do {
        menuPrincipal();
        cout << "\nDigite uma opção: ";
        
        cin >> opcao1;
        cout << endl;
        
            switch(opcao1){
                case 1: 
                do {
                    //Chama o submenu 1.Usários e aguarda interação
                    
                    cout << "Menu de Usuários: \n";
                    menuSub();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirUsuarios();
                        break;
                        
                        case 2: 
                        cadastrarUsuario();
                        break;
                        
                        case 3: 
                        removerUsuario();
                        break;
                        
                        case 0: cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                break;
                
                
                case 2:  
                do {
                    //Chama o submenu 2.Estoque e aguarda interação
                    
                    cout << "Menu de Estoque: \n";
                    menuSub();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirEstoque();
                        break;
                        
                        case 2: 
                        cadastrarItemEstoque();
                        break;
                        
                        case 3: 
                        removerItemEstoque();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 3:  
                do {
                    //Chama o submenu 3.Camarim e aguarda interação
                    
                    cout << "Menu de Camarim: \n";
                    menuSub();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirCamarins();
                        break;
                        
                        case 2: 
                        cadastrarItemCamarim();
                        break;
                        
                        case 3: 
                        removerItemCamarim();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 4:  
                do {
                    //Chama o submenu 4.Artistas e aguarda interação
                    
                    cout << "Menu de Artistas: \n";
                    menuSub();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirArtistas();
                        break;
                        
                        case 2: 
                        cadastrarArtista();
                        break;
                        
                        case 3: 
                        removerArtista();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 5:  
                do {
                    //Chama o submenu 4.Lista de Pedidos e aguarda interação
                    
                    cout << "Menu de Lista de Pedidos: \n";
                    menuSub();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirPedidos();
                        break;
                        
                        case 2: 
                        cadastrarPedido();
                        break;
                        
                        case 3: 
                        removerPedido();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 6:  
                do {
                    //Chama o submenu 5.Lista de Compras e aguarda interação
                    
                    cout << "Menu de Lista de Compras: \n";
                    menuSub();
                    cout << "\nDigite uma opção: ";
                    cin >> opcao2;
                    cout << endl;
                    
                    switch (opcao2){
                        case 1: 
                        exibirListasCompras();
                        break;
                        
                        case 2: 
                        cadastrarListaCompras();
                        break;
                        
                        case 3: 
                        removerListaCompras();
                        break;
                        
                        case 0: 
                        cout << "\nRetornando ao menu principal...\n" << endl;
                        break;
                        
                        default: cout <<"Digite uma opção válida...\n" << endl;
                    }
                } while (opcao2 != 0);
                
                break;
                
                case 0: cout << "Finalizando programa"; break; 
                default: cout <<"Digite uma opção válida...\n" << endl; // retorna ao menu principal
                
            }
            
        
    
    } while (opcao1 != 0);
    
    
}
