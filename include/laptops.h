#ifndef LAPTOPS_H_INCLUDE
#define LAPTOPS_H_INCLUDED

#include "elements.h"
#include "date.h"

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
	enum typeLocal location;
	typeDate date;
	float price;
} typeLaptop;

#endif // LAPTOPS_H_INCLUDED
