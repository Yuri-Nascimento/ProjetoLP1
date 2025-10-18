#ifndef CAMARIM_H
#define CAMARIM_H

class Camarim {
public:
	int id; // ID do camarim
	string nome; //Nome do camarim, se necessC!rio


// MC)todos principais
	void inserirItem(int valor); // Inserir produto atraves de cC3digo e nC#o de nome
	void removerItemCamarim(int valor);
	void verif_Camarim(int valor); // Verificar total de itens de um Camarim
	void verif_ItemPorCamarim(int valor);// Verificar um iten ao longo dos camarins


}

classe Estoque{
public:
	string nome;
	int quantidade;

    void removerItem(int valor);

}