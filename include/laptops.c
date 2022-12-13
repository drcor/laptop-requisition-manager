#include "laptops.h"

/**
 * @brief Set type of cpu from a integer
 * 
 * @param cpu 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeCPU
 * @return 0 if 'num' exists in typeCPU
 */
int set_typeCPU(enum typeCPU *cpu, int num) {
	int result = 0;
	switch (num) {
	case I3:
		*cpu = I3;
		break;
	case I5:
		*cpu = I5;
		break;
	case I7:
		*cpu = I7;
		break;
	default:
		result = -1;
		break;
	}

	return result;
}

/**
 * @brief Set the state of laptop from a integer
 * 
 * @param state 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeState
 * @return 0 if 'num' exists in typeState
 */
int set_typeState(enum typeState *state, int num) {
	int result = 0;
	switch (num) {
	case BROKEN:
		*state = BROKEN;
		break;
	case AVAILABLE:
		*state = AVAILABLE;
		break;
	case TAKEN:
		*state = TAKEN;
		break;
	default:
		result = -1;
		break;
	}

	return result;
}
