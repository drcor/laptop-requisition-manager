#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

#include <stdint.h>

/* Enumeration of locations */
enum typeLocal {
	NONE=-1,
	RESIDENCES=0,
	CAMPUS1=1,
	CAMPUS2=2,
	CAMPUS5=5
};
/* Set location from a integer */
int set_typeLocal(enum typeLocal *location, int num);
/* Print locations */
void print_typeLocal(enum typeLocal location);
/* Check if 'number' is in range from 'min' to 'max' */
int check_range(int number, int min, int max);
/* Compare two numbers */
int compare_numbers(int number1, int number2);
/* Limpa o buffer de input */
void clean_stdin_buffer(void);
/* Read a integer from the input */
int read_integer(char *message, int min, int max);
/* Read a float from the input */
float read_float(char *message, float min, float max);
/* Read a string from the input */
void read_string(char *message, char *outputString, unsigned int maxChars);

#endif // ELEMENTS_H_INCLUDED
