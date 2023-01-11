#ifndef LAPTOPS_H_INCLUDE
#define LAPTOPS_H_INCLUDED

#include "generic.h"
#include "date.h"
#include <stdio.h>

#define MAX_LAPTOPS 	30
#define DESCRIPTION_SIZE	100

/* Enumeration of cpu's */
enum typeCPU {
	I3=3,
	I5=5,
	I7=7
};
/* Set type of cpu from a integer */
int set_typeCPU(enum typeCPU *cpu, int num);
/* Print the type of CPU */
void print_typeCPU(enum typeCPU cpu);

/* Enumeration of laptop's states */
enum typeState {
	AVAILABLE,
	TAKEN,
	BROKEN
};
/* Set the state of laptop from a integer */
int set_typeState(enum typeState *state, int num);
/* Print the state of laptop */
void print_typeState(enum typeState state);

/* Laptop information */
typedef struct {
	int id;
	char description[DESCRIPTION_SIZE];
	enum typeCPU cpu;			// i3=3, i5=5, i7=7
	int memory;		// GB
	enum typeState state;		// available=0, taken=1, broken=2
	enum typeLocal location;	// RESIDENCES=0,CAMPUS1=1,CAMPUS2=2,CAMPUS5=5
	typeDate date;
	float price;
} typeLaptop;

/* Get max laptop id */
int get_max_laptop_id(typeLaptop *laptops, unsigned int numberLaptops);
/* Search laptop by id */
int search_laptop_id(typeLaptop *laptops, unsigned int numberLaptops, int id);
/* Insert a laptop in the vector */
int insert_laptop(typeLaptop **laptops, unsigned int *numberLaptops);
/* Update the location of laptop */
int update_laptop_location(typeLaptop **laptops, unsigned int numberLaptops);
/* Read a N number of laptops from a file */
int read_laptop_from_file(typeLaptop **laptops, unsigned int *amount, FILE *file);
/* Write a vector of laptops to a file */
int write_laptop_to_file(typeLaptop *laptops, unsigned int amount, FILE *file);

#endif // LAPTOPS_H_INCLUDED
