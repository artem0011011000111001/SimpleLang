#pragma once

#ifndef _RAW_VARIABLE_H_
#define _RAW_VARIABLE_H_

#include "Expressions.h"
#include "Simple_typedefs.h"
#include "Simple_defines.h"

namespace Simple {

	struct RawVariable {
		ExpressionPtr value;
		bool isConst;

		RawVariable(ExpressionPtr value, bool isConst = false);
	};
}

#endif // !_RAW_VARIABLE_H_