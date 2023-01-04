#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

#include <stdint.h>

/* Enumeration of locations */
enum typeLocal {
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

/* Limpa o buffer de input */
void limparBufferStdin(void);

/* Read a integer from the input */
int lerInteiro(char *message, int min, int max);

/* Read a float from the input */
float lerFloat(char *message, float min, float max);

/* Read a string from the input */
void lerString(char *message, char *outputString, unsigned int maxChars);

#endif // ELEMENTS_H_INCLUDED
