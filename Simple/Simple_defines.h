#pragma once

#ifndef _SIMPLE_DEFINES_H_
#define _SIMPLE_DEFINES_H_

#include "Module_defines.h"

#define simple_npos static_cast<size_t>(-1)
#define EOF_TOKEN Token(TokenType::END_OF_FILE, "")
#define MATH_PI 3.14159265358979323846
#define MATH_E 2.71828182845904523536

#define CREATE_PTR std::make_unique
#define NUM_VALUE(val) CREATE_PTR<NumberValue>(val)
#define STR_VALUE(val) CREATE_PTR<StringValue>(val)
#define ZERO NUM_VALUE(0)
#define CHECK_END_STR consume(TokenType::SEMICOLON);

#endif // _SIMPLE_DEFINES_H_
