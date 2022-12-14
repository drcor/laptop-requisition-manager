#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

/* Date format */
typedef struct {
	uint8_t day;	// (1-31)
	uint8_t month;	// (1-12)
	uint16_t year;
} typeDate;

/* Check if 'year' is a leap year */
bool is_leap_year(uint16_t year);

#endif	// DATE_H_INCLUDED