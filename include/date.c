#include "date.h"
#include "elements.h"
#include <stdbool.h>

/**
 * @brief Check if 'year' is a leap year
 *
 * @param year
 * @return true if 'year' is a leap year
 * @return false if not
 */
bool is_leap_year(uint16_t year) {
	bool result = false;

	if (year % 4 == 0) 	{
		if (year % 100 == 0) {
			if (year % 400 == 0) {
				result = true;
			}
		} else {
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
int validate_date(typeDate date) {
	int result = 1;

	if (date.month != 2) {	// if is not february
		switch (date.month) {
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
	} else {	// if is february
		if (is_leap_year(date.year) == true) {	// if is a leap year
			if (check_range(date.day, 1, 29) == 0) {
				result = 0;
			}
		} else {
			if (check_range(date.day, 1, 28) == 0) {
				result = 0;
			}
		}
	}

	return result;
}
