#include <string.h>
#include "../fff.h"
DEFINE_FFF_GLOBALS;
#include "gmock/gmock.h"

#include "funcB_wrap.cpp"

FAKE_VOID_FUNC(funcA_test)

#define RESET_FFF \
RESET_FAKE(funcA_test); \
FFF_RESET_HISTORY();

class FuncBMock : public FuncB {
public:
	MOCK_METHOD0(init, void());
	MOCK_METHOD1(recv, int(S_FUNCA_MSG *msg));
};
FuncBMock *mock;


void FuncB::init(void) {mock->init();}
int FuncB::recv(S_FUNCA_MSG *msg) {return mock->recv(msg);}

class funcB_wrap_test : public ::testing::Test {
	virtual void SetUp() {
		RESET_FFF;
		mock = new FuncBMock();
	}
	
	virtual void TearDown() {
		delete mock;
	}
};


TEST_F(funcB_wrap_test, Test1) {
	/* クラスメソッドの呼び出しチェック */
	EXPECT_CALL(*mock, init()).Times(1);
	
	funcB = new FuncB();
	funcB_init();
	
	/* C++からCの呼び出しチェック */
	EXPECT_EQ(funcA_test_fake.call_count, 1);
}

TEST_F(funcB_wrap_test, Test2) {
	EXPECT_CALL(*mock, recv(::testing::Field(&S_FUNCA_MSG::id, ::testing::Eq(55))))
		.Times(1)
		/* クラスメソッドの戻り値指定 */
		.WillOnce(::testing::Return(11));
	
	S_FUNCA_MSG msg;
	msg.id = 55;
	funcB = new FuncB();
	int ret = funcB_recv(&msg);
	
	/* C++からCの呼び出しチェック */
	EXPECT_EQ(ret, 11);
}
