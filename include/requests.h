#ifndef REQUESTS_H_INCLUDED
#define REQUESTS_H_INCLUDED

#include "generic.h"
#include "date.h"
#include <stdio.h>

#define CODE_SIZE 5
#define USERNAME_SIZE 60
#define DEADLINE_LIMIT 30

/* Enumeration of type of user */
enum typeUser {
	STUDENT,		// 0
	TEACHER,		// 1
	ADMNISTRATIVE	// 2
};
/* Set type of user from a integer */
int set_typeUser(enum typeUser *user_type, int num);
/* Print type of user */
void print_typeUser(enum typeUser user_type);

/* Enumeration of type of requisition state */
enum typeReqState {
	ACTIVE,	// 0
	DONE	// 1
};
/* Set type of requisition state from a number */
int set_typeReqState(enum typeReqState *req_state, int num);
/* Print type of requistion state */
void print_typeReqState(enum typeReqState req_state);

/* Requests information */
typedef struct {
	char code[CODE_SIZE];
	int laptop_id;
	char user_name[USERNAME_SIZE];
	enum typeUser user_type;
	typeDate requisition_date;
	unsigned short deadline;
	enum typeReqState requisition_state;
	typeDate devolution_date;
	enum typeLocal devolution_local;
	float price;
} typeRequest;

/* Count active requests */
int count_requests_active(typeRequest *requests, unsigned int numberRequests);
/* Count number of requests with a laptop_id */
int count_requests_by_laptop_id(typeRequest *requests, unsigned int numberRequests, int laptopId);
/* Search request by code */
int search_request_by_code(typeRequest *requests, unsigned int numberRequests, char code[CODE_SIZE]);
/* Insert a request in the vector */
int insert_request(typeRequest **requests, unsigned int *numberRequests, int laptopId, typeDate requisition_date);
/* List all requests */
void list_request(typeRequest *requests, unsigned int numberRequests);
/* List one request by code*/
void list_one_request(typeRequest *requests, unsigned int *numberRequests);
/* List requests by laptop_id */
void list_requests_by_laptop_id(typeRequest *requests, unsigned int numberRequests, int laptopId, char *preMessage);
/* Read a N number of requests from a file */
int read_request_from_file(typeRequest **requests, unsigned int *amount, FILE *file);
/* Write a vector of requests to a file */
int write_request_to_file(typeRequest *requests, unsigned int amount, FILE *file);

#endif // REQUESTS_H_INCLUDED
