#ifndef BREAKDOWNS_H_INCLUDED
#define BREAKDOWNS_H_INCLUDED

#include "elements.h"
#include "date.h"

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

#endif // BREAKDOWNS_H_INCLUDED
