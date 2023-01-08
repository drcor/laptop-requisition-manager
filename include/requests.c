#include "requests.h"
#include <stdlib.h>

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
