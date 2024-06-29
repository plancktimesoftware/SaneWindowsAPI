
#pragma once

#include "InternalMacros.h"


#define CAT(_1, _2) INTERNAL_CAT(_1, _2)

#define IF(_Cond, _Then, _Else) CAT(INTERNAL_IF_, _Cond)(_Then, _Else)

#define IS_ZERO(num) CAT(IS_ZERO_INTERNAL_, num)

/**
 * Expands to the number of items in the input tuple.
 * Supports tuples with 1-16 values.
 */
#define NUM(tuple) INTERNAL_NUM tuple

#define APPEND_IF_NOT_ZERO(str, index) \
	IF(IS_ZERO(index), str, str##index)

#define CALL_MACRO(Macro, index, _1, _2, _3, _4) Macro(index, _1, _2, _3, _4)

#define ITERATE_MACRO_FOR_TUPLE(Macro, tuple, tupleSize, _1, _2, _3, _4) \
	CAT(INTERNAL_ITERATE_TUPLE_, tupleSize)(Macro, tuple, _1, _2, _3, _4)

#define REVERSE_ITERATE_MACRO_FOR_TUPLE(Macro, tuple, tupleSize, _1, _2, _3, _4) \
	CAT(INTERNAL_REVERSE_ITERATE_TUPLE_, tupleSize)(Macro, tuple, _1, _2, _3, _4)

#define DECLARE_VARIABLE(index, type, name, defValue, _unused) \
	APPEND_IF_NOT_ZERO(type, index) name##V##index = defValue;

#define DECLARE_VERSIONED_VARIABLES(versions, numVersions, type, name, defValue) \
	ITERATE_MACRO_FOR_TUPLE(DECLARE_VARIABLE, versions, numVersions, type, name, defValue, )

#define DECLARE_POINTER_VARIABLE(index, type, name, defValue, _unused) \
	APPEND_IF_NOT_ZERO(type, index)* name##V##index = defValue;

#define DECLARE_VERSIONED_POINTER_VARIABLES(versions, numVersions, type, name, defValue) \
	ITERATE_MACRO_FOR_TUPLE(DECLARE_POINTER_VARIABLE, versions, numVersions, type, name, defValue, )

#define INITIALIZE_VARIABLE(index, name, value, _unused1, _unused2) \
	, name##V##index{ value##V##index }

#define INITIALIZE_VERSIONED_VARIABLES(versions, numVersions, name, value) \
	ITERATE_MACRO_FOR_TUPLE(INITIALIZE_VARIABLE, versions, numVersions, name, value, , )

#define ASSIGN_TO_VARIABLE(index, name, value, _unused1, _unused2) \
	name##V##index = value;

#define ASSIGN_TO_VERSIONED_VARIABLES(versions, numVersions, name, value) \
	ITERATE_MACRO_FOR_TUPLE(ASSIGN_TO_VARIABLE, versions, numVersions, name, value, , )

#define ASSIGN_TO_VARIABLE_2(index, name, value, _unused1, _unused2) \
	name##V##index = value##V##index;

#define ASSIGN_TO_VERSIONED_VARIABLES_2(versions, numVersions, name, value) \
	ITERATE_MACRO_FOR_TUPLE(ASSIGN_TO_VARIABLE_2, versions, numVersions, name, value, , )

#define ADDREF_TO_VARIABLE(index, name, _unused1, _unused2, _unused3) \
	if (name##V##index) name##V##index->AddRef();

#define ADDREF_TO_VERSIONED_VARIABLES(versions, numVersions, name) \
	ITERATE_MACRO_FOR_TUPLE(ADDREF_TO_VARIABLE, versions, numVersions, name, , , )

#define RELEASE_VARIABLE(index, name, _unused1, _unused2, _unused3) \
	if (name##V##index) { name##V##index->Release(); name##V##index = nullptr; }

#define RELEASE_VERSIONED_VARIABLES(versions, numVersions, name) \
	ITERATE_MACRO_FOR_TUPLE(RELEASE_VARIABLE, versions, numVersions, name, , , )

#define RELEASE_VARIABLE_IF_DIFFERENT(index, name, other, _unused1, _unused2) \
	if (name##V##index && name##V##index != other##V##index) { \
		name##V##index->Release(); name##V##index = nullptr; \
	}

#define RELEASE_VERSIONED_VARIABLES_IF_DIFFERENT(versions, numVersions, name, other) \
	ITERATE_MACRO_FOR_TUPLE(RELEASE_VARIABLE_IF_DIFFERENT, versions, numVersions, name, other, , )

#define QUERY_INTERFACE_OR_RETURN(index, name, sourceVar, failureReturn, _unused) \
	hres = sourceVar->QueryInterface(&name##V##index); \
	if (hres != S_OK) return failureReturn;

#define QUERY_INTERFACE_VERSIONED_VARIABLES(versions, numVersions, name, sourceVar, failureReturn) \
	ITERATE_MACRO_FOR_TUPLE(QUERY_INTERFACE_OR_RETURN, versions, numVersions, name, sourceVar, failureReturn, )


#define TEMPLATED_GETNATIVE(index, type, name, _unused1, _unused2) \
	template<> \
	auto GetNative<APPEND_IF_NOT_ZERO(type, index)>() const -> APPEND_IF_NOT_ZERO(type, index)* \
	{ return name##V##index; }


#define GETNATIVE_VERSIONED_VARIABLES(versions, numVersions, type, name) \
	template<typename T> \
	auto GetNative() const -> T* { return nullptr; } \
	ITERATE_MACRO_FOR_TUPLE(TEMPLATED_GETNATIVE, versions, numVersions, type, name, , )

