#pragma once

#ifndef _TYPE_FUNCTIONS_H_
#define _TYPE_FUNCTIONS_H_

#include "Simple.h"
#include "Function.h"

namespace Simple {

	ValuePtr Cast_number(std::vector<ValuePtr> args);
	
	ValuePtr Cast_string(std::vector<ValuePtr> args);

	ValuePtr Typeof(std::vector<ValuePtr> args);

	ValuePtr IsConst(std::vector<ValuePtr> args);
}

#endif // !_CAST_FUNCTIONS_H_