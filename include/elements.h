#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

#include <stdint.h>

/* Enumeration of locations */
enum typeLocal {
	RESIDENCES=0,
	CAMPUS1=1,
	CAMPUS2=2,
	CAMPUS5=5
};
/* Set location from a integer */
int set_typeLocal(enum typeLocal *location, int num);

/* Check if 'number' is in range from 'min' to 'max' */
int check_range(int number, int min, int max);

#endif // ELEMENTS_H_INCLUDED
