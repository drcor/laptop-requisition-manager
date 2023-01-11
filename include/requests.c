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
		printf("Concluído");
		break;
	}
}

/**
 * @brief Count active requests
 * 
 * @param requests 
 * @param numberRequests 
 * @return int 
 */
int count_requests_active(typeRequest *requests, unsigned int numberRequests) {
	int count = 0;
	unsigned int pos;

	if (requests != NULL && numberRequests > 0) {
		for (pos = 0; pos < numberRequests; pos++) {
			if (requests[pos].requisition_state == ACTIVE) {
				count++;
			}
		}
		
	}

	return count;
}

/**
 * @brief Count number of requests with a laptop_id
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptopId 
 * @return int number of requests
 */
int count_requests_by_laptop_id(typeRequest *requests, unsigned int numberRequests, int laptopId) {
	int count = 0;
	unsigned int pos;

	if (numberRequests > 0) {
		for (pos = 0; pos < numberRequests; pos++) {
			if (requests[pos].laptop_id == laptopId) {
				count++;
			}
		}
	}

	return count;
}

/**
 * @brief Search request by code
 * 
 * @param requests 
 * @param numberRequests 
 * @param code 
 * @return -1 if not found
 * @return int position of id
 */
int search_request_by_code(typeRequest *requests, unsigned int numberRequests, char code[CODE_SIZE]){
	int result = -1;
	unsigned int pos;

	for (pos = 0; pos < numberRequests; pos++) {
		if (strcmp(requests[pos].code, code) == 0) {
			result = pos;
			pos = numberRequests;
		}
	}

	return result;
}

/**
 * @brief Insert a request in the vector
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptopId 
 * @return -1 failure to insert request
 * @return 0 success to insert request
 */
int insert_request(typeRequest **requests, unsigned int *numberRequests, int laptopId, typeDate requisitionDate) {
	typeRequest request;
	int tmp, control, result = -1;
	typeDate devolutionDate = {0,0,0};

	// Backup in case something goes wrong
	typeRequest *save = *requests;

	*requests = realloc(*requests, (*numberRequests + 1) * sizeof(typeRequest));
	if (*requests != NULL) {
		// Inserts product code, already validated.
		do {
			lerString("Insira o código do produto", request.code, CODE_SIZE);
			control = search_request_by_code(*requests, *numberRequests, request.code);
			
			if (control > -1) {
				printf("\nATENÇÃO: O código introduzido já está registado\n");
			}
		} while (control > -1);
		
		// Set client name
		lerString("Insira o nome do cliente", request.user_name, USERNAME_SIZE);

		// Set type of user
		tmp = lerInteiro("Insira o tipo de cliente\n\t0 - Estudante\n\t1 - Docente\n\t2 - Técnico Administrativo\n", 0, 2);
		set_typeUser(&(request.user_type), tmp);

		// User chooses deadline
		request.deadline = lerInteiro("Insira o prazo de devolução do portátil em dias: ", 1, DEADLINE_LIMIT);

		// Set the requisition state to active and store laptop ID
		request.requisition_date = requisitionDate;
		request.requisition_state = ACTIVE;
		request.laptop_id = laptopId;
		request.price = 0.0;
		request.devolution_local = NONE;
		request.devolution_date = devolutionDate;

		(*requests)[*numberRequests] = request;
		(*numberRequests)++;
		result = 0;
	} else {
		*requests = save;
		printf("ERRO: Falha na alocação de memória!\n");
	}

	return result;
}

void list_request(typeRequest *requests, unsigned int numberRequests) {
	unsigned int pos;
	int days;

	// Check if there are requests
	if (requests != NULL && numberRequests > 0) {
		printf("Code\tLID\tEstado\t\tPrazo\tLocal devol.\tData requi.\tData devol.\tDias req.\tMulta\t\tTipo User\tUtilizador\n");

		for (pos = 0; pos < numberRequests; pos++) {
			printf("%s\t%d\t", requests[pos].code, requests[pos].laptop_id);
			print_typeReqState(requests[pos].requisition_state);
			printf("\t%d\t", requests[pos].deadline);
			print_typeLocal(requests[pos].devolution_local);
			printf("\t");
			print_date(requests[pos].requisition_date);
			printf("\t");
			// Print duration of requisition
			if (requests[pos].requisition_state == DONE) {
				print_date(requests[pos].devolution_date);
				days = diff_date(requests[pos].requisition_date, requests[pos].devolution_date);
				printf("\t%d\t", days);
			} else {
				printf(" ---\t\t ---\t");
			}
			printf("\t   %.2f $\t", requests[pos].price);
			print_typeUser(requests[pos].user_type);
			printf("\t%s\n", requests[pos].user_name);
		}
	} else {
		printf("\nATENÇÃO: Não existe nenhuma requisição registada!\n");
	}
}

/**
 * @brief List requests by laptop_id
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptopId 
 * @param preMessage 
 */
void list_requests_by_laptop_id(typeRequest *requests, unsigned int numberRequests, int laptopId, char *preMessage) {
	if (requests != NULL && numberRequests > 0) {
		printf("%sCode\tTipo cliente\tPrazo\tEstado\n", preMessage);
		for (unsigned int pos = 0; pos < numberRequests; pos++) {
			if (requests[pos].laptop_id == laptopId) {
				printf("%s", preMessage);	// Print message before request data
				printf(" %s\t", requests[pos].code);
				print_typeUser(requests[pos].user_type);
				printf("\t%d\t", requests[pos].deadline);
				print_typeReqState(requests[pos].requisition_state);
				printf("\n");
			}
		}
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
