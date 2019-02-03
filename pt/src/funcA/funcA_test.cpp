#include <string.h>
#include "../fff.h"
DEFINE_FFF_GLOBALS;
#include "gmock/gmock.h"

extern "C" {
/* 標準関数を置き換え */
#define printf my_printf
int my_printf(const char*, ...);

#include "funcA.c"
}

FAKE_VALUE_FUNC_VARARG(int, my_printf, const char*, ...)
FAKE_VOID_FUNC(funcB_init)
FAKE_VALUE_FUNC(int, funcB_recv, S_FUNCA_MSG *)

#define RESET_FFF \
RESET_FAKE(my_printf); \
RESET_FAKE(funcB_init); \
RESET_FAKE(funcB_recv); \
FFF_RESET_HISTORY();

class funcA_test : public ::testing::Test {
	void setup() {
		RESET_FFF;
	}
};

TEST_F(funcA_test, Test1) {
	int ret = funcA_send(NULL);
	/* 試験対象関数の戻り値をチェック */
	EXPECT_EQ(ret, FUNCA_NG);
}

/* 可変引数のチェック */
int Test2_my_printf(const char *format, va_list ap) {
	switch (my_printf_fake.call_count) {
		/* 1回目の呼び出し */
		case 1:
			EXPECT_EQ(strcmp(format, "[funcA] send. id=%d\n"), 0);
			EXPECT_EQ(va_arg(ap, int), 10);
			break;
	}
	
	return my_printf_fake.return_val;
}
TEST_F(funcA_test, Test2) {
	S_FUNCA_MSG msg;
	msg.id = 10;
	
	/* 外部関数の戻り値指定 */
	funcB_recv_fake.return_val = FUNCB_OK;
	
	my_printf_fake.custom_fake = Test2_my_printf;
	
	int ret = funcA_send(&msg);
	
	EXPECT_EQ(ret, FUNCA_OK);
	EXPECT_EQ(my_printf_fake.call_count, 1);
	
	/* 外部関数の呼び出しチェック */
	EXPECT_EQ(funcB_init_fake.call_count, 1);
	EXPECT_EQ(funcB_recv_fake.call_count, 1);
	
	/* 外部関数の引数チェック */
	EXPECT_EQ(funcB_recv_fake.arg0_val, VALUE_A);
}

