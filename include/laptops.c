#include "laptops.h"
#include <stdlib.h>

/**
 * @brief Set type of cpu from a integer
 * 
 * @param cpu 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeCPU
 * @return 0 if 'num' exists in typeCPU
 */
int set_typeCPU(enum typeCPU *cpu, int num) {
	int result = 0;
	switch (num) {
	case I3:
		*cpu = I3;
		break;
	case I5:
		*cpu = I5;
		break;
	case I7:
		*cpu = I7;
		break;
	default:
		result = -1;
		break;
	}

	return result;
}

/**
 * @brief Set the state of laptop from a integer
 * 
 * @param state 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeState
 * @return 0 if 'num' exists in typeState
 */
int set_typeState(enum typeState *state, int num) {
	int result = 0;
	switch (num) {
	case BROKEN:
		*state = BROKEN;
		break;
	case AVAILABLE:
		*state = AVAILABLE;
		break;
	case TAKEN:
		*state = TAKEN;
		break;
	default:
		result = -1;
		break;
	}

	return result;
}

/**
 * @brief Read a N number of laptops from a file
 * The N number is given in the first 4 bytes of the file
 * 
 * @param laptops 
 * @param amount
 * @param file 
 * @return 1 if failed to read laptops
 * @return 0 if success
 */
int read_laptop_from_file(typeLaptop *laptops, unsigned int *amount, FILE *file) {
	int result = 1;

	// Check if 'file' is valid
	if (file != NULL) {
		// Get the amount of laptops in the file
		fread(amount, sizeof(unsigned int), 1, file);

		if (*amount != 0) {
			laptops = malloc(*amount * sizeof(typeLaptop)); // Allocate memory

			if (laptops != NULL) {	// failed to allocate memory
				// Read all laptops from the file to the vector 'laptops'
				if (fread(laptops, sizeof(typeLaptop), *amount, file) == *amount) {
					result = 0;
				}
			}
		}
	}

	return result;
}

/**
 * @brief Write all laptops to a file
 * 
 * @param laptops 
 * @param amount 
 * @param file 
 * @return 1 if failed to write laptops
 * @return 0 if success
 */
int write_laptop_to_file(typeLaptop *laptops, unsigned int amount, FILE *file) {
	int result = 1;

	// Check if 'file' is valid and there is any laptop to write
	if (file != NULL) {
		if (amount > 0) {
			// Write amount and the laptops
			fwrite(&amount, sizeof(unsigned int), 1, file);
			fwrite(laptops, sizeof(typeLaptop), amount, file);

			result = 0;
		}
	}

	return result;
}