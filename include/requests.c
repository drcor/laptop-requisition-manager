#include "requests.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Set type of user from a integer
 *
 * @param user_type
 * @param num
 * @return -1 if 'num' doesn't exist in typeUser
 * @return 0 if not
 */
int set_typeUser(enum typeUser *user_type, int num) {
	int result = 0;
	switch (num) {
	case STUDENT:
		*user_type = STUDENT;
		break;
	case TEACHER:
		*user_type = TEACHER;
		break;
	case ADMNISTRATIVE:
		*user_type = ADMNISTRATIVE;
		break;
	default:
		result = -1;
		break;
	}

	return result;
}

/**
 * @brief Print type of user
 * 
 * @param user_type 
 */
void print_typeUser(enum typeUser user_type) {
	switch (user_type) {
	case STUDENT:
		printf("Aluno         ");
		break;
	case TEACHER:
		printf("Docente       ");
		break;
	case ADMNISTRATIVE:
		printf("Administrativo");
		break;
	}
}

/**
 * @brief Set type of requisition state from a number
 *
 * @param req_state
 * @param num
 * @return -1 if 'num' doesn't exist in typeReqState
 * @return 0 if not
 */
int set_typeReqState(enum typeReqState *req_state, int num) {
	int result = 0;
	switch (num) {
	case ACTIVE:
		*req_state = ACTIVE;
		break;
	case DONE:
		*req_state = DONE;
		break;
	default:
		result = -1;
		break;
	}

	return result;
}

/**
 * @brief Print type of requistion state
 * 
 * @param req_state 
 */
void print_typeReqState(enum typeReqState req_state) {
	switch (req_state) {
	case ACTIVE:
		printf("Ativo    ");
		break;
	case DONE:
		printf("Concluùdo");
		break;
	}
}

/**
 * @brief Count number of requests with a laptop_id
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptopId 
 * @return int number of requests
 */
int count_requests_from_laptop_id(typeRequest *requests, unsigned int numberRequests, int laptopId) {
	int count = 0;

	if (numberRequests > 0) {
		for (unsigned int i = 0; i < numberRequests; i++) {
			if (requests[i].laptop_id == laptopId) {
				count++;
			}
		}
	}

	return count;
}

/**
 * @brief Insert a request in the vector
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptopId 
 * @return int 
 */
void insert_request(typeRequest **requests, unsigned int *numberRequests, int laptopId) {
	typeRequest request;
	int aux = 0, result = -1;
	char code[CODE_SIZE];

	// Backup in case something goes wrong
	typeRequest *save = *requests;

	*requests = realloc(*requests, (*numberRequests + 1) * sizeof(typeRequest));
	if(*requests != NULL){
		// Inserts product code, already validated.
		do{
			lerString("Insira o cùdigo do produto", code, 10);
			aux = search_request_by_code(*requests, *numberRequests, code);
			if (aux == -1) {
				strcpy(request.code, code);
			} else {
				printf("O cùdigo introduzido jù existe!\n");
			}
		} while (aux != -1);

		// Insert laptop's id
		

		// Inserts client name
		lerString("Insira o nome do cliente", request.user_name, 60);

		// Inserts user type
		aux = lerInteiro("Insira o tipo de cliente\n\t0 - Estudante\n\t1 - Professor\n\t2 - Admininstraùùo\n", 0, 2);
		set_typeUser(&(request.user_type), aux);

		// User chooses deadline
		request.deadline = lerInteiro("Insira o prazo de devoluùùo do portùtil em dias: ", 1, 30);

		// Set the requisition state
		set_typeReqState(&(request.requisition_state), 0);

		// Inserts request date
		read_date("Insira a data da requisiùùo", &(request.requisition_date));

		// Inserts delivery date
		// DATE IS AUTOMATICALLY SET BY THE DEADLINE, no need for this
		//read_date("Insira a data de entrega", &(request.devolution_date));

		// Store laptop ID
		request.laptop_id = laptopId;

		(*requests)[*numberRequests] = request;
		result = 0;
	} else{
		*requests = save;
		printf("Falha na alocaùùo de memùria!\n");
	}
}

void list_request(typeRequest *requests, unsigned int numberRequests){
	printf("\nRequisiùùes:\n");
	// Check if there are requests
	if (requests != NULL && numberRequests > 0) {
		printf("ID\tCode\tNome\tUtilizador\tData\t\tDevoluùùo\tLocal\tMulta\n");
		for (int i = 0; i < numberRequests; i++) {
			printf("%d\t%c\t%c\t", requests[i].laptop_id, requests[i].code, requests[i].user_name);
			printf("%d\t", requests[i].user_type);
			print_date(requests[i].requisition_date);
			printf("%d dias\t%d\t%d euros", requests[i].deadline, requests[i].devolution_local, requests[i].price);
		}
	} else {
		printf("ATENùùO: Nùo existe nenhuma requisiùùo registada!\n");
	}
}

/**
 * @brief Read a N number of requests from a file
 * The N number is given in the first 4 bytes of the file
 *
 * @param requests
 * @param amount
 * @param file 
 * @return -1 if failed to read requests
 * @return int if success
 */
int read_request_from_file(typeRequest **requests, unsigned int *amount, FILE *file) {
	int result = -1;

	// Check if 'file' is valid
	if (file != NULL) {
		fseek(file, 0, SEEK_SET);
		// Get the amount of requests in the file
		fread(amount, sizeof(unsigned int), 1, file);

		if (*amount > 0) {
			*requests = malloc(*amount * sizeof(typeRequest));	// Allocate memory

			if (*requests != NULL) {	// success to allocate memory
				// Read all requests from the file to the vector 'requests'
				result = fread(*requests, sizeof(typeRequest), *amount, file);
				
				if ((unsigned int)result != *amount) {
					*amount = 0;
				}
			}
		} else {
			result = 0;
		}
	}

	return result;
}

/**
 * @brief Write a vector os requests to a file
 *
 * @param requests
 * @param amount
 * @param file
 * @return -1 if failed to write requests
 * @return 0 if success
 */
int write_request_to_file(typeRequest *requests, unsigned int amount, FILE *file) {
	int result = 1;

	// Check if 'file' is valid and there is any request to write
	if (file != NULL) {
		// Write amount and the requests
		fwrite(&amount, sizeof(unsigned int), 1, file);
		result = fwrite(requests, sizeof(typeRequest), amount, file);
	}

	return result;
}

int search_request_by_code(typeRequest *requests, unsigned int numberRequests, char code[CODE_SIZE]) {
	int result = -1;

	for (unsigned int i = 0; i < numberRequests; i++) {
		if (strcmp(requests[i].code, code) == 0) {
			result = i;
			i = numberRequests;
		}
	}

	return result;
}