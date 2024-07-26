#include "AST.h"

using namespace Simple;

void ContinueStatement::execute() {
	throw *this;
}