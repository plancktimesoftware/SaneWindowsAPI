#pragma once

#define INTERNAL_CAT(_1, _2) _1##_2

#define INTERNAL_IF_1(_Then, _Else) _Then
#define INTERNAL_IF_0(_Then, _Else) _Else

#define IS_ZERO_INTERNAL_0 1
#define IS_ZERO_INTERNAL_1 0
#define IS_ZERO_INTERNAL_2 0
#define IS_ZERO_INTERNAL_3 0
#define IS_ZERO_INTERNAL_4 0
#define IS_ZERO_INTERNAL_5 0
#define IS_ZERO_INTERNAL_6 0
#define IS_ZERO_INTERNAL_7 0
#define IS_ZERO_INTERNAL_8 0
#define IS_ZERO_INTERNAL_9 0
#define IS_ZERO_INTERNAL_10 0
#define IS_ZERO_INTERNAL_11 0
#define IS_ZERO_INTERNAL_12 0
#define IS_ZERO_INTERNAL_13 0
#define IS_ZERO_INTERNAL_14 0
#define IS_ZERO_INTERNAL_15 0
#define IS_ZERO_INTERNAL_16 0

#define INTERNAL_TUPLE_FIRST(first, ...) first
#define INTERNAL_TUPLE_REMOVE_FIRST(first, ...) __VA_ARGS__

#define INTERNAL_ITERATE_TUPLE_2(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_REMOVE_FIRST tuple, _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_3(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_2(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4) \

#define INTERNAL_ITERATE_TUPLE_4(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_3(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_5(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_4(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_6(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_5(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_7(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_6(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_8(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_7(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_9(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_8(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_10(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_9(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_11(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_10(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_12(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_11(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_13(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_12(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_14(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_13(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_15(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_14(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

#define INTERNAL_ITERATE_TUPLE_16(Macro, tuple, _1, _2, _3, _4) \
	CALL_MACRO(Macro, INTERNAL_TUPLE_FIRST tuple, _1, _2, _3, _4) \
	INTERNAL_ITERATE_TUPLE_17(Macro, (INTERNAL_TUPLE_REMOVE_FIRST tuple), _1, _2, _3, _4)

