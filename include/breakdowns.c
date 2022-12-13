#include "breakdowns.h"

/**
 * @brief Set type of breakdown from a integer
 * 
 * @param breakdown_type 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeBreak
 * @return 0 if 'num' exists in typeBreak
 */
int set_typeBreak(enum typeBreak *breakdown_type, int num) {
	int result = 0;
	switch (num) {
	case TEMPORARY:
		*breakdown_type = TEMPORARY;
		break;
	case PERMANENT:
		*breakdown_type = PERMANENT;
		break;
	default:
		result = -1;
		break;
	}

	return result;
}