#include "AST.h"
#include "Variables.h"

using namespace Simple;

VariableDefineStatement::VariableDefineStatement(WString name, ExpressionPtr expr, bool IsConst)
	: name(name), expr(std::move(expr)), IsConst(IsConst) {}

void VariableDefineStatement::execute() {
	Variables::Set(name, Variable(expr->eval().clone(), IsConst));
}