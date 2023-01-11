#include "breakdowns.h"
#include <stdlib.h>
#include <limits.h>

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
 * @brief Print type of breakdown
 * 
 * @param break_type 
 */
void print_typeBreak(enum typeBreak break_type) {
	switch (break_type) {
	case TEMPORARY:
		printf("Temporário");
		break;
	case PERMANENT:
		printf("Permanente");
		break;
	}
}

/**
 * @brief Count number of breakdowns with a laptop_id
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param laptopId 
 * @return int number of breakdowns 
 */
int count_breakdowns_by_laptop_id(typeBreakdown *breakdowns, unsigned int numberBreakdowns, int laptopId) {
	int count = 0;

	if (numberBreakdowns > 0) {
		for (unsigned int i = 0; i < numberBreakdowns; i++) {
			if (breakdowns[i].laptop_id == laptopId) {
				count++;
			}
		}
	}

	return count;
}

/**
 * @brief Get max breakdown id
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @return int max id 
 */
int get_max_breakdown_id(typeBreakdown *breakdowns, unsigned int numberBreakdowns) {
	int id = -1;

	if (breakdowns != NULL) {
		if (numberBreakdowns > 0) {
			for (unsigned int i = 0; i < numberBreakdowns; i++) {
				if (breakdowns[i].id > id) {
					id = breakdowns[i].id;
				}
			}
		} else {
			id = 0;
		}
	}

	return id;
}

/**
 * @brief Search for breakdown ID
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param id 
 * @return -1 if not found
 * @return int position of id 
 */
int search_breakdown_id(typeBreakdown *breakdowns, unsigned int numberBreakdowns, int id) {
	int result = -1;
	unsigned int pos;

	for (pos = 0; pos < numberBreakdowns; pos++) {
		if (breakdowns[pos].id == id) {
			result = pos;
			pos = numberBreakdowns;
		}
	}
	
	return result;
}

/**
 * @brief Insert a breakdown in the vector
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @return -1 failure to insert breakdown
 * @return 0 success to insert breakdown
 */
int insert_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, int laptopId) {
	typeBreakdown breakdown;
	int tmp, control, result = -1;

	// Allocate space for the new breakdown
	typeBreakdown *save = *breakdowns;

	*breakdowns = realloc(*breakdowns, (*numberBreakdowns + 1) * sizeof(typeBreakdown));
	if (*breakdowns != NULL) {
		// Define breakdown id
		breakdown.id = get_max_breakdown_id(*breakdowns, *numberBreakdowns) + 1;

		do {	// Read type of breakdown
			tmp = lerInteiro("Insira o tipo de avaria do portátil\n\t0 - Temporária\n\t1 - Permanente\n", 0, 1);
			control = set_typeBreak(&(breakdown.break_type), tmp);

			if (control != 0) {	// If not valid
				printf("\nATENÇÃO: Insira uma localização válida\n");
			}
		} while (control != 0);

		// Read date of breakdown
		read_date("Insira a data de avaria", &(breakdown.date));

		// Set duration to -1 standing for not repaired
		breakdown.duration = -1;

		// Store laptop ID and duration
		breakdown.laptop_id = laptopId;
		
		(*breakdowns)[*numberBreakdowns] = breakdown;
		(*numberBreakdowns)++;
		
		result = 0;
	} else {
		*breakdowns = save;
		printf("ERRO: Falha na alocação de memória!\n");
	}
	
	return result;
}

/**
 * @brief Delete a breakdown from vector
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param id 
 * @return -1 failure deleting
 * @return int success deleting
 */
int delete_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, int id) {
	int result = -1, pos;

	typeBreakdown *save = *breakdowns;
	pos = search_breakdown_id(*breakdowns, *numberBreakdowns, id);

	if (*breakdowns != NULL && *numberBreakdowns > 0 && pos > -1) {
		// Replace the breakdown deleted by the last in vector
		if (*numberBreakdowns > 1) {
			(*breakdowns)[pos] = (*breakdowns)[*numberBreakdowns-1];
		}

		// Resize vector
		*breakdowns = realloc(*breakdowns, (*numberBreakdowns - 1) * sizeof(typeBreakdown));
		if (*breakdowns != NULL) {
			(*numberBreakdowns)--;
			result = 0;
		} else {
			*breakdowns = save;
			printf("Falha na alocação de memória!\n");
		}
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
 * @return -1 if failed to read breakdowns
 * @return int if success
 */
int read_breakdown_from_file(typeBreakdown **breakdowns, unsigned int *amount, FILE *file) {
	int result = -1;

	// Check if 'file' is valid
	if (file != NULL) {
		fseek(file, 0, SEEK_SET);
		// Get the amount of breakdowns in the file
		fread(amount, sizeof(unsigned int), 1, file);

		if (*amount > 0) {
			*breakdowns = malloc(*amount * sizeof(typeBreakdown));	// Alloc memory

			if (*breakdowns != NULL) {	// success to allocate memory
				// Read all breakdowns from the file to the vector 'breakdowns'
				result = fread(*breakdowns, sizeof(typeBreakdown), *amount, file);

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
		// Write amount and the requests
		fwrite(&amount, sizeof(unsigned int), 1, file);
		result = fwrite(breakdowns, sizeof(typeBreakdown), amount, file);
	}

	return result;
}