#include "AST.h"

using namespace Simple;

ReturnStatement::ReturnStatement(ExpressionPtr expr) : expr(std::move(expr)) {}

void ReturnStatement::execute() {
	throw ReturnValue(expr->eval().clone());
}

const ExpressionPtr& ReturnStatement::GetExpression() const {
	return expr;
}

ReturnStatement::ReturnValue::ReturnValue(ValuePtr value) 
	: value(std::move(value)) {}