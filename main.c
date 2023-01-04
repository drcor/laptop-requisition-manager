#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "include/generic.h"
#include "include/laptops.h"
#include "include/breakdowns.h"
#include "include/requests.h"

void inicializarDados(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeRequest **requests, unsigned int *numberRequests);
void guardarDados(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);
int menu(void);
void menuPortateis(typeLaptop **laptops, unsigned int *numberLaptops);
void menuRequisicoes(void);
void menuAvarias(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void menuDados(void);
void registaAvaria(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void registaReparacao(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void listaAvarias(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);

int main(void){
	unsigned int numberLaptops = 0;
	unsigned int numberBreakdowns = 0;
	unsigned int numberRequests = 0;
	typeLaptop *laptops = NULL;
	typeBreakdown *breakdowns = NULL;
	typeRequest *requests = NULL;
	int opcao;

	// Set locale for Portuguese
	setlocale(LC_ALL, "Portuguese");

	// Inicializa vetores com dados dos ficheiros
	inicializarDados(&laptops, &numberLaptops, &breakdowns, &numberBreakdowns, &requests, &numberRequests);
	
	// Apresenta o menu principal de opções
	do {
		opcao = menu();
		switch (opcao) {
			case 0:
				break;
			case 1:
				menuPortateis(&laptops, &numberLaptops);
				break;
			case 2:
				menuRequisicoes();
				break;
			case 3:
				menuAvarias(&breakdowns, &numberBreakdowns, laptops, numberLaptops);
				break;
			case 4:
				menuDados();
				break;
			default:
				printf("ATENÇÃO: Insira uma Opção válida\n");
				break;
	   }
	} while(opcao != 0);

	guardarDados(laptops, numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
	
	free(laptops);
	free(breakdowns);

	return 0;
}

void inicializarDados(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeRequest **requests, unsigned int *numberRequests) {
	// Initialize vector with data from files
	FILE *laptops_file = NULL;
	FILE *breakdowns_file = NULL;
	FILE *requests_file = NULL;
	// Open data files
	laptops_file = fopen("laptops.bin", "rb");
	breakdowns_file = fopen("breakdowns.bin", "rb");
	// Read data
	read_laptop_from_file(laptops, numberLaptops, laptops_file);
	read_breakdown_from_file(breakdowns, numberBreakdowns, breakdowns_file);
	read_request_from_file(requests, numberRequests, requests_file);
	// Close files
	fclose(laptops_file);
	fclose(breakdowns_file);
	fclose(requests_file);
}

void guardarDados(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests) {
	// Save vector data to files
	FILE *laptops_file = NULL;
	FILE *breakdowns_file = NULL;
	FILE *requests_file = NULL;
	// Open data files
	laptops_file = fopen("laptops.bin", "wb");
	breakdowns_file = fopen("breakdowns.bin", "wb");
	requests_file = fopen("requests.bin", "wb");
	// Read data
	write_laptop_to_file(laptops, numberLaptops, laptops_file);
	write_breakdown_to_file(breakdowns, numberBreakdowns, breakdowns_file);
	write_request_to_file(requests, numberRequests, requests_file);
	// Close files
	fclose(laptops_file);
	fclose(breakdowns_file);
	fclose(requests_file);
}

// Mostra o menu principal e retorna uma Opção
int menu(void) {
	int opcao;
			
	// This is the main menu
	printf("\n+------------------------------------------+\n");
	printf(" |                   MENU                   |\n");
	printf(" +------------------------------------------+\n");
	printf(" |  [1] Portáteis                           |\n");
	printf(" |  [2] Requisições                         |\n");
	printf(" |  [3] Avarias                             |\n");
	printf(" |  [4] Dados Estatísticos                  |\n");
	printf(" |  [0] Sair                                |\n");
	printf(" +------------------------------------------+\n");
	opcao = lerInteiro("Opção: ", 0, 4);

	return opcao;  
}

void menuPortateis(typeLaptop **laptops, unsigned int *numberLaptops) {
	int opcao2;
	// If he chooses laptops this shows up
	printf("\n+------------------------------------------+\n");
	printf(" |                Portáteis                 |\n");
	printf(" +------------------------------------------+\n");                
	printf(" |  [1] Inserir Portáteis                   |\n");
	printf(" |  [2] Listar Portáteis                    |\n");
	printf(" |  [3] Alterar Localização do portátil     |\n");
	printf(" |  [0] Anterior                            |\n");
	printf(" +------------------------------------------+\n");
	opcao2 = lerInteiro("Opção", 0, 3);

	switch(opcao2) {
		case 1:
			insert_laptop(laptops, numberLaptops);
			break;
		case 2:
			printf("\n");
			list_laptops(*laptops, *numberLaptops);
			printf("\n");
			break;
		case 3:
			update_laptop_location(laptops, *numberLaptops);
			break;
	}
}

void menuRequisicoes() {
	int opcao2;
	printf("\n+------------------------------------------+\n");
	printf(" |               Requisições                |\n");
	printf(" +------------------------------------------+\n");
	printf(" |  [1] Requisitar portátil                 |\n");
	printf(" |  [2] Listar Requisições                  |\n");
	printf(" |  [3] Mostrar Requisição                  |\n");
	printf(" |  [4] Devolução de portátil Requisitado   |\n");
	printf(" |  [5] Renovar Requisição                  |\n");
	printf(" |  [0] Anterior                            |\n");
	printf(" +------------------------------------------+\n");
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
	printf("\n+------------------------------------------+\n");
	printf(" |                  Avarias                 |\n");
	printf(" +------------------------------------------+\n");
	printf(" |  [1] Registar Avaria                     |\n");
	printf(" |  [2] Registar Reparação                  |\n");
	printf(" |  [3] Listar Avarias                      |\n");
	printf(" |  [0] Anterior                            |\n");
	printf(" +------------------------------------------+\n");
	opcao2 = lerInteiro("Opção", 0, 3);

	switch (opcao2) {
		case 1:
			registaAvaria(breakdowns, numberBreakdowns, laptops, numberLaptops);
			break;
		case 2:
			registaReparacao(breakdowns, numberBreakdowns, laptops, numberLaptops);
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
	if (breakdowns != NULL && laptops != NULL && numberLaptops > 0) {
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

void registaReparacao(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	int pos, control, id;
	// Check if exist laptops and breakdowns
	if (*breakdowns != NULL && laptops != NULL && numberLaptops > 0) {
		// Read id
		do {
			id = lerInteiro("Insira o ID da avaria", 1, INT_MAX);
			pos = search_breakdown_id(*breakdowns, *numberBreakdowns, id);
			if (pos == -1) {
				printf("ATENÇÃO: Tem de inserir um ID existente\n");
			}
			if ((*breakdowns)[id].duration != -1) {
				printf("ATENÇÃO: Insira o ID de uma avaria ainda não reparada\n");
			}
		} while (pos == -1 && (*breakdowns)[id].duration != -1);
		
		// Set laptop available for requisition and set duration of reparation
		breakdowns[pos]->duration = lerInteiro("Insira a duração da reparação", 0, 90);
		control = search_laptop_id(laptops, numberLaptops, breakdowns[pos]->laptop_id);
		laptops[control].state = AVAILABLE;
		// control = delete_breakdown(breakdowns, numberBreakdowns, id);
		// if (control == 0) {
		// 	laptops[pos].state = AVAILABLE;
		// }
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
	if (breakdowns != NULL && numberBreakdowns > 0) {	// If exist breakdowns then have to exist at least a laptop
		printf("ID\tCPU\tMem.\tEstado\tLocal\tMulta\tID\tTipo\tDuração\tData\t\tDescrição\n");

		for (unsigned int i = 0; i < numberBreakdowns; i++) {	// Get breakdow by breakdown
			// Get position of laptop in vector of laptops
			pos = search_laptop_id(laptops, numberLaptops, breakdowns[i].laptop_id);
			printf("%d\ti%d\t%dGB\t", laptops[pos].id, laptops[pos].cpu, laptops[pos].memory);
			printf("%d\t%d\t", laptops[pos].state, laptops[pos].location);
			printf("%.2f\t%d\t%d\t", laptops[pos].price, breakdowns[i].id, breakdowns[i].break_type);
			printf("%d\t", breakdowns[i].duration);
			print_date(breakdowns[i].date);
			printf("\t%s\n", laptops[pos].description);
		}
	} else {
		printf("ATENÇÃO: não existe nenhuma avaria registada!\n");
	}
}