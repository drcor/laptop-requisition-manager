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
 * @brief Read a N number of requests from a file
 * The N number is given in the first 4 bytes of the file
 * 
 * @param requests 
 * @param amount 
 * @param file 
 * @return 1 if failed to read requests
 * @return 0 if success
 */
int read_request_from_file(typeRequest *requests, unsigned int *amount, FILE *file) {
	int result = 1;

	// Check if 'file' is valid
	if (file != NULL) {
		// Get the amount of requests in the file
		fread(amount, sizeof(unsigned int), 1, file);

		if (*amount > 0) {
			requests = malloc(*amount * sizeof(typeRequest));	// Allocate memory

			if (requests != NULL) {	// success to allocate memory
				// Read all reuquests from the file to the vector 'requests'
				if (fread(requests, sizeof(typeRequest), *amount, file) == *amount) {
					result = 0;
				}
			}
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
		if (amount > 0) {
			// Write amount and the requests
			fwrite(&amount, sizeof(unsigned int), 1, file);
			fwrite(requests, sizeof(typeRequest), amount, file);

			result = 0;
		}
	}

	return result;
}
