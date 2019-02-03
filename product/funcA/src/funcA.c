#include "funcA.h"

int funcA_send(S_FUNCA_MSG *msg) {
	if (msg == NULL) {
		return FUNCA_NG;
	}
	printf("[funcA] send. id=%d\n", msg->id);
	msg->value = VALUE_A;
	
	funcB_init();
	if (funcB_recv(msg->value) != FUNCB_OK) {
		return FUNCA_NG;
	}
	return FUNCA_OK;
}
