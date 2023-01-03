#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "include/generic.h"
#include "include/laptops.h"
#include "include/breakdowns.h"

int menu(void);
void menuPortateis(typeLaptop **laptops, unsigned int *sizeLaptops);
void menuRequisicoes(void);
void menuAvarias(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void menuDados(void);
void registaAvaria(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void listaAvarias(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);

int main(void){
	unsigned int sizeLaptops = 0;
	typeLaptop *laptops = NULL;
	unsigned int sizeBreakdowns = 0;
	typeBreakdown *breakdowns = NULL;

	// Set locale for Portuguese
	setlocale(LC_ALL, "Portuguese");

	int opcao;
	
	// Apresenta o menu principal de opções
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
				menuAvarias(&breakdowns, &sizeBreakdowns, laptops, sizeLaptops);
				break;
			case 4:
				menuDados();
				break;
			default:
				printf("ATENÇÃO: Insira uma Opção válida\n");
				break;
	   }
	} while(opcao != 0);
	
	return 0;
}

// Mostra o menu principal e retorna uma Opção
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
	printf("|  [3] Alterar Localização do portátil     |\n");
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
	}
}

void menuRequisicoes() {
	int opcao2;
	printf("+------------------------------------------+\n");
	printf("|               Requisições                |\n");
	printf("+------------------------------------------+\n");
	printf("|  [1] Requisitar portátil                 |\n");
	printf("|  [2] Listar Requisições                  |\n");
	printf("|  [3] Mostrar Requisição                  |\n");
	printf("|  [4] Devolução de portátil Requisitado   |\n");
	printf("|  [5] Renovar Requisição                  |\n");
	printf("|  [0] Anterior                            |\n");
	printf("+------------------------------------------+\n");
	opcao2 = lerInteiro("Opção", 0, 5);

	switch (opcao2) {
		case 1:
			printf("\nteste\n\n");
			// *op = lerInteiro("Deseja continuar no programa? não/Sim", 0, 1);  // Asks if the user wants to coninue the program               
			break;
		}
}

void menuAvarias(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
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
			registaAvaria(breakdowns, numberBreakdowns, laptops, numberLaptops);
			break;
		case 3:
			listaAvarias(*breakdowns, *numberBreakdowns, laptops, numberLaptops);
			break;
	}
}

void menuDados() {

}

/**
 * @brief Regista uma Avaria
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param laptops 
 * @param numberLaptops 
 */
void registaAvaria(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	int pos, control, id;
	// Check if exist laptops and breakdowns
	if (*breakdowns != NULL && *numberBreakdowns > 0 && laptops != NULL && numberLaptops > 0) {
		// Read id
		do {
			id = lerInteiro("Insira o ID do portátil avariado", 1, MAX_LAPTOPS);
			pos = search_laptop_id(laptops, numberLaptops, id);	// TODO: search_breakdown_id()
			if (pos == -1) {
				printf("ATENÇÃO: Tem de inserir um ID existente\n");
			}
		} while (pos == -1);

		control = insert_breakdown(breakdowns, numberBreakdowns, id);
		if (control == 0) {
			laptops[pos].state = BROKEN;
		}
	}
} 

/**
 * @brief Mostra os dados do portátil e das avarias juntos
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param laptops 
 * @param numberLaptops 
 */
void listaAvarias(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	int pos;
	// Check if exist laptops and breakdowns
	if (breakdowns != NULL && numberBreakdowns > 0) {
		printf("ID\tCPU\tMem.\tEstado\tLocal\tMulta\tTipo\tDuração\tData\t\tDescrição\n");

		for (unsigned int i = 0; i < numberBreakdowns; i++) {	// Get breakdow by breakdown
			// Get position of laptop in vector of laptops
			pos = search_laptop_id(laptops, numberLaptops, breakdowns[i].laptop_id);
			printf("%d\ti%d\t%dGB\t", laptops[pos].id, laptops[pos].cpu, laptops[pos].memory);
			printf("%d\t%d\t", laptops[pos].state, laptops[pos].location);
			printf("%.2f\t%d\t", laptops[pos].price, breakdowns[i].break_type);
			printf("%d\t", breakdowns[i].duration);
			print_date(breakdowns[i].date);
			printf("\t%d\t%s\n", breakdowns[i].duration, laptops[pos].description);
		}
	} else {
		printf("ATENÇÃO: não existe nenhuma avaria registada!\n");
	}
}