#include "AST.h"
#include "Simple_defines.h"

using namespace Simple;

AbbreviatedOperationsStatement::AbbreviatedOperationsStatement(ExpressionPtr expr1, BinaryOperators operation, ExpressionPtr expr2)
	: expr1(std::move(expr1)), operation(operation), expr2(std::move(expr2)) {}

void AbbreviatedOperationsStatement::execute() {
	Value& ref = expr1->eval();
	ValuePtr result = BinaryExpression(std::move(expr1), operation, std::move(expr2)).eval().clone();
	ref.set_ref(result);
}