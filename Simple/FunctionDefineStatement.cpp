#include "AST.h"
#include "Functions.h"
#include "Simple_defines.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;


std::function<VALUE(Args_t)> FunctionDefineStatement::TurnFuncFromVoidToVALUE(StatementPtr& statement) {
	return [&statement, this](Args_t args) -> VALUE {
		Vars_t savedGlobals;
		try {
			Variables::PushState();
			create_arguments(argsParam, args, savedGlobals);

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

			disassemble_arguments(savedGlobals);
			Variables::PopState();

			return VOID;
		}
		catch (ReturnStatement::ReturnValue& ReturnValue) {
			//ValuePtr result = Return.GetExpression()->eval();

			disassemble_arguments(savedGlobals);

			Variables::PopState();
			return std::move(ReturnValue.value);
		}
		};
}

FunctionDefineStatement::FunctionDefineStatement(String name, ArgsParam_t argsParam, StatementPtr statement)
	: statement(std::move(statement)), name(std::move(name)), argsParam(std::move(argsParam)) {}

void FunctionDefineStatement::execute() {
	Functions::RegisterDynamicFunction(name, TurnFuncFromVoidToVALUE(statement), { argsParam.first.size() });
}