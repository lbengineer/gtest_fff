#include "funcB.h"

FuncB* funcB;

void funcB_init(void) {
	funcA_test();
	funcB->init();
}

int funcB_recv(S_FUNCA_MSG *msg) {
	return funcB->recv(msg);
}
