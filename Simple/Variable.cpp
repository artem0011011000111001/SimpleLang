#include "Variable.h"

using namespace Simple;

Variable::Variable(ValuePtr value, bool is_const)
	: value(value->clone()), is_const(is_const) {}

ValuePtr Variable::clone_value() const {
	return value->clone();
}