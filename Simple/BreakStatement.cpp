#include "AST.h"

using namespace Simple;

void BreakStatement::execute() {
	throw *this;
}