#include <assert.h>
#include <stdio.h>
#include "../include/requests.h"
#include "../include/date.h"

void test_SetTypeUser(void) {
	enum typeUser temp;
	/* All of these tests should pass */
	// Success tests
	assert(set_typeUser(&temp, 0) == 0);	// STUDENT
	assert(set_typeUser(&temp, 1) == 0);	// TEACHER
	assert(set_typeUser(&temp, 2) == 0);	// ADMNISTRATIVE
	// Failure tests
	assert(set_typeUser(&temp, -1) == -1);
	assert(set_typeUser(&temp, 3) == -1);


	printf(" PASSED - set_typeUser()\n");
}

void test_SetTypeReqState(void) {
	enum typeReqState temp;
	/* All of these tests should pass */
	// Success tests
	assert(set_typeReqState(&temp, 0) == 0);	// ACTIVE
	assert(set_typeReqState(&temp, 1) == 0);	// DONE
	// Failure tests
	assert(set_typeReqState(&temp, -1) == -1);
	assert(set_typeReqState(&temp, 2) == -1);


	printf(" PASSED - set_typeReqState()\n");
}

void test_WriteRequestToFile(void) {
	typeDate date = {17,12,2022};
	typeDate dev_date = {26,12,2022};
	typeRequest requests[9] = {{
		"ABCD",
		12345,
		"drcor",
		STUDENT,
		date,
		9,
		ACTIVE,
		dev_date,
		CAMPUS1,
		0.0
	}};
	FILE *file = NULL;
	file = fopen("test/resources/requests.bin", "wb");

	// Success test
	assert(write_request_to_file(requests, 9, file) == 0);

	// Failure tests
	assert(write_request_to_file(requests, 0, file) == 1);
	file = NULL;
	assert(write_request_to_file(requests, 9, file) == 1);

	fclose(file);

	printf(" PASSED - write_request_to_file()\n");
}

void test_ReadRequestFromFile(void) {
	typeRequest *requests = NULL;
	unsigned int amount_laps;
	FILE *file = NULL;
	file = fopen("test/resources/requests.bin", "rb");

	// Success test
	assert(read_request_from_file(requests, &amount_laps, file) == 0);
	assert(amount_laps == 9);
	
	//Failures tests
	file = freopen("test/resources/requests_fail1.bin", "rb", file);
	assert(read_request_from_file(requests, &amount_laps, file) == 1);
	file = freopen("test/resources/requests_fail2.bin", "rb", file);
	assert(read_request_from_file(requests, &amount_laps, file) == 1);
	file = NULL;
	assert(read_request_from_file(requests, &amount_laps, file) == 1);


	fclose(file);

	printf(" PASSED - read_request_from_file()\n");
}

// Test include/requests.h
void group_Requests(void) {
	test_SetTypeReqState();
	test_ReadRequestFromFile();
	test_WriteRequestToFile();
}
