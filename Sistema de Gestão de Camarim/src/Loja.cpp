// Metropole Veste: Loja de roupas, bolsas e calçados  

#include <iostream>
using namespace std;


/* 
Classes: 
    masculino: 
        calça
            preço, tamanho, cor, quantidade
        camisetas
            preço, tamanho, cor, quantidade
        moletons,
            preço, tamanho, cor, quantidade
        tênis
            preço, tamanho, cor, quantidade
        jaquetas
            preço, tamanho, cor, quantidade

    feminino: 
        vestidos 
            preço, tamanho, cor, quantidade
        saias
            preço, tamanho, cor, quantidade
        blusas
            preço, tamanho, cor, quantidade
        sandálias 
            preço, tamanho, cor, quantidade
        bolsas
            preço, tamanho, cor, quantidade
            
*/


class Masculino{
    public:
    Calca calca;
    Camiseta camiseta;
    Moletons moletom;
    Tenis tenis;
    Jaquetas jaqueta;
       
};
class Feminino{
    public:
    Vestidos vestido;
    Saias saia;
    Blusas blusa;
    Sandalias sandalia;
    Bolsas bolsa;
       
};
class Calca : public Masculino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};

class Camiseta : public Masculino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};

class Moletons : public Masculino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};

class Tenis : public Masculino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};

class Jaquetas : public Masculino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};

class Vestidos : public Feminino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};

class Saias : public Feminino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};

class Blusas : public Feminino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};

class Sandalias : public Feminino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};

class Bolsas : public Feminino{
    public:
    string cor;
    string tamanho;
    float preco;
    int quantidade;
};




int main(){
    //Declaração de variáveis
    int operacao;
    
    //Prompt para escolha de operação
    cout << "Escolha a operação de dados desejada: \n" << "1. Cadastro\n" << "2. Consulta\n" << "3. Alteração\n" 
    << "4. Remoção\n" << endl; 
    cin >> operacao;
  
    //Condicional para tomada de decisação baseado na escolha
    switch (operacao){ 
        
        case 1:
            //codigo à implementar
            cout << "Implementar função Cadastro\n";
            break;
        
        case 2: 
            //codigo à implementar
            cout << "Implementar função Consulta\n";
            break; 
                
        case 3:
            //codigo à implementar
            cout << "Implementar função Alteração\n";
            break;
            
        case 4: 
            //codigo à implementar
            cout << "Implementar função Remoção\n";
            break;
    }
    
   



    return 0;
}




