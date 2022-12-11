#include "elements.h"

/**
 * @brief Set type of cpu from a integer
 * 
 * @param cpu 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeCPU, 0 if does
 */
int set_typeCPU(enum typeCPU *cpu, int num) {
	int ret = 0;
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
		ret = -1;
		break;
	}

	return ret;
}

/**
 * @brief Set the state of laptop from a integer
 * 
 * @param state 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeState, 0 if does
 */
int set_typeState(enum typeState *state, int num) {
	int ret = 0;
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
		ret = -1;
		break;
	}

	return ret;
}

/**
 * @brief Set location from a integer
 * 
 * @param location 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeLocal, 0 if does
 */
int set_typeLocal(enum typeLocal *location, int num) {
	int ret = 0;
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
		ret = -1;
		break;
	}

	return ret;
}

/**
 * @brief Set type of breakdown from a integer
 * 
 * @param breakdown_type 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeBreak, 0 if does
 */
int set_typeBreak(enum typeBreak *breakdown_type, int num) {
	int ret = 0;
	switch (num) {
	case TEMPORARY:
		*breakdown_type = TEMPORARY;
		break;
	case PERMANENT:
		*breakdown_type = PERMANENT;
		break;
	default:
		ret = -1;
		break;
	}

	return ret;
}

/**
 * @brief Set type of user from a integer
 * 
 * @param user_type 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeUser, 0 if does 
 */
int set_typeUser(enum typeUser *user_type, int num) {
	int ret = 0;
	switch (num) {
	case STUDENT:
		*user_type = STUDENT;
		break;
	case TEACHER:
		*user_type = TEACHER;
		break;
	case ADMNISTRATIVE:
		*user_type = ADMNISTRATIVE;
		break;
	default:
		ret = -1;
		break;
	}

	return ret;
}

/**
 * @brief Set type of requisition state from a number
 * 
 * @param req_state 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeUser, 0 if does 
 */
int set_typeReqState(enum typeReqState *req_state, int num) {
	int ret = 0;
	switch (num) {
	case ACTIVE:
		*req_state = ACTIVE;
		break;
	case DONE:
		*req_state = DONE;
		break;	
	default:
		ret = -1;
		break;
	}

	return ret;
}
