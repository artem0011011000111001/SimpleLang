#pragma once

#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include "Values.h"
#include "Simple_typedefs.h"

namespace Simple {

	struct Variable {
		ValuePtr value;
		bool is_const;
		Variable() : value(nullptr), is_const(false) {}
		Variable(ValuePtr value, bool is_const = false);
		ValuePtr clone_value() const;
	};
}
#endif // _VARIABLE_H_
