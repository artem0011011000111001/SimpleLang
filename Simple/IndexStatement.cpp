#include "AST.h"

using namespace Simple;

IndexStatement::IndexStatement(ExpressionPtr appeal_to_index)
	: appeal_to_index(std::move(appeal_to_index)) {}

void IndexStatement::execute() {
	appeal_to_index->eval(); //////////////////////////////////
}

std::string IndexStatement::to_string() {
	return appeal_to_index->to_string(); //////////////////////////////////
}