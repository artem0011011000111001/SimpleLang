#pragma once

#ifndef _MATH_FUNCTIONS_H_
#define _MATH_FUNCTIONS_H_

#include "Function.h"

using namespace Simple;

namespace Simple_libs {

	namespace Math {

		VALUE Sin(Args_t args);

		VALUE Cos(Args_t args);

		VALUE Tan(Args_t args);

		VALUE Sqrt(Args_t args);

		VALUE Cbrt(Args_t args);

		VALUE Round(Args_t args);

		VALUE Floor(Args_t args);

		VALUE Log(Args_t args);
	}
}

#endif // _MATH_FUNCTIONS_H_