#pragma once

#ifndef _SIMPLE_DEFINES_H_
#define _SIMPLE_DEFINES_H_

#include "Module_defines.h"

#define simple_npos static_cast<size_t>(-1)
#define any_args -1
#define not_specified_args -2
#define EOF_TOKEN Token(TokenType::END_OF_FILE, L"")
#define MATH_PI 3.14159265358979323846
#define MATH_E 2.71828182845904523536

#define CREATE_PTR std::make_unique
#define NUMBER	 CREATE_PTR<NumberValue>
#define DIGIT	 CREATE_PTR<DigitValue>
#define STRING	 CREATE_PTR<StringValue>
#define CHAR	 CREATE_PTR<CharValue>
#define ARRAY	 CREATE_PTR<ArrayValue>
#define VOID	 CREATE_PTR<VoidValue>()
#define FUNCTION CREATE_PTR<FunctionValue>

#define CREATE_GET_VALUEPTR(type, value) \
		[&]() -> ValuePtr { return CREATE_PTR<type>(MOVE(value)); }()

#define CREATE_GET_VALUEPTR_VOID		 \
		[]() -> ValuePtr { return CREATE_PTR<VoidValue>(); }()

#define STRUCT(name, fields) CREATE_PTR<StructValue>(name, MOVE(fields))
#define BOOL	  NUMBER
#define ZERO	  NUMBER(0)
#define EMPTY_STR STRING("")
#define TRUE	  NUMBER(1)
#define FALSE	  NUMBER(0)
#define DEFAULT   nullptr
#define NOT_VALUE nullptr
#define PAIR      std::pair
#define MK_PAIR   std::make_pair

#define CHECK_END_STR consume(TokenType::SEMICOLON);

#endif // _SIMPLE_DEFINES_H_
