#include "AST.h"
#include "Functions.h"
#include "Simple_defines.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;


std::function<ValuePtr(std::vector<ValuePtr>)> FunctionDefineStatement::TurnFuncFromVoidToValuePtr(StatementPtr& statement) {
	return [&statement, this](std::vector<ValuePtr> args) -> ValuePtr {
		std::unordered_map<std::string, Variable> savedGlobals;
		try {
			Variables::PushState();

			/*for (auto& arg : args) {
				Variables::Set(*argIt, std::move(arg));
				++argIt;
			}*/
			auto argNameIt = argsParam.first.begin();
			auto argIsConstIt = argsParam.second.begin();
			for (auto& arg : args) {
				if (Variables::IsExist(*argNameIt)) {
					savedGlobals[*argNameIt] = Variable(Variables::Get(*argNameIt), Variables::IsConstant(*argNameIt));
				}
				Variables::Set(*argNameIt, Variable(std::move(arg), *argIsConstIt));
				++argNameIt;
			}

			statement->execute();

			for (const auto& var : savedGlobals) {
				Variables::SetNew(var.first, Variable(var.second.value->clone(), var.second.is_const));
			}

			Variables::PopState();
			return ZERO;
		}
		catch (ValuePtr& ReturnValue) {
			//ValuePtr result = Return.GetExpression()->eval();

			for (const auto& var : savedGlobals) {
				Variables::SetNew(var.first, Variable(var.second.value->clone(), var.second.is_const));
			}

			Variables::PopState();
			return std::move(ReturnValue);
		}
		};
}

FunctionDefineStatement::FunctionDefineStatement(std::string name, std::pair<std::list<std::string>, std::list<bool>> argsParam, StatementPtr statement)
	: statement(std::move(statement)), name(std::move(name)), argsParam(std::move(argsParam)) {}

void FunctionDefineStatement::execute() {
	Functions::RegisterDynamicFunction(name, TurnFuncFromVoidToValuePtr(statement), { argsParam.first.size() });
}

std::string FunctionDefineStatement::to_string() {
	return "function " + name + "(" + [this](){
		std::string res;

		for (const auto& name : argsParam.first)
		{
			res += name + ", ";
		}
		return res;
		}() + ")" + statement->to_string();
}