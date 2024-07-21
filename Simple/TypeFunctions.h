#pragma once

#ifndef _TYPE_FUNCTIONS_H_
#define _TYPE_FUNCTIONS_H_

#include "Function.h"

using namespace Simple;

namespace Simple_libs {

	namespace Type {

		VALUE Cast_number(Args_t args);

		VALUE Cast_string(Args_t args);

		VALUE Typeof(Args_t args);

		VALUE Is_const(Args_t args);
	}
}

#endif // _CAST_FUNCTIONS_H_