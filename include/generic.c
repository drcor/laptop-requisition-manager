#include "generic.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Set location from a integer
 *
 * @param location
 * @param num
 * @return -1 if 'num' doesn't exist in typeLocal
 * @return 0 if 'num' exists in typeLocal
 */
int set_typeLocal(enum typeLocal *location, int num)
{
    int result = 0;
    switch (num)
    {
    case NONE:
        *location = NONE;
        break;
    case RESIDENCES:
        *location = RESIDENCES;
        break;
    case CAMPUS1:
        *location = CAMPUS1;
        break;
    case CAMPUS2:
        *location = CAMPUS2;
        break;
    case CAMPUS5:
        *location = CAMPUS5;
        break;
    default:
        result = -1;
        break;
    }

    return result;
}

/**
 * @brief Print locations
 *
 * @param location
 */
void print_typeLocal(enum typeLocal location)
{
    switch (location)
    {
    case NONE:
        printf("---        ");
        break;
    case RESIDENCES:
        printf("Residencias");
        break;
    case CAMPUS1:
        printf("Campus 1   ");
        break;
    case CAMPUS2:
        printf("Campus 2   ");
        break;
    case CAMPUS5:
        printf("Campus 5   ");
        break;
    }
}

/**
 * @brief Check if 'number' is in range from 'min' to 'max'
 *
 * @param number
 * @param min
 * @param max
 * @return -1 if 'number' is bellow 'min'
 * @return 0 if in between 'min' and 'max'
 * @return 1 if is above 'max'
 */
int check_range(int number, int min, int max)
{
    int result;

    if (min <= number && number <= max)
    {
        result = 0;
    }
    else
    {
        if (number < min)
        {
            result = -1;
        }
        else  	// then 'number' only can be above 'max'
        {
            result = 1;
        }

    }

    return result;
}

/**
 * @brief Compare two numbers
 *
 * @param number1
 * @param number2
 * @return -1 number1 > number2
 * @return 0 number1 = number2
 * @return 1 number1 < number2
 */
int compare_numbers(int number1, int number2)
{
    int result = 0;
    if (number1 > number2)
    {
        result = -1;
    }
    else
    {
        if (number1 < number2)
        {
            result = 1;
        }
    }

    return result;
}

/**
 * @brief Limpa o buffer de input
 */
void clean_stdin_buffer(void)
{
    char chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}

/**
 * @brief Read a integer from the input
 *
 * @param message
 * @param min
 * @param max
 * @return int
 */
int read_integer(char *message, int min, int max)
{
    int number, control;

    // Get integer number
    do
    {
        printf("%s (%d a %d) : ", message, min, max);
        control = scanf("%d", &number);
        clean_stdin_buffer();

        // Validate the input for a integer number
        if (control == 0)
        {
            printf("\nATENCAO: Devera inserir um numero inteiro\n");
        }
        else
        {
            if (number < min || number > max)
            {
                printf("\nATENCAO: Numero invalido. Insira novamente: ");
            }
        }
    }
    while (number < min || max < number || control == 0);

    return number;
}

/**
 * @brief Read a float from the input
 *
 * @param message
 * @param min
 * @param max
 * @return float
 */
float read_float(char *message, float min, float max)
{
    float number;
    int control;

    // Get float number
    do
    {
        printf("%s (%.2f a %.2f) : ", message, min, max);
        control = scanf("%f", &number);
        clean_stdin_buffer();

        // Validate the input for a float number
        if (control == 0)
        {
            printf("\nATENCAO: Devera inserir um numero decimal (float)\n");
        }
        else
        {
            if (number < min || max < number)
            {
                printf("\nATENCAO: Numero invalido. Insira novamente: ");
            }
        }
    }
    while (number < min || max < number || control == 0);

    return number;
}

/**
 * @brief Read a string from the input
 *
 * @param message
 * @param outputString
 * @param maxChars
 */
void read_string(char *message, char *outputString, unsigned int maxChars)
{
    int stringSize;

    do
    {
        printf("%s: ", message);
        fgets(outputString, maxChars, stdin);

        stringSize = strlen(outputString);

        if (stringSize == 1)  	// Check if the user inserted a string
        {
            printf("\nATENCAO: Nao foram introduzidos caracteres! Apenas carregou no ENTER\n\n");
        }
    }
    while (stringSize == 1);

    // Clean the stdin buffer only if there are chars left
    if (outputString[stringSize - 1] != '\n')
    {
        clean_stdin_buffer();
    }
    else
    {
        outputString[stringSize - 1] = '\0';	// Deletes the \n stored in the vector
    }
}
