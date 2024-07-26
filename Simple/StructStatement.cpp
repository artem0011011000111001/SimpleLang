#include "AST.h"

using namespace Simple;

StructStatement::StructStatement(ExpressionPtr _struct)
	: _struct(std::move(_struct)) {}

void StructStatement::execute() {
	_struct->eval();
}

std::string StructStatement::to_string() {
	return _struct->to_string();
}