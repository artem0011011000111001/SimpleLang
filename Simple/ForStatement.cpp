#include "AST.h"
#include "Variables.h"

using namespace Simple;

ForStatement::ForStatement(std::string InitName, StatementPtr initialization, ExpressionPtr termination,
	ExpressionPtr increment, StatementPtr block)
	: InitName(InitName), initialization(std::move(initialization)), 
	termination(std::move(termination)), increment(std::move(increment)), statement(std::move(block)) {}

void ForStatement::execute() {

	Variables::PushState();
	Variable SaveGlobalMatchWithInitNameValue;

	if (Variables::IsExist(InitName)) {
		SaveGlobalMatchWithInitNameValue = Variable(Variables::Get(InitName), Variables::IsConstant(InitName));
	}

	for (initialization->execute();
		termination->eval().AsDouble() != 0;
		increment->eval()) {
		try {
			statement->execute();
		}
		catch (const BreakStatement&) {
			break;
		}
		catch (const ContinueStatement&) {
			//continue;
		}
	}
	if (SaveGlobalMatchWithInitNameValue.value)
		Variables::Set(InitName, std::move(SaveGlobalMatchWithInitNameValue));
	Variables::PopState();
}