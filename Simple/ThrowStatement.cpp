#include "AST.h"
#include "Variables.h"

using namespace Simple;

ThrowStatement::ThrowStatement(ExpressionPtr expr)
	: expr(std::move(expr)) {}

void ThrowStatement::execute() {
	if (!Variables::StateEmpty())
		Variables::PopState();
	throw expr->eval().clone();
}