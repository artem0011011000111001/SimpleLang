#include "AST.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;

AssigmentStatement::AssigmentStatement(ExpressionPtr expr, ExpressionPtr expression)
	: expr1(std::move(expr)), expr2(std::move(expression)) {}

void AssigmentStatement::execute() {
	ValuePtr result = expr2->eval().clone();
	expr1->eval().set_ref(result);
}