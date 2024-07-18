#include "AST.h"
#include "Functions.h"
#include "Simple_defines.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;


std::function<ValuePtr(std::vector<ValuePtr>)> FunctionDefineStatement::TurnFuncFromVoidToValuePtr(StatementPtr& statement) {
	return [&statement, this](std::vector<ValuePtr> args) -> ValuePtr {
		std::unordered_map<std::string, ValuePtr> savedGlobals;
		try {
			Variables::PushState();

			/*for (auto& arg : args) {
				Variables::Set(*argIt, std::move(arg));
				++argIt;
			}*/
			auto argIt = argsNames.begin();
			for (auto& arg : args) {
				if (Variables::IsExist(*argIt)) {
					savedGlobals[*argIt] = Variables::Get(*argIt);
				}
				Variables::Set(*argIt, std::move(arg));
				++argIt;
			}

			statement->execute();

			for (const auto& pair : savedGlobals) {
				Variables::Set(pair.first, pair.second->clone());
			}


			Variables::PopState();
			return ZERO;
		}
		catch (ValuePtr& ReturnValue) {
			//ValuePtr result = Return.GetExpression()->eval();

			for (const auto& pair : savedGlobals) {
				Variables::Set(pair.first, pair.second->clone());
			}


			Variables::PopState();
			return std::move(ReturnValue);
		}
		};
}

FunctionDefineStatement::FunctionDefineStatement(std::string name, std::list<std::string> argsNames, StatementPtr statement)
	: statement(std::move(statement)), name(std::move(name)), argsNames(std::move(argsNames)) {}

void FunctionDefineStatement::execute() {
	Functions::RegisterDynamicFunction(name, TurnFuncFromVoidToValuePtr(statement), { argsNames.size() });
}

std::string FunctionDefineStatement::to_string() {
	return "function " + name + "(" + [this](){
		std::string res;

		for (const auto& name : argsNames)
		{
			res += name + ", ";
		}
		return res;
		}() + ")" + statement->to_string();
}