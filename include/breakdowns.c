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

	for (unsigned int i = 0; i < numberBreakdowns; i++) {
		if (breakdowns[i].id == id) {
			result = i;
			i = numberBreakdowns;
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
int insert_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, unsigned int laptopId) {
	typeBreakdown breakdown;
	int tmp, control, result = -1;

	// Allocate space for the new breakdown
	typeBreakdown *save = *breakdowns;

	*breakdowns = realloc(*breakdowns, (*numberBreakdowns + 1) * sizeof(typeBreakdown));
	if (*breakdowns != NULL) {
		// Read id
		do {
			breakdown.id = lerInteiro(L"Insira o ID do da avaria", 0, INT_MAX);
			control = search_breakdown_id(*breakdowns, *numberBreakdowns, breakdown.id);	// TODO: search_breakdown_id()
			if (control != -1) {
				wprintf(L"ATENÇÃO: Não pode inserir um ID repetido\n");
			}
		} while (control != -1);

			
		do {	// Read type of breakdown
			tmp = lerInteiro(L"Insira o tipo de avaria do portátil\n\t0 - Temporária\n\t1 - Permanente\n", 0, 1);
			control = set_typeBreak(&(breakdown.break_type), tmp);

			if (control != 0) {	// If not valid
				wprintf(L"\nATENÇÃO: Insira uma localização válida\n");
			}
		} while (control != 0);

		// Read date of breakdown
		read_date(L"Insira a data de avaria", &(breakdown.date));

		// Store laptop ID
		breakdown.laptop_id = laptopId;
		
		(*breakdowns)[*numberBreakdowns] = breakdown;
		(*numberBreakdowns)++;
		// list_breakdowns(*breakdowns, *numberBreakdowns);	// Debug
		result = 0;
	} else {
		*breakdowns = save;
		wprintf(L"Falha na alocação de memória!\n");
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