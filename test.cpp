#include "macro_utils.h"
#include <iostream>

#define EMPTY_MACRO

int main()
{
	std::cout << "general utils:" << std::endl;
	#define XYZW xyzw
	TEST_CASE_MACRO(EXPAND_AND_CALL(TO_STRING, XYZW), "xyzw");
	std::cout << std::endl;
	
	std::cout << "REMOVE_COMMAS:" << std::endl;
	TEST_CASE_MACRO(REMOVE_COMMAS(), );
	TEST_CASE_MACRO(REMOVE_COMMAS(abc), abc);
	TEST_CASE_MACRO(REMOVE_COMMAS(,), );
	TEST_CASE_MACRO(REMOVE_COMMAS(a,b), a b);
	TEST_CASE_MACRO(REMOVE_COMMAS("a",b, c,5   ,int*,,,8,), "a" b c 5 int* 8);
	std::cout << std::endl;
	
	std::cout << "CHECK_IF_THING:" << std::endl;
	TEST_CASE_MACRO(CHECK_IF_THING(a_thing), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING("abc"), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING("abc", 5, foo), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING(, "abc", 5, foo), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING(,,,,,,,,,,,a,,), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING(), NOTHING);
	TEST_CASE_MACRO(CHECK_IF_THING(EMPTY_MACRO), NOTHING);
	TEST_CASE_MACRO(CHECK_IF_THING(,,,,,,,,,,,,,), NOTHING);
	std::cout << std::endl;
	
	std::cout << "COUNT_THINGS:" << std::endl;
	TEST_CASE_MACRO(COUNT_THINGS(), 0);
	TEST_CASE_MACRO(COUNT_THINGS(a), 1);
	TEST_CASE_MACRO(COUNT_THINGS(a, b), 2);
	TEST_CASE_MACRO(COUNT_THINGS(a, b, c), 3);
	TEST_CASE_MACRO(COUNT_THINGS(EMPTY_MACRO), 0);
	TEST_CASE_MACRO(COUNT_THINGS("abc", 2, fsdafds, ()), 4);
	std::cout << std::endl;
	
	std::cout << "meta tests:" << std::endl;
	TEST_CASE(1 + 2, 3);
	TEST_CASE("foo", "foo");
	TEST_CASE("this is fine", "failure");
	TEST_CASE_MACRO(TO_STRING(abc), "abc");
	std::cout << std::endl;
	
	return 0;
}
