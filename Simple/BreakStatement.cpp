#include "AST.h"

using namespace Simple;

void BreakStatement::execute() {
	throw *this;
}

std::string BreakStatement::to_string() {
	return "break;";
}