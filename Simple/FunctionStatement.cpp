#include "AST.h"

using namespace Simple;

FunctionStatement::FunctionStatement(FunctionalExpression function) : function(std::move(function)) {}

void FunctionStatement::execute() {
	function.eval();
}

std::string FunctionStatement::to_string() {
	return function.to_string();
}