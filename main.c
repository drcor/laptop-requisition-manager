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
	printf("|  [1] Portáteis                           |\n");
	printf("|  [2] Requisições                         |\n");
	printf("|  [3] Avarias                             |\n");
	printf("|  [4] Dados Estatísticos                  |\n");
	printf("|  [0] Sair                                |\n");
	printf("+------------------------------------------+\n");
	opcao = lerInteiro("Opção: ", 0, 4);

	return opcao;  
}

void menuPortateis(typeLaptop **laptops, unsigned int *sizeLaptops) {
	int opcao2;
	// If he chooses laptops this shows up
	printf("+------------------------------------------+\n");
	printf("|                Portáteis                 |\n");
	printf("+------------------------------------------+\n");                
	printf("|  [1] Inserir Portáteis                   |\n");
	printf("|  [2] Listar Portáteis                    |\n");
	printf("|  [3] Alterar Localização do Portátil     |\n");
	printf("|  [0] Anterior                            |\n");
	printf("+------------------------------------------+\n");
	opcao2 = lerInteiro("Opção", 0, 3);

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
	printf("|               Requisições                |\n");
	printf("+------------------------------------------+\n");
	printf("|  [1] Requisitar Portátil                 |\n");
	printf("|  [2] Listar Requisições                  |\n");
	printf("|  [3] Mostrar Requisição                  |\n");
	printf("|  [4] Devolução de Portátil Requisitado   |\n");
	printf("|  [5] Renovar Requisição                  |\n");
	printf("|  [0] Anterior                            |\n");
	printf("+------------------------------------------+\n");
	opcao2 = lerInteiro("Opção", 0, 5);

	switch (opcao2) {
		case 1:
			printf("\nteste\n\n");
			// *op = lerInteiro("Deseja continuar no programa? Não/Sim", 0, 1);  // Asks if the user wants to coninue the program               
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
	printf("|  [2] Registar Reparação                  |\n");
	printf("|  [0] Anterior                            |\n");
	printf("+------------------------------------------+\n");
	opcao2 = lerInteiro("Opção", 0, 2);

	switch (opcao2) {
		case 1:

			break;
		case 0:
			break;
	}
}

void menuDados() {

}
