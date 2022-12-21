#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <wchar.h>

/* Date format */
typedef struct {
	uint8_t day;	// (1-31)
	uint8_t month;	// (1-12)
	uint16_t year;
} typeDate;

/* Check if 'year' is a leap year */
bool is_leap_year(uint16_t year);
/* Check if date format is correct and valid */
int validate_date(typeDate date);
/* Print date in text format */
void print_date(typeDate date);
/* Read date from input */
void read_date(wchar_t *message, typeDate *date);

#endif	// DATE_H_INCLUDED