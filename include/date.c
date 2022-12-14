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
