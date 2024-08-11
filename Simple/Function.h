#pragma once

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "Simple_typedefs.h"
#include "Simple_Error.h"

#include <vector>

namespace Simple {

	class Function {
	public:
		virtual VALUE execute(Args_t args) = 0;
		virtual FunctionPtr clone() const = 0;

		virtual ~Function() = default;
	};
}
#endif // !_FUNCTION_H_