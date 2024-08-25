#pragma once

#ifndef _ARG_PARAMS_H_
#define _ARG_PARAMS_H_

#include "Simple_typedefs.h"
#include "Simple_defines.h"

namespace Simple {

	struct ArgParams {

		WString name;
		bool isConst = false;
		ExpressionPtr defaultValue;

		ArgParams(WString name, bool isConst = false, ExpressionPtr defaultValue = EXPR_NOT_VALUE);
		ArgParams() = default;
	};

}

#endif // _ARG_PARAMS_H_