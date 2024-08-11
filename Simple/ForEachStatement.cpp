#include "AST.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;

ForEachStatement::ForEachStatement(WString name, bool isConst, WString in, StatementPtr block)
	: name(name), isConst(isConst), in(in), block(MOVE(block)) {}

void ForEachStatement::execute() {
	Value& arr = Variables::GetRef(in);

	Variables::PushState();
	for (Simple_Iterator it = arr.begin(); it != arr.end(); ++it) {
		Variables::Set(name, Variable((*it)->clone(), isConst));
		block->execute();
		*it = MOVE(Variables::Get(name));
	}
	Variables::PopState();
}