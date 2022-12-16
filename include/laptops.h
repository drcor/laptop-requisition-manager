#ifndef LAPTOPS_H_INCLUDE
#define LAPTOPS_H_INCLUDED

#include "elements.h"
#include "date.h"
#include <stdio.h>

#define MAX_LAPTOPS 30

/* Enumeration of cpu's */
enum typeCPU {
	I3=3,
	I5=5,
	I7=7
};
/* Set type of cpu from a integer */
int set_typeCPU(enum typeCPU *tmp, int num);

/* Enumeration of laptop's states */
enum typeState {
	BROKEN=-1,
	AVAILABLE=0,
	TAKEN=1
};
/* Set the state of laptop from a integer */
int set_typeState(enum typeState *state, int num);

/* Laptop information */
typedef struct {
	unsigned int id;
	char subtitle[100];
	enum typeCPU cpu;			// i3=3, i5=5, i7=7
	unsigned int memory;		// MB
	enum typeState state;		// broken=-1, available=0, taken=1
	enum typeLocal location;	// RESIDENCES=0,CAMPUS1=1,CAMPUS2=2,CAMPUS5=5
	typeDate date;
	float price;
} typeLaptop;

/* Read a N number of laptops from a file */
int read_laptop_from_file(typeLaptop *laptops, unsigned int *amount, FILE *file);
/* Write all laptops to a file */
int write_laptop_to_file(typeLaptop *laptops, unsigned int amount, FILE *file);

#endif // LAPTOPS_H_INCLUDED
