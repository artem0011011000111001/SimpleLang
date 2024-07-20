#pragma once

#ifndef _MATH_FUNCTIONS_H_
#define _MATH_FUNCTIONS_H_

#include "Function.h"

namespace Simple {

	ValuePtr Sin(std::vector<ValuePtr> args);

	ValuePtr Cos(std::vector<ValuePtr> args);

	ValuePtr Tan(std::vector<ValuePtr> args);

	ValuePtr Sqrt(std::vector<ValuePtr> args);

	ValuePtr Cbrt(std::vector<ValuePtr> args);

	ValuePtr Round(std::vector<ValuePtr> args);

	ValuePtr Floor(std::vector<ValuePtr> args);
}

#endif // _MATH_FUNCTIONS_H_