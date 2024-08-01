#include "AST.h"

using namespace Simple;

ThrowStatement::ThrowStatement(ExpressionPtr expr)
	: expr(std::move(expr)) {}

void ThrowStatement::execute() {
	throw expr->eval().clone();
}