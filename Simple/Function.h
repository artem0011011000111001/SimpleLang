#pragma once

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "Values.h"
#include "Simple_typedefs.h"
#include "Simple_Error.h"

#include <vector>

namespace Simple {

	class Function {
	public:
		virtual ValuePtr execute(std::vector<ValuePtr> args) = 0;
		virtual FunctionPtr clone() const = 0;

		virtual ~Function() = default;
	};
}
#endif // !_FUNCTION_H_