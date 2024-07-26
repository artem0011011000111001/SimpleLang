#include "Expressions.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;

StructExpression::StructExpression(ExpressionPtr expr, std::string field_name)
	: expr(std::move(expr)), field_name(field_name) {}

//ValuePtr StructExpression::eval() {
//	if (is_request)
//		return expr->eval()->dot(field_name)->operator[](index);
//	return expr->eval()->dot(field_name);
//}

Value& StructExpression::eval() {
	/*if (is_request)
		ref = expr->eval().dot(field_name)->operator[](index);*/
	ref = expr->eval().dot(field_name);

	return *ref;
}

//void StructExpression::SetIndex(const int index) {
//	this->index = index;
//	is_request = true;
//}