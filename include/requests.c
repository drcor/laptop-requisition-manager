#include "requests.h"

/**
 * @brief Set type of user from a integer
 * 
 * @param user_type 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeUser
 * @return 0 if not
 */
int set_typeUser(enum typeUser *user_type, int num) {
	int result = 0;
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
		result = -1;
		break;
	}

	return result;
}

/**
 * @brief Set type of requisition state from a number
 * 
 * @param req_state 
 * @param num 
 * @return -1 if 'num' doesn't exist in typeReqState
 * @return 0 if not
 */
int set_typeReqState(enum typeReqState *req_state, int num) {
	int result = 0;
	switch (num) {
	case ACTIVE:
		*req_state = ACTIVE;
		break;
	case DONE:
		*req_state = DONE;
		break;	
	default:
		result = -1;
		break;
	}

	return result;
}
