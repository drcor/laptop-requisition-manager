#ifndef BREAKDOWNS_H_INCLUDED
#define BREAKDOWNS_H_INCLUDED

#include "generic.h"
#include "date.h"
#include <stdio.h>

/* Enumeration of breakdown types */
enum typeBreak {
	TEMPORARY,	// 0
	PERMANENT	// 1
};
/* Set type of breakdown from a integer */
int set_typeBreak(enum typeBreak *break_type, int num);
/* Print type of breakdown */
void print_typeBreak(enum typeBreak break_type);

/* Breakdowns information */
typedef struct {
	int id;
	int laptop_id;
	enum typeBreak break_type;
	typeDate date;
	int duration;
} typeBreakdown;

/* Get max id */
int get_max_id(typeBreakdown *breakdowns, unsigned int numberBreakdowns);
/* Search for breakdown ID */
int search_breakdown_id(typeBreakdown *breakdowns, unsigned int numberBreakdowns, int id);
/* Insert a breakdown in the vector */
int insert_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, int laptopId);
/* List all breakdowns */
void list_breakdowns(typeBreakdown *breakdowns, unsigned int numberBreakdowns);
/* Delete a breakdown from vector */
int delete_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, int id);
/* Read a N number of breakdowns from a file */
int read_breakdown_from_file(typeBreakdown **breakdowns, unsigned int *amount, FILE *file);
/* Write vector of breakdowns to a file */
int write_breakdown_to_file(typeBreakdown *breakdowns, unsigned int amount, FILE *file);

#endif // BREAKDOWNS_H_INCLUDED
