#include "date.h"
#include "generic.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Check if 'year' is a leap year
 *
 * @param year
 * @return true if 'year' is a leap year
 * @return false if not
 */
bool is_leap_year(uint16_t year)
{
    bool result = false;

    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                result = true;
            }
        }
        else
        {
            result = true;
        }
    }

    return result;
}

/**
 * @brief Check if date format is correct and valid
 *
 * @param date
 * @return 0 if date is valid
 * @return 1 if day is invalid
 * @return 2 if month is invalid
 */
int validate_date(typeDate date)
{
    int result = 1;

    if (date.year > BEGIN_DATE)
    {
        if (date.month != 2)  	// if is not february
        {
            switch (date.month)
            {
            // If month have 31 days
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                // result will be 0 if day is in the range, 1 if not
                result = check_range(date.day, 1, 31) == 0 ? 0 : 1;
                break;
            // If month have 30 days
            case 4:
            case 6:
            case 9:
            case 11:
                // result will be 0 if day is in the range, 1 if not
                result = check_range(date.day, 1, 30) == 0 ? 0 : 1;
                break;
            default:
                result = 2;	// month is invalid
                break;
            }
        }
        else  	// if is february
        {
            if (is_leap_year(date.year) == true)  	// if is a leap year
            {
                if (check_range(date.day, 1, 29) == 0)
                {
                    result = 0;
                }
            }
            else
            {
                if (check_range(date.day, 1, 28) == 0)
                {
                    result = 0;
                }
            }
        }
    }

    return result;
}

/**
 * @brief Print date in text format
 *
 * @param date
 */
void print_date(typeDate date)
{
    if (validate_date(date) == 0)
    {
        printf("%02d/%02d/%04d", date.day, date.month, date.year);
    }
    else
    {
        printf("--/--/----");
    }
}

/**
 * @brief Read date from input
 *
 * @param message
 * @param date
 */
void read_date(char *message, typeDate *date)
{
    int control;

    // Get date
    do
    {
        printf("%s superior a (01/01/2000): ", message);
        control = scanf("%hhu/%hhu/%hu", &(date->day), &(date->month), &(date->year));
        clean_stdin_buffer();

        // Validate the input for the date number
        if (control == 0 || validate_date(*date) != 0)
        {
            printf("\nATENCAO: Devera inserir uma data valida no formato dia/mes/ano\n");
        }
    }
    while (control == 0 || validate_date(*date) != 0);
}

/**
 * @brief Compare two typeDates
 *
 * @param date1
 * @param date2
 * @return -1 date1 > date2
 * @return 0 date1 = date2
 * @return 1 date1 < date2
 */
int compare_date(typeDate date1, typeDate date2)
{
    int result = 0;

    result = compare_numbers((int)date1.year, (int)date2.year);
    if (result == 0)  	// if years are equal, check months
    {
        result = compare_numbers((int)date1.month, (int)date2.month);
        if (result == 0)  	// if months are equal, check days
        {
            result = compare_numbers((int)date1.day, (int)date2.day);
        }
    }

    return result;
}

/**
 * @brief Calculate total number of days since 2020
 *
 * @param date
 * @return int
 */
int count_days(typeDate date)
{
    int total = 0;
    uint16_t year;
    uint8_t month;

    // Add days in years
    for (year = BEGIN_DATE; year < date.year; year++)
    {
        if (is_leap_year(year))
        {
            total += 366;
        }
        else
        {
            total += 365;
        }
    }

    // Add days in months
    for (month = 1; month < date.month; month++)
    {
        switch (month)
        {
        // If month have 31 days
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            // add 31 days
            total += 31;
            break;
        // If month have 30 days
        case 4:
        case 6:
        case 9:
        case 11:
            // add 30 days
            total += 30;
            break;
        case 2:
            total += is_leap_year(date.year) ? 29 : 28;	// february
            break;
        default:
            break;
        }
    }

    // Add days in last month
    total += date.day;

    return total;
}

/**
 * @brief Calculate number of days between two dates
 *
 * @param date1
 * @param date2
 * @return int
 */
int diff_date(typeDate date1, typeDate date2)
{
    int result, total1 = 0, total2 = 0;

    total1 = count_days(date1);
    total2 = count_days(date2);

    if (compare_date(date1, date2) == 1)
    {
        result = total2 - total1;
    }
    else
    {
        result = total1 - total2;
    }

    return result;
}
