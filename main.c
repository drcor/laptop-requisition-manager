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
int menu(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void menu_laptops(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);
void menu_requests(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void menu_breakdowns(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void menu_statistics(typeLaptop *laptops, unsigned int numberLaptops, typeRequest *requests, unsigned int numberRequests);
/* Declaration of menus functionalities */
void register_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void register_repair(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void register_devolution(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void register_request(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void renovate_request(typeRequest *requests, unsigned int numberRequests);
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
		opcao = menu(requests, numberRequests, laptops, numberLaptops);
		switch (opcao) {
			case 0:
				break;
			case 1:
				menu_laptops(&laptops, &numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
				break;
			case 2:
				menu_requests(&requests, &numberRequests, laptops, numberLaptops);
				break;
			case 3:
				menu_breakdowns(&breakdowns, &numberBreakdowns, laptops, numberLaptops);
				break;
			case 4:
				menu_statistics(laptops, numberLaptops, requests, numberRequests);
				break;
			default:
				printf("\nATEN��O: Insira uma op��o v�lida\n");
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
			fprintf(log_file, "C�digo:%s\t IDport�til:%d\t", requests[pos].code, requests[pos].laptop_id);
			// Print type of user
			fprintf(log_file, "TipoCliente:");
			switch (requests[pos].user_type) {
			case STUDENT:
				fprintf(log_file, "Estudante\t\t");
				break;
			case TEACHER:
				fprintf(log_file, "Docente\t\t");
				break;
			case ADMNISTRATIVE:
				fprintf(log_file, "T�cnico Administrativo\t");
			}

			fprintf(log_file, "Prazo:%d\t", requests[pos].deadline);
			fprintf(log_file, "Estado:Conclu�do\t");
			fprintf(log_file, "DataRequisi��o:%02d/%02d/%04d\t", requests[pos].requisition_date.day, requests[pos].requisition_date.month, requests[pos].requisition_date.year);
			
			fprintf(log_file, "Local de devolu��o:");
			switch (requests[pos].devolution_local) {
			case NONE:
				fprintf(log_file, "----\t");
				break;
			case RESIDENCES:
				fprintf(log_file, "Resid�ncias\t");
				break;
			case CAMPUS1:
				fprintf(log_file, "Campus 1\t");
				break;
			case CAMPUS2:
				fprintf(log_file, "Campus 2\t");
				break;
			case CAMPUS5:
				fprintf(log_file, "Campus 5\t");
				break;
			}
			fprintf(log_file, "Multa:%.2f\t", requests[pos].price);
			// Print laptop data
			laptop_pos = search_laptop_id(laptops, numberLaptops, requests[pos].laptop_id);
			fprintf(log_file, "Processador:i%d\t", laptops[laptop_pos].cpu);
			fprintf(log_file, "Mem�riaRAM:%dGB\t", laptops[laptop_pos].memory);
			fprintf(log_file, "NomeUtilizador:%s\t\n", requests[pos].user_name);

			fclose(log_file);
		}

	}
}

// Show main menu options
int menu(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops) {
	int opcao, active_requests, available_laptops;

	available_laptops = count_laptops_availale(laptops, numberLaptops);
	active_requests = count_requests_active(requests, numberRequests);

	printf("\n +----------------------------------------------------+\n");
	printf(" |                        MENU                        |\n");
	printf(" +----------------------------------------------------+\n");
	// - [ ]  quantidade de port�teis existentes
	// - [ ]  quantidade de port�teis dispon�veis
	printf(" | N� port�teis:   %3d  N� port�teis disponiveis: %3d |\n", numberLaptops, available_laptops);
	// - [ ]  quantidade total de requisi��es efetuadas
	// - [ ]  quantidade de requisi��es ativas
	printf(" | N� requisi��es: %3d  N� requisi��es ativas:    %3d |\n", numberRequests, active_requests);
	printf(" +----------------------------------------------------+\n");
	printf(" |  [1] Port�teis                                     |\n");
	printf(" |  [2] Requisi��es                                   |\n");
	printf(" |  [3] Avarias                                       |\n");
	printf(" |  [4] Dados Estat�sticos                            |\n");
	printf(" |  [0] Sair                                          |\n");
	printf(" +----------------------------------------------------+\n");
	opcao = lerInteiro("Op��o: ", 0, 4);

	return opcao; 
}

// Laptops menu
void menu_laptops(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests) {
	int opcao2;
	printf("\n +------------------------------------------+\n");
	printf(" |                Port�teis                 |\n");
	printf(" +------------------------------------------+\n");
	printf(" |  [1] Inserir Port�teis                   |\n");
	printf(" |  [2] Listar Port�teis                    |\n");
	printf(" |  [3] Alterar localiza��o do Port�til     |\n");
	printf(" |  [0] Anterior                            |\n");
	printf(" +------------------------------------------+\n");
	opcao2 = lerInteiro("Op��o", 0, 3);

	switch(opcao2) {
		case 1:
			printf("\nRegistar Port�til:\n");
			insert_laptop(laptops, numberLaptops);
			break;
		case 2:
			printf("\nLista de Port�teis:\n");
			list_laptops(*laptops, *numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
			printf("\n");
			break;
		case 3:
			printf("\nAtualizar localiza��o:\n");
			update_laptop_location(laptops, *numberLaptops);
			break;
	}
}

// Requests menu
void menu_requests(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops) {
	int opcao2;

	printf("\n +------------------------------------------+\n");
	printf(" |               Requisi��es                |\n");
	printf(" +------------------------------------------+\n");
	printf(" |  [1] Requisitar port�til                 |\n");
	printf(" |  [2] Listar Requisi��es                  |\n");
	printf(" |  [3] Mostrar uma Requisi��o              |\n");
	printf(" |  [4] Renovar Requisi��o                  |\n");
	printf(" |  [5] Devolu��o de port�til Requisitado   |\n");
	printf(" |  [0] Anterior                            |\n");
	printf(" +------------------------------------------+\n");
	opcao2 = lerInteiro("Op��o", 0, 5);

	switch (opcao2) {
		case 1:
			printf("\nRegistar Requisi��o:\n");
			register_request(requests, numberRequests, laptops, numberLaptops);
			break;
		case 2:
			printf("\nLista de requisi��es:\n");
			list_request(*requests, *numberRequests);
			break;
		case 3:
			printf("\nVer informa��es de uma requisi��o:\n");
			list_one_request(*requests, numberRequests);
			break;
		case 4:
			printf("\nRenovar Requisi��o:\n");
			renovate_request(*requests, *numberRequests);
			break;
		case 5:
			printf("\nRegistar Devolu��o:\n");
			register_devolution(*requests, *numberRequests, laptops, numberLaptops);
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
	printf(" |  [2] Registar Repara��o                  |\n");
	printf(" |  [3] Listar Avarias                      |\n");
	printf(" |  [0] Anterior                            |\n");
	printf(" +------------------------------------------+\n");
	opcao2 = lerInteiro("Op��o", 0, 3);

	switch (opcao2) {
		case 1:
			printf("\nRegistar Avaria:\n");
			register_breakdown(breakdowns, numberBreakdowns, laptops, numberLaptops);
			break;
		case 2:
			printf("\nRegistar Repara��o:\n");
			register_repair(*breakdowns, *numberBreakdowns, laptops, numberLaptops);
			break;
		case 3:
			printf("\nLista de Avarias:\n");
			list_breakdowns(*breakdowns, *numberBreakdowns, laptops, numberLaptops);
			break;
	}
}

// Statistics menu
void menu_statistics(typeLaptop *laptops, unsigned int numberLaptops, typeRequest *requests, unsigned int numberRequests) {
	float medCoast=0, perI3=0, perI5=0, perI7=0;
	unsigned int pos, counter=0, numStudents=0, numTeachers=0, numAdministratives=0, min;
	typeDate maxDate = {0,0,0};

	printf("\nDados estat�sticos:\n");
	// - [ ]  percentagem de port�teis com cada tipo de processador
	for (pos = 0; pos < numberLaptops; pos++) {
		switch (laptops[pos].cpu) {
		case I3:
			perI3++;
			break;
		case I5:
			perI5++;
			break;
		case I7:
			perI7++;
			break;
		}
	}

	perI3 = perI3 * 100 / numberLaptops;
	perI5 = perI5 * 100 / numberLaptops;
	perI7 = perI7 * 100 / numberLaptops;
	printf(" Percentagem de CPUs em port�teis:\n\tI3=%.1f%%\tI5=%.1f%%\tI7=%.1f%%\n", perI3, perI5, perI7);
	
	// Calculate medium coast of payed fines
	for (pos = 0; pos < numberRequests; pos++) {
		if (requests[pos].price > 0.0) {	// sum only if bigger than 0
			medCoast += requests[pos].price;
			counter++;
		}
	}
	medCoast = (float)medCoast / counter;
	printf("\n Custo m�dio de multas pagas: %.2f �\n", medCoast);

	// Type of users with smaller number of requests
	for (pos = 0; pos < numberRequests; pos++) {
		switch (requests[pos].user_type) {
		case STUDENT:
			numStudents++;
			break;
		case TEACHER:
			numTeachers++;
			break;
		case ADMNISTRATIVE:
			numAdministratives++;
			break;
		}
		// Calculate most recent date
		if (compare_date(maxDate, requests[pos].devolution_date) == 1) {	// if devolution_date is more recent than maxDate
			maxDate = requests[pos].devolution_date;
		}
	}
	min = numStudents;
	if (min > numTeachers) {
		min = numTeachers;
	} else {
		if (min > numAdministratives) {
			min = numAdministratives;
		}
	}

	printf("\n Tipo(s) de utente(s) com a menor quantidade de requisi��es efetuadas:\n");
	if (min == numStudents) {
		printf("  - Alunos\n");
	}
	if (min == numTeachers) {
		printf("  - Docentes\n");
	}
	if (min == numAdministratives) {
		printf("  - T�cnicos Administrativos\n");
	}
	
	// Print most recent dates equal to maxDate
	printf("\n As devolu��es mais recentes t�m o c�digo:\n");
	for (pos = 0; pos < numberRequests; pos++) {
		if (compare_date(maxDate, requests[pos].devolution_date) == 0) {
			printf("  - %s\n", requests[pos].code);
		}
	}
	
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
	typeDate date;
	// Check if exist laptops and breakdowns
	if (breakdowns != NULL && laptops != NULL && numberLaptops > 0) {
		// Read id
		do {
			id = lerInteiro("Insira o ID do port�til avariado", 1, MAX_LAPTOPS);
			pos = search_laptop_id(laptops, numberLaptops, id);
			if (pos == -1 || laptops[pos].state != AVAILABLE) {	// if laptop ID dont exist or is not available
				printf("ATEN��O: Insira o ID de um laptop existente e dispon�vel\n");
			}
		} while (pos == -1 || laptops[pos].state != AVAILABLE);	// while laptop ID dont exist or is not available

		// Get request date
		do {
			read_date("Insira a data de avaria", &(date));

			control = compare_date(laptops[pos].date, date);

			if (control == -1) {	// if date is smaller than laptop date
				printf("\nATEN��O: A data tem de ser igual ou superior � data de aquisi��o do port�til\n");
			}
		} while (control == -1);	// while date is smaller than laptop date

		control = insert_breakdown(breakdowns, numberBreakdowns, id, date);
		if (control == 0) {
			laptops[pos].state = BROKEN;
		}

		printf("Registo de avaria conclu�do com sucesso\n");
	} else {
		printf("ATEN��O: N�o existe nenhum avaria registada!\n");
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
				printf("\nATEN��O: Tem de inserir um ID existente\n");
			}
			if (breakdowns[pos].duration != -1) {
				printf("ATEN��O: Insira o ID de uma avaria ainda n�o reparada\n");
			}
		} while (pos == -1 || breakdowns[pos].duration != -1);
		
		// Set laptop available for requisition and set duration of reparation
		breakdowns[pos].duration = lerInteiro("Insira a dura��o da repara��o", 0, 90);
		control = search_laptop_id(laptops, numberLaptops, breakdowns[pos].laptop_id);
		laptops[control].state = AVAILABLE;

		printf("Registo de repara��o conclu�do com sucesso\n");
	} else {
		printf("ATEN��O: N�o existe nenhuma avaria registada!\n");
	}
}

void register_request(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops) {
	int control, laptop_id, pos;
	typeDate requisition_date;
	// Check if exists requests and laptops
	if (requests != NULL && laptops != NULL && numberLaptops > 0) {
		do {
			laptop_id = lerInteiro("Insira o id do laptop que deseja requisitar:", 1, MAX_LAPTOPS);
			pos = search_laptop_id(laptops, numberLaptops, laptop_id);
			
			if (pos == -1 || laptops[pos].state != AVAILABLE) {
				printf("\nATEN��O: Insira o ID de um laptop existente e dispon�vel\n");
			}
		} while (pos == -1 || laptops[pos].state != AVAILABLE);

		// Get request date
		do {
			read_date("Insira a data de requisi��o", &(requisition_date));

			control = compare_date(laptops[pos].date, requisition_date);

			if (control == -1) {	// if date is smaller than laptop date
				printf("\nATEN��O: A data tem de ser igual ou superior � data de aquisi��o do port�til\n");
			}
		} while (control == -1);	// while date is smaller than laptop date

		control = insert_request(requests, numberRequests, laptop_id, requisition_date);
		if (control == 0) {
			// Set laptop state to taken
			laptops[pos].state = TAKEN;
		}

		printf("Registo de requisi��o conclu�do com sucesso\n");
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
			lerString("Insira o c�digo da requisi��o", code, CODE_SIZE-1);
			pos = search_request_by_code(requests, numberRequests, code);
			if (pos == -1) {
				printf("ATEN��O: Tem de inserir o c�digo de uma requisi��o existente\n");
			}
			if (requests[pos].requisition_state == DONE) {
				printf("ATEN��O: Insira o c�digo de uma requisi��o ainda n�o conclu�da\n");
			}
		} while (pos == -1 || requests[pos].requisition_state == DONE);

		do {	// Read devolution date
			read_date("Insira a data de devolu��o do port�til", &devolution_date);
			control = compare_date(requests[pos].requisition_date, devolution_date);
			if (control == -1) {	// if devolution_date is smaller than requisition_date
				printf("ATEN��O: Insira uma data igual ou superior � data de requisi��o\n");
			}
		} while (control == -1);	// while devolution_date is smaller than requisition_date
		requests[pos].devolution_date = devolution_date;

		do {	// Read location of devolution
			tmp = lerInteiro("Insira a localiza��o do port�til\n\t0 - Resid�ncias\n\t1 - Campus 1\n\t2 - Campus 2\n\t5 - Campus 5\n", 0, 5);
			control = set_typeLocal(&(requests[pos].devolution_local), tmp);
		
			if (control != 0) {	// If not valid
				printf("\nATEN��O: Insira uma localiza��o v�lida\n");
			}
		} while (control != 0);

		// Calculate fine
		holded_days = diff_date(requests[pos].requisition_date, devolution_date);
		tmp = holded_days - requests[pos].deadline;
		if (tmp >= 0) {
			requests[pos].price = tmp * 10;
			printf("\nMULTA: %.2f �\n", requests[pos].price);
		}

		// Set request as done
		requests[pos].requisition_state = DONE;

		// Set laptop available
		control = search_laptop_id(laptops, numberLaptops, requests[pos].laptop_id);
		laptops[control].state = AVAILABLE;

		save_request_to_log(requests, numberRequests, laptops, numberLaptops, pos);

		printf("Registo de devolu��o conclu�do com sucesso\n");
	} else {
		printf("ATEN��O: N�o existe nenhuma requisi��o registada!\n");
	}
}

/**
 * @brief Renovate a request
 * 
 * @param requests 
 * @param numberRequests 
 */
void renovate_request(typeRequest *requests, unsigned int numberRequests) {
	char code[CODE_SIZE];
	int pos;
	// Check if exist requests
	if (requests != NULL && numberRequests > 0) {
		do {	// Get request code
			lerString("Insira o c�digo da requisi��o", code, CODE_SIZE-1);
			pos = search_request_by_code(requests, numberRequests, code);
			if (pos == -1) {
				printf("ATEN��O: Tem de inserir o c�digo de uma requisi��o existente\n");
			}
			if (requests[pos].requisition_state == DONE) {
				printf("ATEN��O: Insira o c�digo de uma requisi��o ainda n�o conclu�da\n");
			}
		} while (pos == -1 || requests[pos].requisition_state == DONE);

		// Add 7 days to deadline
		requests[pos].deadline += 7;
	} else {
		printf("ATEN��O: N�o existe nenhuma requisi��o registada!\n");
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
		printf("ID\tTipo avaria\tData avaria\tDura�.\tLID\tCPU\tMemor.\tEstado\t\tLocaliza��o\tPre�o\t\tDescri��o\n");

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
			printf("\t   %.2f �\t%s\n", laptops[pos].price, laptops[pos].description);
		}
	} else {
		printf("\nATEN��O: N�o existe nenhuma avaria registada!\n");
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
		printf("ID\tCPU\tMemor.\tEstado\t\tLocaliza��o\tPre�o\t\tN.Avar\tN.Requi\tDescri��o\n");

		for (pos = 0; pos < numberLaptops; pos++) {	// Get laptop by laptop
			// Print laptop data
			printf("%d\t", laptops[pos].id);
			print_typeCPU(laptops[pos].cpu);
			printf("\t%dGB\t", laptops[pos].memory);
			print_typeState(laptops[pos].state);
			printf("\t");
			print_typeLocal(laptops[pos].location);
			printf("\t   %.2f �\t", laptops[pos].price);
			
			counted = count_breakdowns_by_laptop_id(breakdowns, numberBreakdowns, laptops[pos].id);
			printf("%d\t", counted);
			counted = count_requests_by_laptop_id(requests, numberRequests, laptops[pos].id);
			printf("%d\t", counted);
			printf("%s\n", laptops[pos].description);

			// TODO: Print type of user
			// TODO: Print deadline for each request
			if (counted > 0) {
				printf("     +----\n");
				list_requests_by_laptop_id(requests, numberRequests, laptops[pos].id, "     | ");
				printf("\n");
			}
		}
	} else {
		printf("\nATEN��O: N�o existe nenhum port�til registado!\n");
	}
}
