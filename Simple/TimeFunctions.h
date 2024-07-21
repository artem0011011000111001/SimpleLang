#pragma once

#ifndef _TIME_FUNCTIONS_H_
#define _TIME_FUNCTIONS_H_

#include "Function.h"

using namespace Simple;

namespace Simple_libs {

	namespace Time {

		VALUE Now(Args_t args);

		VALUE Sleep(Args_t args);
	}
}

#endif // _TIME_FUNCTIONS_H_