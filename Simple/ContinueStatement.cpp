#include "AST.h"

using namespace Simple;

void ContinueStatement::execute() {
	throw *this;
}

std::string ContinueStatement::to_string() {
	return "continue;";
}