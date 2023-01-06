#include <assert.h>
#include <stdio.h>
#include "../include/breakdowns.h"

void test_SetTypeBreak(void) {
	enum typeBreak temp;
	/* All of these tests should pass */
	// Success tests
	assert(set_typeBreak(&temp, 0) == 0);	// TEMPORARY
	assert(set_typeBreak(&temp, 1) == 0);	// PERMANENT
	// Failure tests
	assert(set_typeBreak(&temp, -8) == -1);
	assert(set_typeBreak(&temp, 15) == -1);


	printf(" PASSED - set_typeBreak()\n");
}

void test_WriteBreakdownToFile(void) {
	typeDate date = {17,12,2022};
	typeBreakdown breakdowns = {
		54321,
		12345,
		TEMPORARY,
		date,
		15
	};
	FILE *file = NULL;
	file = fopen("test/resources/breakdowns.bin", "wb");

	// Success test
	assert(write_breakdown_to_file(&breakdowns, 1, file) == 0);

	// Failure tests
	assert(write_breakdown_to_file(&breakdowns, 0, file) == 1);
	fclose(file);
	file = NULL;
	assert(write_breakdown_to_file(&breakdowns, 1, file) == 1);


	printf(" PASSED - write_breakdown_to_file()\n");
}

void test_ReadBreakdownFromFile(void) {
	typeBreakdown *breakdowns = NULL;
	unsigned int amount_laps;
	FILE *file = NULL;
	file = fopen("test/resources/breakdowns.bin", "rb");

	// Success test
	assert(read_breakdown_from_file(breakdowns, &amount_laps, file) == 0);
	assert(amount_laps == 1);
	
	//Failures tests
	file = freopen("test/resources/breakdowns_fail1.bin", "rb", file);
	assert(read_breakdown_from_file(breakdowns, &amount_laps, file) == 1);
	file = freopen("test/resources/breakdowns_fail2.bin", "rb", file);
	assert(read_breakdown_from_file(breakdowns, &amount_laps, file) == 1);
	file = NULL;
	assert(read_breakdown_from_file(breakdowns, &amount_laps, file) == 1);


	fclose(file);

	printf(" PASSED - read_breakdown_from_file()\n");
}

// Test include/breakdowns.h
void group_Breakdowns(void) {
	test_SetTypeBreak();
	test_ReadBreakdownFromFile();
	test_WriteBreakdownToFile();
}
