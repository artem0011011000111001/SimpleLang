#include "AST.h"
#include "Simple_typedefs.h"
#include "Simple_Error.h"
#include "Functions.h"
#include "Variables.h"
#include "Structs.h"

#include <algorithm>
#include <iterator>

using namespace Simple;

std::function<VALUE(Args_t)> Simple::ConstructorDefineStatement::TurnFuncFromVoidToVALUE(StatementPtr& statement) {
	return [&statement, this](Args_t args) -> VALUE {
		Vars_t savedGlobals;
		try {
			Variables::PushState();
			create_arguments(argsParam, args, savedGlobals);

			Val_map fields;

			for (auto& fields_param : fields_params) {
				fields.emplace(fields_param.first, [fields_param]() -> ValuePtr {

					if (fields_param.second == ValueType::_NUMBER)
						return NUMBER(0);

					else if (fields_param.second == ValueType::_STRING)
						return STRING("");

					else if (fields_param.second == ValueType::_DIGIT_)
						return DIGIT(0);

					else if (fields_param.second == ValueType::_CHAR)
						return CHAR("");

					else if (fields_param.second == ValueType::_VOID)
						return VOID;

					else throw Simple_Error("Unknown type");
					}());
			}

			Variables::SetNew("this", Variable(STRUCT(name, fields), false));
			
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

			ValuePtr value_this = Variables::Get("this");

			disassemble_arguments(savedGlobals);
			Variables::PopState();

			return std::move(value_this);
		}
		catch (ReturnStatement&) {
			throw Simple_Error("Constructor cannot return a value");
		}
		};
}

ConstructorDefineStatement::ConstructorDefineStatement(String name,
	ArgsParam_t argsParam, StatementPtr statement, Fields_decl_t fields_params)
	: name(name), argsParam(std::move(argsParam)), statement(std::move(statement)), fields_params(fields_params) {
	Structs::Add(name, fields_params);
}

void ConstructorDefineStatement::execute() {
	Functions::RegisterDynamicFunction(name, TurnFuncFromVoidToVALUE(statement), { argsParam.first.size() });
}