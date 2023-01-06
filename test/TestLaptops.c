#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/laptops.h"

void test_SetTypeCPU(void) {
	enum typeCPU temp;
	/* All of these tests should pass */
	// Success tests
	assert(set_typeCPU(&temp, 3) == 0);	// I3
	assert(set_typeCPU(&temp, 5) == 0);	// I5
	assert(set_typeCPU(&temp, 7) == 0);	// I7
	// Failure tests
	assert(set_typeCPU(&temp, 2) == -1);
	assert(set_typeCPU(&temp, 4) == -1);
	assert(set_typeCPU(&temp, 6) == -1);

	printf(" PASSED - set_typeCPU()\n");
}

void test_SetTypeState(void) {
	enum typeState temp;
	/* All of these tests should pass */
	// Success tests
	assert(set_typeState(&temp, 0) == 0);	// AVAILABLE
	assert(set_typeState(&temp, 1) == 0);	// TAKEN
	assert(set_typeState(&temp, 2) == 0);	// BROKEN
	// Failure tests
	assert(set_typeState(&temp, 3) == -1);
	assert(set_typeState(&temp, -2) == -1);

	printf(" PASSED - set_typeState()\n");
}

void test_SearchLaptops(void) {
	typeLaptop laptops[2] = {{
		1,
		"hello",
		I7,
		8,
		AVAILABLE,
		RESIDENCES,
		{2,3,4},
		0.0
	},{
		15,
		"hello",
		I7,
		8,
		AVAILABLE,
		RESIDENCES,
		{2,3,4},
		0.0
	}};

	// Success
	assert(search_laptop_id(laptops, 2, 15) == 1);
	// Failure
	assert(search_laptop_id(laptops, 2, 18) == -1);

	printf(" PASSED - search_laptop_id()\n");
}

void test_InsertLaptop(void) {
	typeLaptop *laptops;
	laptops = malloc(1 * sizeof(typeLaptop));
	laptops[0].id = 15;
	strcpy(laptops[0].description, "hello");
	laptops[0].cpu = I7;
	laptops[0].memory = 8;
	laptops[0].state = BROKEN;
	laptops[0].location = RESIDENCES;
	typeDate date = {9,3,2004};
	laptops[0].date = date;
	laptops[0].price = 0.0;
	unsigned int size = 1;

	// Success
	assert(insert_laptop(&laptops, &size) == 0);
	assert(size == 2);
	list_laptops(laptops, size);

	free(laptops);

	printf(" PASSED - insert_laptop()\n");
}

void test_ListLaptops(void) {
	unsigned int size = 1;
	typeLaptop laptops[1] = {{
		15,
		"hello",
		I7,
		8,
		AVAILABLE,
		RESIDENCES,
		{2,3,4},
		0.0
	}};

	// Success
	list_laptops(laptops, size);

	printf(" PASSED - list_laptops()\n");
}

void test_WriteLaptopToFile(void) {
	typeDate date = {16,12,2022};
	typeLaptop laptops[9] = {{
		12345,			// id
		"Test subs!",	// subtitle
		I5,				// cpu
		4096,			// memory
		AVAILABLE,		// state
		CAMPUS2,		// location
		date,			// date
		20.0			// price
	}};
	FILE *file = NULL;
	file = fopen("test/resources/laptops.bin", "wb");

	// Success test
	assert(write_laptop_to_file(laptops, 9, file) == 0);

	// Failure tests
	assert(write_laptop_to_file(laptops, 0, file) == 1);
	file = NULL;
	assert(write_laptop_to_file(laptops, 9, file) == 1);

	fclose(file);

	printf(" PASSED - write_laptop_to_file()\n");
}

void test_ReadLatopFromFile(void) {
	typeLaptop *laptops = NULL;
	unsigned int amount_laps;
	FILE *file = NULL;
	file = fopen("test/resources/laptops.bin", "rb");

	// Success test
	assert(read_laptop_from_file(laptops, &amount_laps, file) == 0);
	assert(amount_laps == 9);
	
	//Failures tests
	file = freopen("test/resources/laptops_fail1.bin", "rb", file);
	assert(read_laptop_from_file(laptops, &amount_laps, file) == 1);
	file = freopen("test/resources/laptops_fail2.bin", "rb", file);
	assert(read_laptop_from_file(laptops, &amount_laps, file) == 1);
	file = NULL;
	assert(read_laptop_from_file(laptops, &amount_laps, file) == 1);


	fclose(file);

	printf(" PASSED - read_laptop_from_file()\n");
}

// Test include/breakdowns.h
void group_Laptops(void) {
	test_SetTypeCPU();
	test_SetTypeState();
	test_SearchLaptops();
	test_ListLaptops();
	// test_InsertLaptop();
	// test_ReadLatopFromFile();
	// test_WriteLaptopToFile();
}
