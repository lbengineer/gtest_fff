#ifndef FUNCB_IF
#define FUNCB_IF

#include <funcA_if.h>

#define FUNCB_OK 0
#define FUNCB_NG -1

#ifdef __cplusplus
extern "C" {
#endif

void funcB_init(void);
int funcB_recv(S_FUNCA_MSG *msg);

#ifdef __cplusplus
};
#endif

#endif
