#include "Expressions.h"
#include "Variables.h"

using namespace Simple;

IndexExpression::IndexExpression(ExpressionPtr expr, ExpressionPtr pos)
	: expr(std::move(expr)), pos(std::move(pos)) {}

//ValuePtr IndexExpression::eval() {
//	return get_ref().clone();
//}

Value& IndexExpression::eval() {
	return expr->eval().operator[](static_cast<int>(pos->eval().AsDouble()));
}
