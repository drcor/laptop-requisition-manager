#include "breakdowns.h"

/**
 * @brief Set type of breakdown from a integer
 * 
 * @param breakdown_type 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeBreak
 * @return 0 if 'num' exists in typeBreak
 */
int set_typeBreak(enum typeBreak *breakdown_type, int num) {
	int result = 0;
	switch (num) {
	case TEMPORARY:
		*breakdown_type = TEMPORARY;
		break;
	case PERMANENT:
		*breakdown_type = PERMANENT;
		break;
	default:
		result = -1;
		break;
	}

	return result;
}

/**
 * @brief Read a N number of breakdowns from a file
 * The N number is given in the first 4 bytes of the file
 * 
 * @param breakdowns 
 * @param amount 
 * @param file 
 * @return 1 if failed to read breakdowns
 * @return 0 if success
 */
int read_breakdown_from_file(typeBreakdown *breakdowns, unsigned int *amount, FILE *file) {
	int result = 1;

	// Check if 'file' is valid
	if (file != NULL) {
		// Get the amount of breakdowns in the file
		fread(amount, sizeof(unsigned int), 1, file);

		if (*amount > 0) {
			breakdowns = malloc(*amount * sizeof(typeBreakdown));	// Alloc memory

			if (breakdowns != NULL) {	// success to allocate memory
				// Read all breakdowns from the file to the vector 'breakdowns'
				if (fread(breakdowns, sizeof(typeBreakdown), *amount, file)  == *amount) {
					result = 0;
				}
			}
		}
	}

	return result;
}

/**
 * @brief Write vector of breakdowns to a file
 * 
 * @param breakdowns 
 * @param amount 
 * @param file 
 * @return -1 if failed to write breakdowns
 * @return 0 if success
 */
int write_breakdown_to_file(typeBreakdown *breakdowns, unsigned int amount, FILE *file) {
	int result = 1;

	// Check if 'file' is valid and there is any breakdown to write
	if (file != NULL) {
		if (amount > 0) {
			// Write amount and the requests
			fwrite(&amount, sizeof(unsigned int), 1, file);
			fwrite(breakdowns, sizeof(typeBreakdown), amount, file);

			result = 0;
		}
	}

	return result;
}