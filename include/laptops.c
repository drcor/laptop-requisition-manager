#include "laptops.h"
#include "date.h"
#include "generic.h"
#include <stdlib.h>
#include <stdint.h>

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
 * @brief Search for laptop ID
 * 
 * @param laptops 
 * @param numberLaptops 
 * @param id 
 * @return -1 if not found
 * @return int position of id 
 */
int search_laptop_id(typeLaptop *laptops, unsigned int numberLaptops, int id) {
	int result = -1;

	for (unsigned int i = 0; i < numberLaptops; i++) {
		if (laptops[i].id == id) {
			result = i;
			i = numberLaptops;
		}
	}
	
	return result;
}

/**
 * @brief Insert a laptop in the vector
 * 
 * @param laptops 
 * @param numberLaptops 
 * @return pointer of vector
 */
int insert_laptop(typeLaptop **laptops, unsigned int *numberLaptops) {
	typeLaptop laptop;
	int tmp, control, result = -1;

	// Allocate space for the new laptop
	typeLaptop *save = *laptops;

	*laptops = realloc(*laptops, (*numberLaptops + 1) * sizeof(typeLaptop));
	if (*laptops != NULL) {
		// Check if vector is full
		if (*numberLaptops < 30) {
			// Read id
			do {
				laptop.id = lerInteiro(L"Insira o ID do portátil: ", 0, MAX_LAPTOPS);
				control = search_laptop_id(*laptops, *numberLaptops, laptop.id);
				if (control != -1) {
					wprintf(L"ATENÇÃO: Não pode inserir um ID repetido\n");
				}
			} while (control != -1);

			do {	// Read type of CPU
				tmp = lerInteiro(L"Insira o tipo de CPU\n\t3 - i3\n\t5 - i5\n\t7- i7\n: ", 3, 7);
				control = set_typeCPU(&(laptop.cpu), tmp);

				if (control != 0) {	// If not valid
					wprintf(L"\nATENÇÃO: Insira um CPU válido\n");
				}
			} while (control != 0);

			// Read memory of laptop
			laptop.memory = lerInteiro(L"Insira o valor de memoria RAM em Gigabytes: ", 0, 256);
			
			// Set state of laptop	
			laptop.state = AVAILABLE;

			do {	// Read location of laptop
				tmp = lerInteiro(L"Insira a localização do portátil\n\t0 - Residências\n\t1 - Campus 1\n\t2 - Campus 2\n\t5 - Campus 5\n: ", 0, 5);
				control = set_typeLocal(&(laptop.location), tmp);

				if (control != 0) {	// If not valid
					wprintf(L"\nATENÇÃO: Insira uma localização válida\n");
				}
			} while (control != 0);

			// Read date of aquisition
			read_date(L"Insira a data de aquisição", &(laptop.date));
			// Read price
			laptop.price = lerFloat(L"Insira o preço do portátil em €", 0.0, 10000.0);
			// Read Subtitle
			lerString(L"Insira a descrição do portátil: ", laptop.subtitle, SUBTITLE_SIZE);
		}

		(*laptops)[*numberLaptops] = laptop;
		(*numberLaptops)++;
		list_laptops(*laptops, *numberLaptops);
		result = 0;
	} else {
		*laptops = save;
		wprintf(L"Falha na alocação de memória!\n");
	}
	
	return result;
}

/**
 * @brief List all laptops
 * 
 * @param laptops 
 * @param numberLaptops 
 */
/* TODO: Add extra information */
void list_laptops(typeLaptop *laptops, unsigned int numberLaptops) {
	// Check if exist any laptop
	if (laptops != NULL && numberLaptops != 0) {
		wprintf(L"ID\tCPU\tMem.\tEstado\tLocal\tData\t\tMulta\tDescrição\n");
		for (size_t i = 0; i < numberLaptops; i++) {
			wprintf(L"%d\ti%d\t%dGB\t", laptops[i].id, laptops[i].cpu, laptops[i].memory);
			wprintf(L"%d\t%d\t", laptops[i].state, laptops[i].location);
			print_date(laptops[i].date);
			wprintf(L"\t%.2f\t%s\n", laptops[i].price, laptops[i].subtitle);
		}
	} else {
		wprintf(L"ATENÇÃO: Não existe nenhum portátil registado!\n");
	}
}

/**
 * @brief Update the location of laptop
 * 
 * @param laptops 
 * @param numberLaptops 
 * @param id 
 * @return -1 failure to update laptop location
 * @return int postion of laptop updated 
 */
int update_laptop_location(typeLaptop **laptops, unsigned int numberLaptops) {
	int aux, pos, control;

	if (*laptops != NULL && numberLaptops != 0) {
		aux = lerInteiro(L"Insira o ID do portátil: ", INT_MIN, INT_MAX);
		pos = search_laptop_id(*laptops, numberLaptops, aux);

		if (pos != -1) {
			do {	// Read location of laptop
				aux = lerInteiro(L"Insira a localização do portátil\n\t0 - Residências\n\t1 - Campus 1\n\t2 - Campus 2\n\t5 - Campus 5\n: ", 0, 5);
				control = set_typeLocal(&((*laptops[pos]).location), aux);

				if (control != 0) {	// If not valid
					wprintf(L"\nATENÇÃO: Insira uma localização válida\n");
				}
			} while (control != 0);
		}
	}

	return pos;
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

		if (*amount > 0) {
			laptops = malloc(*amount * sizeof(typeLaptop)); // Allocate memory

			if (laptops != NULL) {	// success to allocate memory
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