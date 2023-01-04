#ifndef REQUESTS_H_INCLUDED
#define REQUESTS_H_INCLUDED

#include "generic.h"
#include "date.h"
#include <stdio.h>

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

/* Read a N number of requests from a file */
int read_request_from_file(typeRequest **requests, unsigned int *amount, FILE *file);
/* Write a vector os requests to a file */
int write_request_to_file(typeRequest *requests, unsigned int amount, FILE *file);

#endif // REQUESTS_H_INCLUDED
