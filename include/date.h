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

#endif	// DATE_H_INCLUDED