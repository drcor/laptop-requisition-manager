#include "elements.h"

/**
 * @brief Set location from a integer
 * 
 * @param location 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeLocal
 * @return 0 if not
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
