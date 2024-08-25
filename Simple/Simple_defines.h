#pragma once

#ifndef _SIMPLE_DEFINES_H_
#define _SIMPLE_DEFINES_H_

#include "Module_defines.h"

#define simple_npos static_cast<size_t>(-1)
#define any_args -1
#define not_specified_args -2
#define EOF_TOKEN Token(TokenType::END_OF_FILE, L"")
//#define MATH_PI  3.14159265358979323846
//#define MATH_E   2.71828182845904523536

#define MATH_PI  3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706
#define MATH_PHI 1.61803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113
#define MATH_E   2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642

#define CREATE_PTR std::make_unique
#define NUMBER	 CREATE_PTR<NumberValue>
#define DIGIT	 CREATE_PTR<DigitValue>
#define PERCENT	 CREATE_PTR<PercentValue>
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
#define CLASS(name, fields, methods) CREATE_PTR<ClassValue>(name, MOVE(fields), MOVE(methods))
#define BOOL	  NUMBER
#define ZERO	  NUMBER(0)
#define EMPTY_STR STRING(L"")
#define TRUE	  NUMBER(1)
#define FALSE	  ZERO
#define DEFAULT		   CREATE_PTR<nullptrValue>()
#define NOT_VALUE	   CREATE_PTR<nullptrValue>()
#define EXPR_DEFAULT   nullptr
#define EXPR_NOT_VALUE nullptr
#define PAIR      std::pair
#define MK_PAIR   std::make_pair

#define UNDEF_DEFINES \
#undef NUMBER		  \
#undef DIGIT		  \
#undef CHAR			  \
#undef STRING		  \
#undef BOOL			  \
#undef VOID			  \
#undef ARRAY		  \
#undef FUNCTION		  \
#undef STRUCT		  \
#undef ZERO			  \
#undef DEFAULT		  \
#undef NOT_VALUE      \
#undef PAIR           \
#undef MK_PAIR		  \
#undef TRUE			  \
#undef FALSE		  \

#define CHECK_END_STR consume(TokenType::SEMICOLON);

#endif // _SIMPLE_DEFINES_H_
