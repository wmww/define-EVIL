#ifndef EVIL
#define EVIL

// macros auto-generated from autogen.sh
// should all be prefixed with _AG_
#include "autogen.h"

/// General Utils

// convert input to string literal, can be used with EXPAND_CALL
// depends on: none
#define TO_STRING(a) #a

// expands the arguments and concatenates them
// depends on: none
#define EXPAND_CAT(a, b) _EXPAND_CAT(a, b)
#define _EXPAND_CAT(a, b) a##b

// expands the arguments and then call macro with the expanded arguments
// depends on: none
#define EXPAND_CALL(macro, ...) macro(__VA_ARGS__)

// even I'm not completely sure why this is needed, but it is.
#define EXPAND(a) a

// removes commas in a list of arguments, leaves a space between each one
// depends on: _AG_REMOVE_COMMAS_...
#define REMOVE_COMMAS(...) _AG_REMOVE_COMMAS_0(__VA_ARGS__)

// CHECK_IF_THING(one_or_more, args)	-> A_THING
// CHECK_IF_THING()						-> NOTHING
// a common way to use is to make two macros (ex. EXAMPLE_A_THING and EXAMPLE_NOTHING) and concat your prefix with the
// result of this macro, so you can do different things depending on the thingyness
// depends on: EXPAND_CALL, EXPAND_CAT, EXPAND
// I realize how much of a clusterfuck this is. If you can make it cleaner without failing any tests, plz submit PR
#define CHECK_IF_THING(...) _CHECK_IF_THING_A(EXPAND_CAT(_, EXPAND(_CHECK_IF_THING_D REMOVE_COMMAS(__VA_ARGS__))))
#define _CHECK_IF_THING_A(a) EXPAND_CALL(_CHECK_IF_THING_C, _CHECK_IF_THING_B a (), A_THING)
#define _CHECK_IF_THING_B() dummy, NOTHING
#define _CHECK_IF_THING_C(a, b, ...) b
#define _CHECK_IF_THING_D(...) dummy
#define __CHECK_IF_THING_D

// checks if the argument(s) are completely surrounded by parenthesis
// CHECK_FOR_PEREN() -> NO_PEREN
// CHECK_FOR_PEREN("a") -> NO_PEREN
// CHECK_FOR_PEREN((), 6, "a") -> NO_PEREN
// CHECK_FOR_PEREN(()) -> HAS_PEREN
// CHECK_FOR_PEREN((a, 6, "a")) -> HAS_PEREN
// depends on: EXPAND_CAT, CHECK_IF_THING
#define CHECK_FOR_PEREN(...) EXPAND_CAT(_PEREN_, CHECK_IF_THING(_CHECK_FOR_PEREN_A __VA_ARGS__))
#define _CHECK_FOR_PEREN_A(...)
#define _PEREN_A_THING NO_PEREN
#define _PEREN_NOTHING HAS_PEREN

// expands to the number of arguments; empty arguments are counted; zero arguments is handeled correctly
// depends on: EXPAND_CAT, EXPAND_CALL, CHECK_IF_THING, _AG_COUNT_THINGS, _AG_COUNT_THINGS_NUMBERS
#define COUNT_THINGS(...) EXPAND_CAT(_COUNT_THINGS_, CHECK_IF_THING(__VA_ARGS__))(__VA_ARGS__)
#define _COUNT_THINGS_NOTHING(...) 0
#define _COUNT_THINGS_A_THING(...) EXPAND_CALL(_AG_COUNT_THINGS, __VA_ARGS__, _AG_COUNT_THINGS_NUMBERS)

// applies the given macro to all additional arguments
// macro should accept item and index
// MAP_DOWN: indexes count down to 0 instead of up from 0
// MAP_REVERSE: items are in reverse order
// MAP_REVERSE_DOWN: both
// depends on: EXPAND_CAT, COUNT_THINGS, INC_.. (auto generated), DEC_.. (auto generated)
#define MAP(macro, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(macro, _MAP_FWD, 0, INC_, __VA_ARGS__)
#define MAP_DOWN(macro, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(macro, _MAP_FWD, EXPAND_CAT(DEC_, COUNT_THINGS(__VA_ARGS__)), DEC_, __VA_ARGS__)
#define MAP_REVERSE(macro, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(macro, _MAP_BKWD, EXPAND_CAT(DEC_, COUNT_THINGS(__VA_ARGS__)), DEC_, __VA_ARGS__)
#define MAP_REVERSE_DOWN(macro, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(macro, _MAP_BKWD, 0, INC_, __VA_ARGS__)
#define _MAP_FWD(a, b) a b
#define _MAP_BKWD(a, b) b a

// Tests

// tests if the input expression matches the expected value and prints result
// depends on:  none
#define TEST_CASE(expr, expected) _TEST_CASE_A(#expr, expr, expected)

// like TEST_CASE, but for when you are testing a macro expression
// depends on:  EXPAND_CALL, TO_STRING
#define TEST_CASE_MACRO(macro_expr, expected) _TEST_CASE_A(#macro_expr, EXPAND_CALL(TO_STRING, macro_expr), #expected)

#define _TEST_CASE_A(expr_str, result, expected) { \
	const bool success = (result == expected); \
	std::cout << (success ? " .  " : " X  ") << expr_str << ": " << result; \
	if (!success) { \
		std::cout << " (" << expected << " expected)"; \
	} \
	std::cout << std::endl; \
}

#endif // EVIL
