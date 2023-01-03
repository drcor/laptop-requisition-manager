#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "include/generic.h"
#include "include/laptops.h"

int menu(void);
void menuPortateis(typeLaptop **laptops, unsigned int *sizeLaptops);
void menuRequisicoes(void);
void menuAvarias(void);
void menuDados(void);


int main(void){
	unsigned int sizeLaptops = 0;
	typeLaptop *laptops = NULL;

	// Set locale for Portuguese
	setlocale(LC_ALL, "Portuguese");

	int opcao;
	
	do { 
		opcao = menu();
		switch (opcao) {
			case 0:
				break;
			case 1:
				menuPortateis(&laptops, &sizeLaptops);
				break;
			case 2:
				menuRequisicoes();
				break;
			case 3:
				menuAvarias();
				break;
			case 4:
				menuDados();
				break;
	   }
	} while(opcao != 0);
	
	return 0;
}

int menu(void) {
	int opcao;
			
	// This is the main menu
	printf("+------------------------------------------+\n");
	printf("|                   MENU                   |\n");
	printf("+------------------------------------------+\n");
	printf("|  [1] Port�teis                           |\n");
	printf("|  [2] Requisi��es                         |\n");
	printf("|  [3] Avarias                             |\n");
	printf("|  [4] Dados Estat�sticos                  |\n");
	printf("|  [0] Sair                                |\n");
	printf("+------------------------------------------+\n");
	opcao = lerInteiro("Op��o: ", 0, 4);

	return opcao;  
}

void menuPortateis(typeLaptop **laptops, unsigned int *sizeLaptops) {
	int opcao2;
	// If he chooses laptops this shows up
	printf("+------------------------------------------+\n");
	printf("|                Port�teis                 |\n");
	printf("+------------------------------------------+\n");                
	printf("|  [1] Inserir Port�teis                   |\n");
	printf("|  [2] Listar Port�teis                    |\n");
	printf("|  [3] Alterar Localiza��o do Port�til     |\n");
	printf("|  [0] Anterior                            |\n");
	printf("+------------------------------------------+\n");
	opcao2 = lerInteiro("Op��o", 0, 3);

	switch(opcao2) {
		case 1:
			insert_laptop(laptops, sizeLaptops);
			break;
		case 2:
			list_laptops(*laptops, *sizeLaptops);
			break;
		case 3:
			update_laptop_location(laptops, *sizeLaptops);
			break;
		case 0:
			printf("\n\nteste 0000\n");
			break;
	}
}

void menuRequisicoes() {
	int opcao2;
	printf("+------------------------------------------+\n");
	printf("|               Requisi��es                |\n");
	printf("+------------------------------------------+\n");
	printf("|  [1] Requisitar Port�til                 |\n");
	printf("|  [2] Listar Requisi��es                  |\n");
	printf("|  [3] Mostrar Requisi��o                  |\n");
	printf("|  [4] Devolu��o de Port�til Requisitado   |\n");
	printf("|  [5] Renovar Requisi��o                  |\n");
	printf("|  [0] Anterior                            |\n");
	printf("+------------------------------------------+\n");
	opcao2 = lerInteiro("Op��o", 0, 5);

	switch (opcao2) {
		case 1:
			printf("\nteste\n\n");
			// *op = lerInteiro("Deseja continuar no programa? N�o/Sim", 0, 1);  // Asks if the user wants to coninue the program               
			break;
		case 0:
			break;
	}      
}

void menuAvarias() {
	int opcao2;
	printf("+------------------------------------------+\n");
	printf("|                  Avarias                 |\n");
	printf("+------------------------------------------+\n");
	printf("|  [1] Registar Avaria                     |\n");
	printf("|  [2] Registar Repara��o                  |\n");
	printf("|  [0] Anterior                            |\n");
	printf("+------------------------------------------+\n");
	opcao2 = lerInteiro("Op��o", 0, 2);

	switch (opcao2) {
		case 1:

			break;
		case 0:
			break;
	}
}

void menuDados() {

}
