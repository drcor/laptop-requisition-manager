#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

#include <stdint.h>

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


/* Enumeration of locations */
enum typeLocal {
	RESIDENCES=0,
	CAMPUS1=1,
	CAMPUS2=2,
	CAMPUS5=5
};
/* Set location from a integer */
int set_typeLocal(enum typeLocal *location, int num);


/* Enumeration of breakdown types */
enum typeBreak {
	TEMPORARY,	// 0
	PERMANENT	// 1
};
/* Set type of breakdown from a integer */
int set_typeBreak(enum typeBreak *breakdown_type, int num);


/* Enumeration of type of user */
enum typeUser {
	STUDENT,		// 0
	TEACHER,		// 1
	ADMNISTRATIVE	// 2
};
/* Set type of user from a integer */
int set_typeUser(enum typeUser *user_type, int num);

/* Enumeration of type of requisition state */
enum typeReqState {
	ACTIVE,	// 0
	DONE	// 1
};
/* Set type of requisition state from a number */
int set_typeReqState(enum typeReqState *req_state, int num);


/* Data format */
typedef struct {
	uint8_t dia;
	uint8_t mes;
	uint16_t ano;
} typeDate;

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

/* Breakdowns information */
typedef struct {
	unsigned int id;
	unsigned int laptop_id;
	enum typeBreak break_type;
	typeDate date;
	unsigned int duration;
} typeBreakdown;

/* Requests information */
typedef struct {
	char code[10];
	unsigned int laptop_id;
	char user_name[60];
	enum typeUser user_type;
	typeDate requisition_date;
	unsigned short deadline;
	enum typeReqState requisition_state;
	typeDate devolution_date;
	enum typeLocal devolution_local;
	float price;
} typeRequest;

#endif // ELEMENTS_H_INCLUDED
