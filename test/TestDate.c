#include <assert.h>
#include "../include/date.h"
#include <stdio.h>
#include <string.h>

void test_IsLeapYear(void) {
	/* All of these tests should pass */
	assert(true == is_leap_year(2004));
	assert(true == is_leap_year(1848));
	assert(true == is_leap_year(2400));
	assert(false == is_leap_year(1900));
	assert(false == is_leap_year(2022));
	assert(false == is_leap_year(2365));

	printf(" PASSED - is_leap_year()\n");
}

void test_ValidateDate(void) {
	// Success
	typeDate date1 = {31, 12, 2022};
	typeDate date2 = {29, 2, 2004};		// leap year
	typeDate date3 = {1, 1, 1800};
	// Failure
	typeDate date4 = {29, 2, 2022};
	typeDate date5 = {32, 10, 2014};
	typeDate date6 = {0, 9, 2022};
	typeDate date7 = {5, 13, 2022};
	typeDate date8 = {18, 0, 2022};

	/* All of these tests should pass */
	// Success tests
	assert(validate_date(date1) == 0);
	assert(validate_date(date2) == 0);
	assert(validate_date(date3) == 0);
	// Failure tests
	assert(1 == validate_date(date4));	// invalid day
	assert(1 == validate_date(date5));
	assert(1 == validate_date(date6));
	assert(2 == validate_date(date7));	// invalid month
	assert(2 == validate_date(date8));

	printf(" PASSED - validate_date()\n");
}

void test_PrintDate(void) {
	// Success
	typeDate date1 = {9, 3, 2004};
	typeDate date2 = {29, 2, 2020};
	typeDate date3 = {9, 3, 2004};
	// Failure
	typeDate date4 = {30, 13, 2012};
	typeDate date5 = {32, 5, 2012};
	
	// Success tests
	print_date(date1);
	printf("\n");
	print_date(date2);
	printf("\n");
	print_date(date3);
	printf("\n");
	// Failure tests
	print_date(date4);
	print_date(date5);

	printf(" PASSED - print_date()\n");
}

void test_ReadDate(void) {
	typeDate date;

	read_date("Insira a data", &date);
	printf("done\n");
	print_date(date);

	printf(" PASSED - read_date()\n");
}

// Test include/date.h
void group_Date(void) {
	test_IsLeapYear();
	test_ValidateDate();
	test_PrintDate();
	// test_ReadDate();
}
