#pragma once

#ifndef _SIMPLE_DEFINES_H_
#define _SIMPLE_DEFINES_H_

#include "Module_defines.h"

#define simple_npos static_cast<size_t>(-1)
#define EOF_TOKEN Token(TokenType::END_OF_FILE, "")
#define MATH_PI 3.14159265358979323846
#define MATH_E 2.71828182845904523536
#define ZERO std::make_unique<NumberValue>(0)
#define CHECK_END_STR consume(TokenType::SEMICOLON);
#define _FLASH_FUNCTION(type) (std::make_unique<decltype(type)>())
#define _FLASH_VAR(type, val) (std::make_unique<decltype(type)>(val))
#define CREATE_PTR std::make_unique

#endif // !_SIMPLE_DEFINES_H_
