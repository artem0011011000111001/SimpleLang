#include "Expressions.h"
#include "Variables.h"
#include "Simple_Error.h"

#include <iostream>

using namespace Simple;

FieldExpression::FieldExpression(ExpressionPtr expr, WString field_name)
	: expr(std::move(expr)), field_name(field_name) {}

Value& FieldExpression::eval() {
   return expr->eval().dot(field_name);
}