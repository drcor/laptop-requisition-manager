#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>
#include "include/generic.h"
#include "include/laptops.h"
#include "include/breakdowns.h"
#include "include/requests.h"

/* Inicializa e guarda os dados dos vetores em ficheiros binários */
void inicializarDados(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeRequest **requests, unsigned int *numberRequests);
void guardarDados(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);
/* Menus de opções */
int menu(void);
void menuPortateis(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);
void menuRequisicoes(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void menuAvarias(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void menuDados(void);
/* Aplicação de funcionalidades */
void registaAvaria(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void registaReparacao(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void registerRequest(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void listaAvarias(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void listaPortateis(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);

int main(void) {
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
				menuPortateis(&laptops, &numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
				break;
			case 2:
				menuRequisicoes(&requests, &numberRequests, laptops, numberLaptops);
				break;
			case 3:
				menuAvarias(&breakdowns, &numberBreakdowns, laptops, numberLaptops);
				break;
			case 4:
				menuDados();
				break;
			default:
				printf("\nATENÇÃO: Insira uma opção válida\n");
				break;
	   }
	} while(opcao != 0);

	guardarDados(laptops, numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
	
	free(laptops);
	free(breakdowns);
	free(requests);

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
	requests_file = fopen("requests.bin", "rb");
	// Read data
	if (laptops_file != NULL) {
		if (read_laptop_from_file(laptops, numberLaptops, laptops_file) == -1) {
			printf("laptops failed to read\n");
		}
		fclose(laptops_file);
	}
	if (breakdowns_file != NULL) {
		if (read_breakdown_from_file(breakdowns, numberBreakdowns, breakdowns_file) == -1) {
			printf("breakdowns failed to read\n");
		}
		fclose(breakdowns_file);
	}
	if (requests_file != NULL) {
		if (read_request_from_file(requests, numberRequests, requests_file) == -1) {
			printf("requests failed to read\n");
		}
		fclose(requests_file);
	}
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
	printf("\n +------------------------------------------+\n");
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

void menuPortateis(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests) {
	int opcao2;
	// If he chooses laptops this shows up
	printf("\n +------------------------------------------+\n");
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
			listaPortateis(*laptops, *numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
			printf("\n");
			break;
		case 3:
			update_laptop_location(laptops, *numberLaptops);
			break;
	}
}

void menuRequisicoes(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops) {
	int opcao2;

	printf("\n +------------------------------------------+\n");
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
			registerRequest(requests, numberRequests, laptops, numberLaptops);
			break;
		case 2:
			list_request(*requests, *numberRequests);
			break;
		}
}

void menuAvarias(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	int opcao2;
	printf("\n +------------------------------------------+\n");
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
				printf("\nATENÇÃO: Tem de inserir um ID existente\n");
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
				printf("\nATENÇÃO: Tem de inserir um ID existente\n");
			}
			if ((*breakdowns)[pos].duration != -1) {
				printf("\nATENÇÃO: Insira o ID de uma avaria ainda não reparada\n");
			}
		} while (pos == -1 || (*breakdowns)[pos].duration != -1);
		
		// Set laptop available for requisition and set duration of reparation
		breakdowns[pos]->duration = lerInteiro("Insira a duração da reparação", 0, 90);
		control = search_laptop_id(laptops, numberLaptops, breakdowns[pos]->laptop_id);
		laptops[control].state = AVAILABLE;
	}
}

void registerRequest(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops) {
	int control, laptop_id, pos;
	typeDate requisition_date;
	// Check if exists requests and laptops
	if (requests != NULL && laptops != NULL && numberLaptops > 0) {
		do {
			laptop_id = lerInteiro("Insira o id do laptop que deseja requisitar:", 1, MAX_LAPTOPS);
			pos = search_laptop_id(laptops, numberLaptops, laptop_id);
			
			if (pos == -1) {
				printf("\nATENÇÃO: Insira o ID de um laptop existente\n");
			}
		} while (pos == -1);

		// Get request date
		do {
			read_date("Insira a data de requisição", &(requisition_date));

			pos = compare_date(laptops[laptop_id].date, requisition_date);

			if (pos == -1) {	// if date is smaller than laptop date
				printf("\nATENÇÃO: A data tem de ser igual ou superior à data de aquisição do portátil\n");
			}
		} while (pos == -1);	// while date is smaller than laptop date

		control = insert_request(requests, numberRequests, laptop_id, requisition_date);
		if (control == 0) {
			// Set laptop state to taken
			laptops[pos].state = TAKEN;
		}

		printf("Registo de requisição concluído com sucesso\n");
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
		// printf("ID\tCPU\tMem.\tEstado\tLocal\tPreço\tID\tTipo\tDuração\tData\t\tDescrição\n");
		printf("ID\tTipo avaria\tData avaria\tDuraç.\tLID\tCPU\tMemor.\tEstado\t\tLocalização\tPreço\t\tDescrição\n");

		for (unsigned int i = 0; i < numberBreakdowns; i++) {	// Get breakdow by breakdown
			// Get position of laptop in vector of laptops
			pos = search_laptop_id(laptops, numberLaptops, breakdowns[i].laptop_id);
			// Print breakdown data
			printf("%d\t", breakdowns[i].id);
			print_typeBreak(breakdowns[i].break_type);
			printf("\t");
			print_date(breakdowns[i].date);
			printf("\t%d\t", breakdowns[i].duration);
			// Print laptop data
			printf("%d\t", laptops[pos].id);
			print_typeCPU(laptops[pos].cpu);
			printf("\t%dGB\t", laptops[pos].memory);
			print_typeState(laptops[pos].state);
			printf("\t");
			print_typeLocal(laptops[pos].location);
			printf("\\t    %.2f €\\t%s\n", laptops[pos].price, laptops[pos].description);
		}
	} else {
		printf("\nATENÇÃO: Não existe nenhuma avaria registada!\n");
	}
}

void listaPortateis(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests) {
	int counted;
	// Check if exist laptops
	if (laptops != NULL && numberLaptops > 0) {
		printf("ID\tCPU\tMemor.\tEstado\t\tLocalização\tPreço\t\tN.Avar\tN.Requi\tDescrição\n");

		for (unsigned int i = 0; i < numberLaptops; i++) {	// Get laptop by laptop
			// Print laptop data
			printf("%d\t", laptops[i].id);
			print_typeCPU(laptops[i].cpu);
			printf("\t%dGB\t", laptops[i].memory);
			print_typeState(laptops[i].state);
			printf("\t");
			print_typeLocal(laptops[i].location);
			printf("\t    %.2f €\t", laptops[i].price);
			
			counted = count_breakdowns_by_laptop_id(breakdowns, numberBreakdowns, laptops[i].id);
			printf("%d\t", counted);
			counted = count_requests_by_laptop_id(requests, numberRequests, laptops[i].id);
			printf("%d\t", counted);
			// TODO: Print type of user
			// TODO: Print deadline for each request
			printf("%s\n", laptops[i].description);
		}
	} else {
		printf("\nATENÇÃO: Não existe nenhum portátil registado!\n");
	}
}