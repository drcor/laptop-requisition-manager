#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>
#include "include/generic.h"
#include "include/laptops.h"
#include "include/breakdowns.h"
#include "include/requests.h"

/* Initialize and save the vectors data in binary */
void initialize_data(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeRequest **requests, unsigned int *numberRequests);
void save_data(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);
void save_request_to_log(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops, int pos);
/* Options menus */
int menu(void);
void menu_laptops(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);
void menu_requests(void);
void menu_breakdowns(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void menu_statistics(void);
/* Declaration of menus functionalities */
void register_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void register_repair(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void register_devolution(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void renovate_request(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void list_breakdowns(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void list_laptops(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);

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

	// Initialize vectors with data
	initialize_data(&laptops, &numberLaptops, &breakdowns, &numberBreakdowns, &requests, &numberRequests);
	
	// Show main menu
	do {
		opcao = menu();
		switch (opcao) {
			case 0:
				break;
			case 1:
				menu_laptops(&laptops, &numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
				break;
			case 2:
				menu_requests();
				break;
			case 3:
				menu_breakdowns(&breakdowns, &numberBreakdowns, laptops, numberLaptops);
				break;
			case 4:
				menu_statistics();
				break;
			default:
				printf("ATENÇÃO: Insira uma opção válida\n");
				break;
	   }
	} while(opcao != 0);

	save_data(laptops, numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
	
	free(laptops);
	free(breakdowns);
	free(requests);

	return 0;
}

// Read binary files to vectors
void initialize_data(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeRequest **requests, unsigned int *numberRequests) {
	// Initialize vector with data from files
	FILE *laptops_file;
	FILE *breakdowns_file;
	FILE *requests_file;
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

// Save vectors to binary files
void save_data(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests) {
	// Save vector data to files
	FILE *laptops_file;
	FILE *breakdowns_file;
	FILE *requests_file;
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

/**
 * @brief Save a request to a log file
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptops 
 * @param numberLaptops 
 */
void save_request_to_log(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops, int pos) {
	FILE *log_file;
	int laptop_pos;
	
	if (requests != NULL && numberRequests > 0 && laptops != NULL && numberLaptops > 0) {
		log_file = fopen("requests.log", "a");
		if (log_file != NULL) {
			// Print devolution date
			fprintf(log_file, "%02d/%02d/%04d\t", requests[pos].devolution_date.day, requests[pos].devolution_date.month, requests[pos].devolution_date.year);
			fprintf(log_file, "Código: %s\t ID portátil: %d\t", requests[pos].code, requests[pos].laptop_id);
			fprintf(log_file, "Nome utilizador: %s\t", requests[pos].user_name);
			// Print type of user
			switch (requests[pos].user_type) {
			case STUDENT:
				fprintf(log_file, "Tipo utilizador: Estudante\t\t");
				break;
			case TEACHER:
				fprintf(log_file, "Tipo utilizador: Professor\t\t");
				break;
			case ADMNISTRATIVE:
				fprintf(log_file, "Tipo utilizador: Técnico Administrativo\t");
			}

			fprintf(log_file, "Prazo: %d\t", requests[pos].deadline);
			fprintf(log_file, "Estado: Concluído\t");
			fprintf(log_file, "Data requisição: %02d/%02d/%04d\t", requests[pos].requisition_date.day, requests[pos].requisition_date.month, requests[pos].requisition_date.year);
			switch (requests[pos].devolution_local) {
			case RESIDENCES:
				fprintf(log_file, "Local de devolução: Residências\t");
				break;
			case CAMPUS1:
				fprintf(log_file, "Local de devolução: Campus 1\t");
				break;
			case CAMPUS2:
				fprintf(log_file, "Local de devolução: Campus 2\t");
				break;
			case CAMPUS5:
				fprintf(log_file, "Local de devolução: Campus 5\t");
				break;
			}
			fprintf(log_file, "Multa: %.2f\t", requests[pos].price);
			// Print laptop data
			laptop_pos = search_laptop_id(laptops, numberLaptops, requests[pos].laptop_id);
			fprintf(log_file, "Processador: i%d\t", laptops[laptop_pos].cpu);
			fprintf(log_file, "Memória RAM: %dGB\r\n", laptops[laptop_pos].memory);

			fclose(log_file);
		}

	}
}

// Show main menu options
int menu(void) {
	int opcao;
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

// Laptops menu
void menu_laptops(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests) {
	int opcao2;
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
			list_laptops(*laptops, *numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
			printf("\n");
			break;
		case 3:
			update_laptop_location(laptops, *numberLaptops);
			break;
	}
}

// Requests menu
void menu_requests() {
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
			printf("\nteste\n\n");
			// *op = lerInteiro("Deseja continuar no programa? Não/Sim", 0, 1);  // Asks if the user wants to coninue the program               
			break;
		}
}

// Breakdowns menu
void menu_breakdowns(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
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
			register_breakdown(breakdowns, numberBreakdowns, laptops, numberLaptops);
			break;
		case 2:
			register_repair(*breakdowns, *numberBreakdowns, laptops, numberLaptops);
			break;
		case 3:
			list_breakdowns(*breakdowns, *numberBreakdowns, laptops, numberLaptops);
			break;
	}
}

// Statistics menu
void menu_statistics() {

}


/**
 * @brief Register a breakdown
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param laptops 
 * @param numberLaptops 
 */
void register_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	int pos, control, id;
	// Check if exist laptops and breakdowns
	if (breakdowns != NULL && laptops != NULL && numberLaptops > 0) {
		// Read id
		do {
			id = lerInteiro("Insira o ID do portátil avariado", 1, MAX_LAPTOPS);
			pos = search_laptop_id(laptops, numberLaptops, id);
			if (pos == -1) {
				printf("ATENÇÃO: Insira o ID de um laptop existente\n");
			}
		} while (pos == -1);

		control = insert_breakdown(breakdowns, numberBreakdowns, id);
		if (control == 0) {
			laptops[pos].state = BROKEN;
		}

		printf("Registo de avaria concluído com sucesso\n");
	} else {
		printf("ATENÇÃO: Não existe nenhum avaria registada!\n");
	}
}

/**
 * @brief Register a repair
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param laptops 
 * @param numberLaptops 
 */
void register_repair(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	int pos, control, id;
	// Check if exist breakdowns and laptops
	if (breakdowns != NULL && numberBreakdowns > 0 && laptops != NULL && numberLaptops > 0) {
		// Get breakdown id
		do {
			id = lerInteiro("Insira o ID da avaria", 1, INT_MAX);
			pos = search_breakdown_id(breakdowns, numberBreakdowns, id);
			if (pos == -1) {
				printf("ATENÇÃO: Tem de inserir um ID existente\n");
			}
			if (breakdowns[pos].duration != -1) {
				printf("ATENÇÃO: Insira o ID de uma avaria ainda não reparada\n");
			}
		} while (pos == -1 || breakdowns[pos].duration != -1);
		
		// Set laptop available for requisition and set duration of reparation
		breakdowns[pos].duration = lerInteiro("Insira a duração da reparação", 0, 90);
		control = search_laptop_id(laptops, numberLaptops, breakdowns[pos].laptop_id);
		laptops[control].state = AVAILABLE;

		printf("Registo de reparação concluído com sucesso\n");
	} else {
		printf("ATENÇÃO: Não existe nenhuma avaria registada!\n");
	}
}

/**
 * @brief Register a laptop devolution
 * 
 * @param requests 
 * @param numberRequests 
 */
void register_devolution(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops) {
	char code[CODE_SIZE];
	int pos, control, tmp, holded_days;
	typeDate devolution_date;

	// Check if exist breakdowns
	if (requests != NULL && numberRequests > 0) {
		do {	// Get request code
			lerString("Insira o código da requisição", code, CODE_SIZE-1);
			pos = search_request_by_code(requests, numberRequests, code);
			if (pos == -1) {
				printf("ATENÇÃO: Tem de inserir o código de uma requisição existente\n");
			}
			if (requests[pos].requisition_state == DONE) {
				printf("ATENÇÃO: Insira o código de uma requisição ainda não concluída\n");
			}
		} while (pos == -1 || requests[pos].requisition_state == DONE);

		do {	// Read devolution date
			read_date("Insira a data de devolução do portátil", &devolution_date);
			control = compare_date(requests[pos].requisition_date, devolution_date);
			if (control == -1) {	// if devolution_date is smaller than requisition_date
				printf("ATENÇÃO: Insira uma date igual ou superior à data de requisição\n");
			}
		} while (control == -1);	// while devolution_date is smaller than requisition_date

		do {	// Read location of devolution
			tmp = lerInteiro("Insira a localização do portátil\n\t0 - Residências\n\t1 - Campus 1\n\t2 - Campus 2\n\t5 - Campus 5\n", 0, 5);
			control = set_typeLocal(&(requests[pos].devolution_local), tmp);
		
			if (control != 0) {	// If not valid
				printf("\nATENÇÃO: Insira uma localização válida\n");
			}
		} while (control != 0);

		// Calculate 
		holded_days = diff_date(requests[pos].requisition_date, devolution_date);
		tmp = holded_days - requests[pos].deadline;
		requests[pos].price = tmp * 10;

		// Set laptop available
		control = search_laptop_id(laptops, numberLaptops, requests[pos].laptop_id);
		laptops[control].state = AVAILABLE;

		printf("Registo de devolução concluído com sucesso\n");
	} else {
		printf("ATENÇÃO: Não existe nenhuma requisição registada!\n");
	}
}

/**
 * @brief Renovate a request
 * 
 * @param requests 
 * @param numberRequests 
 */
void renovate_request(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops) {
	char code[CODE_SIZE];
	int pos;
	// Check if exist requests
	if (requests != NULL && numberRequests > 0) {
		do {	// Get request code
			lerString("Insira o código da requisição", code, CODE_SIZE-1);
			pos = search_request_by_code(requests, numberRequests, code);
			if (pos == -1) {
				printf("ATENÇÃO: Tem de inserir o código de uma requisição existente\n");
			}
			if (requests[pos].requisition_state == DONE) {
				printf("ATENÇÃO: Insira o código de uma requisição ainda não concluída\n");
			}
		} while (pos == -1 || requests[pos].requisition_state == DONE);

		// Add 7 days to deadline
		requests[pos].deadline += 7;

		save_request_to_log(requests, numberRequests, laptops, numberLaptops, pos);
	} else {
		printf("ATENÇÃO: Não existe nenhuma requisição registada!\n");
	}
}

/**
 * @brief Show breakdowns data
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param laptops 
 * @param numberLaptops 
 */
void list_breakdowns(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	unsigned int pos;
	// Check if exist laptops and breakdowns
	if (breakdowns != NULL && numberBreakdowns > 0) {	// If exist breakdowns then have to exist at least a laptop
		// printf("ID\tCPU\tMem.\tEstado\tLocal\tPreço\tID\tTipo\tDuração\tData\t\tDescrição\n");
		printf("ID\tTipo avaria\tData avaria\tDuraç.\tLID\tCPU\tMemor.\tEstado\t\tLocalização\tPreço\tDescrição\n");

		for (pos = 0; pos < numberBreakdowns; pos++) {	// Get breakdow by breakdown
			// Get position of laptop in vector of laptops
			pos = search_laptop_id(laptops, numberLaptops, breakdowns[pos].laptop_id);
			// Print breakdown data
			printf("%d\t", breakdowns[pos].id);
			print_typeBreak(breakdowns[pos].break_type);
			printf("\t");
			print_date(breakdowns[pos].date);
			printf("\t%d\t", breakdowns[pos].duration);
			// Print laptop data
			printf("%d\t", laptops[pos].id);
			print_typeCPU(laptops[pos].cpu);
			printf("\t%dGB\t", laptops[pos].memory);
			print_typeState(laptops[pos].state);
			printf("\t");
			print_typeLocal(laptops[pos].location);
			printf("\t%.2f\t%s\n", laptops[pos].price, laptops[pos].description);
		}
	} else {
		printf("ATENÇÃO: Não existe nenhuma avaria registada!\n");
	}
}

/**
 * @brief Show laptops data
 * 
 * @param laptops 
 * @param numberLaptops 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param requests 
 * @param numberRequests 
 */
void list_laptops(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests) {
	int counted;
	unsigned int pos;
	// Check if exist laptops
	if (laptops != NULL && numberLaptops > 0) {
		printf("ID\tCPU\tMemor.\tEstado\t\tLocalização\tPreço\tN.Avar\tN.Requi\tDescrição\n");

		for (pos = 0; pos < numberLaptops; pos++) {	// Get laptop by laptop
			// Print laptop data
			printf("%d\t", laptops[pos].id);
			print_typeCPU(laptops[pos].cpu);
			printf("\t%dGB\t", laptops[pos].memory);
			print_typeState(laptops[pos].state);
			printf("\t");
			print_typeLocal(laptops[pos].location);
			printf("\t%.2f\t", laptops[pos].price);
			
			counted = count_breakdowns_by_laptop_id(breakdowns, numberBreakdowns, laptops[pos].id);
			printf("%d\t", counted);
			counted = count_requests_by_laptop_id(requests, numberRequests, laptops[pos].id);
			printf("%d\t", counted);
			printf("%s\n", laptops[pos].description);

			// TODO: Print type of user
			// TODO: Print deadline for each request
			list_requests_by_laptop_id(requests, numberRequests, laptops[pos].id, "\t");
		}
	} else {
		printf("ATENÇÃO: Não existe nenhum portátil registado!\n");
	}
}
