#include <iostream>
using namespace std;

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
                        cout << "Chama função exibirUsuarios() \n" << endl; 
                        break;
                        
                        case 2: 
                        cout << "Chama função cadastrarUsuarios() \n"<< endl;
                        break;
                        
                        case 3: 
                        cout << "Chama função removerUsuarios() \n"<< endl;
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
                        cout << "Chama função exibirEstoque() \n" << endl; 
                        break;
                        
                        case 2: 
                        cout << "Chama função cadastrarItemEstoque() \n"<< endl;
                        break;
                        
                        case 3: 
                        cout << "Chama função removerItemEstoque() \n"<< endl;
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
                        cout << "Chama função exibirCamarim() \n" << endl;
                        cout << "Camarim1: \nArtista_X; \nItem_A_10und; \nItem_B_100und;\n" << endl;
                        cout << "Camarim1: \nArtista_Y; \nItem_C_1und; \nItem_D_15und;\n" << endl;
                        cout << "Camarim2: \nArtista_Z; \nItem_C_1und; \nItem_D_15und;\n" << endl;
                        cout << "Camarim3: \nArtista_W; \nItem_C_1und; \nItem_D_15und;\n" << endl;
                        cout << "Camarim4: \nArtista_ZZ; \nItem_C_1und; \nItem_D_15und;\n" << endl;
                        break;
                        
                        case 2: 
                        cout << "Chama função cadastrarItemCamarim() \n"<< endl;
                        break;
                        
                        case 3: 
                        cout << "Chama função removerItemCamarim() \n"<< endl;
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
                        cout << "Chama função exibirArtistas() \n" << endl;
                        cout << "\n ID_1; Artista_X; Camarim1:" << endl;
                        cout << "\n ID_2; Artista_Y; Camarim3:" << endl;
                        break;
                        
                        case 2: 
                        cout << "Chama função cadastrarArtistas() \n"<< endl;
                        break;
                        
                        case 3: 
                        cout << "Chama função removerArtistas() \n"<< endl;
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
                        cout << "Chama função exibirListaPedido() \n" << endl;
                        cout << "\n Artista_X; Camarim_2 \nItem_A_10und \nItem_C_1und" << endl;
                        break;
                        
                        case 2: 
                        cout << "Chama função cadastrarPedido() \n"<< endl;
                        break;
                        
                        case 3: 
                        cout << "Chama função removerPedido() \n"<< endl;
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
                        cout << "Chama função exibirListaCompras() \n" << endl;
                        cout << "\n Artista_X; Camarim_2 \nItem_A_10und \nItem_C_1und" << endl;
                        break;
                        
                        case 2: 
                        cout << "Chama função cadastrarCompras() \n"<< endl;
                        break;
                        
                        case 3: 
                        cout << "Chama função removerCompras() \n"<< endl;
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
