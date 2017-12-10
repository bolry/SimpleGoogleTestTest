#include <cstring>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct X {
	virtual ~X() {}
	virtual void foo() const;
	virtual void foo(int) const;
	virtual void foo(char const*) const;
	virtual void foo();
	virtual void foo(int);
	virtual void foo(char const*);
	virtual int bar() const;
	virtual int bar(int) const;
	virtual int bar(char const*) const;
	virtual int bar();
	virtual int bar(int);
	virtual int bar(char const*);
};

void X::foo() const {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
}
void X::foo(int) const {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
}
void X::foo(char const*) const {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
}
void X::foo() {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
}
void X::foo(int) {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
}
void X::foo(char const*) {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
}
int X::bar() const {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
	return 0;
}
int X::bar(int val) const {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
	return ++val;
}
int X::bar(char const* str) const {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
	return std::strlen(str);
}
int X::bar() {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
	return 0;
}
int X::bar(int val) {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
	return ++val;
}
int X::bar(char const* str) {
	std::cout << "This is " << __PRETTY_FUNCTION__ << '\n';
	return std::strlen(str);
}

void TakesConstXAndUsesFoo(const X& x, int times) {
	for (int i = 0; i != times; ++i) {
		x.foo();
	}
}

void TakesConstXAndUsesFoo(const X& x, int times, int val) {
	for (int i = 0; i != times; ++i) {
		x.foo(val);
	}
}

void TakesConstXAndUsesFoo(const X& x, int times, char const* str) {
	for (int i = 0; i != times; ++i) {
		x.foo(str);
	}
}

void TakesXAndUsesFoo(X& x, int times) {
	for (int i = 0; i != times; ++i) {
		x.foo();
	}
}

void TakesXAndUsesFoo(X& x, int times, int val) {
	for (int i = 0; i != times; ++i) {
		x.foo(val);
	}
}

void TakesXAndUsesFoo(X& x, int times, char const* str) {
	for (int i = 0; i != times; ++i) {
		x.foo(str);
	}
}

void TakesConstXAndUsesBar(const X& x, int times) {
	for (int i = 0; i != times; ++i) {
		x.bar();
	}
}

void TakesConstXAndUsesBar(const X& x, int times, int val) {
	for (int i = 0; i != times; ++i) {
		x.bar(val);
	}
}

void TakesConstXAndUsesBar(const X& x, int times, char const* str) {
	for (int i = 0; i != times; ++i) {
		(void) x.bar(str);
	}
}

void TakesXAndUsesBar(X& x, int times) {
	for (int i = 0; i != times; ++i) {
		x.bar();
	}
}

void TakesXAndUsesBar(X& x, int times, int val) {
	for (int i = 0; i != times; ++i) {
		x.bar(val);
	}
}

void TakesXAndUsesBar(X& x, int times, char const* str) {
	for (int i = 0; i != times; ++i) {
		x.bar(str);
	}
}

struct MockX: X {
	MOCK_CONST_METHOD0(foo, void());
	MOCK_CONST_METHOD1(foo, void(int));
	MOCK_CONST_METHOD1(foo, void(char const*));
	MOCK_METHOD0(foo, void());
	MOCK_METHOD1(foo, void(int));
	MOCK_METHOD1(foo, void(char const*));

	MOCK_CONST_METHOD0(bar, int());
	MOCK_CONST_METHOD1(bar, int(int));
	MOCK_CONST_METHOD1(bar, int(char const*));
	MOCK_METHOD0(bar, int());
	MOCK_METHOD1(bar, int(int));
	MOCK_METHOD1(bar, int(char const*));
};

using ::testing::_;
using ::testing::A;
using ::testing::AllOf;
using ::testing::An;
using ::testing::Const;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Lt;
using ::testing::Matcher;
using ::testing::Matches;
using ::testing::Ne;
using ::testing::Return;
using ::testing::TypedEq;

TEST(TestX,UsingConstMockXFooWithVoid) {
	const MockX k_x;
	EXPECT_CALL(k_x, foo()).Times(3);
	TakesConstXAndUsesFoo(k_x, 3);
}

TEST(TestX,UsingConstMockXFooWithInt) {
	const MockX k_x;
	EXPECT_CALL(k_x, foo(5)).Times(3);
	TakesConstXAndUsesFoo(k_x, 3, 5);
}

TEST(TestX,UsingConstMockXFooWithEmptyStr) {
	const MockX k_x;
	EXPECT_CALL(k_x, foo("")).Times(3);
	TakesConstXAndUsesFoo(k_x, 3, "");
}

TEST(TestX,UsingNonConstMockXFooWithVoid) {
	MockX x;
	EXPECT_CALL(Const(x), foo()).Times(3);
	TakesConstXAndUsesFoo(x, 3);
}

TEST(TestX,UsingNonConstMockXFooWithInt) {
	MockX x;
	EXPECT_CALL(Const(x), foo(5)).Times(3);
	TakesConstXAndUsesFoo(x, 3, 5);
}

TEST(TestX,UsingNonConstMockXFooWithEmptyStr) {
	MockX x;
	EXPECT_CALL(Const(x), foo("")).Times(3);
	TakesConstXAndUsesFoo(x, 3, "");
}

TEST(TestX,UsingMockXFooWithVoid) {
	MockX x;
	EXPECT_CALL(x, foo()).Times(3);
	TakesXAndUsesFoo(x, 3);
}

TEST(TestX,UsingMockXFooWithInt) {
	MockX x;
	EXPECT_CALL(x, foo(5)).Times(3);
	TakesXAndUsesFoo(x, 3, 5);
}

TEST(TestX, UsingMockXFooWithIntUsingMatcherInstead) {
	MockX x;
	EXPECT_CALL(x, foo(Matcher<int>(Lt(6)))).Times(2);
	TakesXAndUsesFoo(x, 2, 5);
}

TEST(TestX, UsingMockXFooWithIntUsingTypedEq) {
	MockX x;
	EXPECT_CALL(x, foo(TypedEq<int>(8))).Times(4);
	TakesXAndUsesFoo(x, 4, 8);
}

TEST(TestX,UsingMockXFooWithEmptyStr) {
	MockX x;
	EXPECT_CALL(x, foo("")).Times(3);
	TakesXAndUsesFoo(x, 3, "");
}

TEST(TestX,UsingMockXFooWithAnyStr) {
	MockX x;
	EXPECT_CALL(x,foo(A<char const*>())).Times(2);
	TakesXAndUsesFoo(x, 2, "any string");
}

TEST(TestX,UsingMockXFooWithAnyInt) {
	MockX x;
	EXPECT_CALL(x,foo(An<int>())).Times(2);
	TakesXAndUsesFoo(x, 2, 7);
}

TEST(TestX,UsingMockXFooWithIntInRange) {
	MockX x;
	Matcher<int> inThisRange = AllOf(Ge(0), Lt(100), Ne(50));
	EXPECT_CALL(x,foo(inThisRange)).Times(2);
	TakesXAndUsesFoo(x, 2, 7);
}

//int main(int argc, char** argv) {
//  testing::InitGoogleMock(&argc, argv);
//  return RUN_ALL_TESTS();
//}
