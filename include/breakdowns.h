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
int set_typeBreak(enum typeBreak *breakdown_type, int num);

/* Breakdowns information */
typedef struct {
	unsigned int id;
	unsigned int laptop_id;
	enum typeBreak break_type;
	typeDate date;
	unsigned int duration;
} typeBreakdown;

/* Read a N number of breakdowns from a file */
int read_breakdown_from_file(typeBreakdown *breakdowns, unsigned int *amount, FILE *file);
/* Write vector of breakdowns to a file */
int write_breakdown_to_file(typeBreakdown *breakdowns, unsigned int amount, FILE *file);

#endif // BREAKDOWNS_H_INCLUDED
