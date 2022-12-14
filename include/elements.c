#include "elements.h"

/**
 * @brief Set location from a integer
 * 
 * @param location 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeLocal
 * @return 0 if 'num' exists in typeLocal
 */
int set_typeLocal(enum typeLocal *location, int num) {
	int result = 0;
	switch (num) {
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
 * @brief Check if 'number' is in range from 'min' to 'max'
 * 
 * @param number 
 * @param min 
 * @param max 
 * @return -1 if 'number' is bellow 'min'
 * @return 0 if in between 'min' and 'max'
 * @return 1 if is above 'max'
 */
int check_range(int number, int min, int max) {
	int result;

	if (min <= number && number <= max) {
		result = 0;
	} else {
		if (number < min) {
			result = -1;
		} else {	// then 'number' only can be above 'max'
			result = 1;
		}
		
	}

	return result;
}