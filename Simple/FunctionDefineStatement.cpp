#include "AST.h"
#include "Functions.h"
#include "Simple_defines.h"
#include "Variables.h"
#include "Simple_Error.h"
#include "ArgParams.h"

using namespace Simple;

std::function<VALUE(Args_t)> FunctionDefineStatement::TurnFuncFromVoidToVALUE(StatementPtr& statement) {
	return [&statement, this](Args_t args) -> VALUE {
		try {
			Variables::PushState();

			create_arguments(argsParam, args, is_any_args);

			/*auto argNameIt = argsParam.first.begin();
			auto argIsConstIt = argsParam.second.begin();
			for (auto& arg : args) {
				if (Variables::IsExist(*argNameIt)) {
					savedGlobals[*argNameIt] = Variable(Variables::Get(*argNameIt), Variables::IsConstant(*argNameIt));
				}
				Variables::SetNew(*argNameIt, Variable(std::move(arg), *argIsConstIt));
				++argNameIt;
			}*/

			statement->execute();

			disassemble_arguments();
			Variables::PopState();

			return VOID;
		}
		catch (ReturnStatement::ReturnValue& ReturnValue) {
			disassemble_arguments();

			Variables::PopState();
			return MOVE(ReturnValue.value);
		}
		};
}

FunctionDefineStatement::FunctionDefineStatement(WString name, ArgsParams_t argsParam, StatementPtr statement, bool is_any_args)
	: statement(MOVE(statement)), name(MOVE(name)), argsParam(MOVE(argsParam)), is_any_args(is_any_args) {}

void FunctionDefineStatement::execute() {
	Functions::RegisterDynamicFunction(name, Statement_to_func(statement, argsParam, is_any_args), { is_any_args ? any_args : (int)argsParam.size() });
}