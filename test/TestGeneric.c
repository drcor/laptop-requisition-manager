#include <assert.h>
#include "../include/generic.h"
#include <stdio.h>

void test_SetTypeLocal(void) {
	enum typeLocal temp;
	/* All of these tests should pass */
	// Success tests
	assert(set_typeLocal(&temp, 0) == 0);	// RESIDENCES
	assert(set_typeLocal(&temp, 1) == 0);	// CAMPUS1
	assert(set_typeLocal(&temp, 2) == 0);	// CAMPUS2
	assert(set_typeLocal(&temp, 5) == 0);	// CAMPUS5
	// Failure tests
	assert(set_typeLocal(&temp, -8) == -1);
	assert(set_typeLocal(&temp, 15) == -1);


	printf(" PASSED - set_typeLocal()\n");
}

void test_CheckRange(void) {
	/* All of these tests should pass */
	// Success tests
	assert(check_range(15, 14, 16) == 0);
	assert(check_range(0, -60, 20) == 0);
	assert(check_range(-22, -25, -10) == 0);
	// Failure tests
	assert(check_range(15, 17, 19) == -1);
	assert(check_range(-15, -12, -8) == -1);
	assert(check_range(15, 12, 14) == 1);
	assert(check_range(-58, -79, -60) == 1);


	printf(" PASSED - check_range()\n");
}

// Test include/elements.h
void group_Elements(void) {
	test_SetTypeLocal();
	test_CheckRange();
}
