#include "AST.h"
#include "Simple_defines.h"

using namespace Simple;

AbbreviatedOperationsStatement::AbbreviatedOperationsStatement(ExpressionPtr expr1, BinaryOperators operation, ExpressionPtr expr2)
	: expr1(std::move(expr1)), operation(operation), expr2(std::move(expr2)) {}

void AbbreviatedOperationsStatement::execute() {
	if (operation == BinaryOperators::PLUS)
		expr1->eval() += expr2->eval().clone();

	else if (operation == BinaryOperators::MINUS)
		expr1->eval() -= expr2->eval().clone();

	else if (operation == BinaryOperators::MULTIPLY)
		expr1->eval() *= expr2->eval().clone();

	else if (operation == BinaryOperators::DIVIDE)
		expr1->eval() /= expr2->eval().clone();

	else if (operation == BinaryOperators::POWER)
		expr1->eval().powereq(expr2->eval().clone());
}