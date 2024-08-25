#include "Expressions.h"

using namespace Simple;

TernaryExpression::TernaryExpression(ExpressionPtr condition, ExpressionPtr expr1, ExpressionPtr expr2)
	: condition(MOVE(condition)), expr1(MOVE(expr1)), expr2(MOVE(expr2)) {}

Value& TernaryExpression::eval() {
	if (condition->eval().AsDouble()) return expr1->eval();
	else return expr2->eval();
}