#include "AST.h"
#include "Simple_typedefs.h"
#include "Simple_Error.h"
#include "Functions.h"
#include "Variables.h"
#include "Structs.h"
#include "ArgParams.h"
#include "Field_decl.h"
#include "Function.h"
#include "Utils.h"

#include <algorithm>
#include <iterator>

using namespace Simple;

std::function<VALUE(Args_t)> ConstructorDefineStatement::TurnFuncFromVoidToVALUE(StatementPtr& statement) {
	return [&statement, this](Args_t args) -> VALUE {
		Vars_t savedGlobals;
		try {
			Variables::PushState();
			create_arguments(argsParam, args, savedGlobals, is_any_args);

			Vars_t fields;

			Val_map TypedDefaultValue = CreateTypedDefaultValue();

			for (auto& fields_param : fields_params) {
				fields.emplace(fields_param.first, [&fields_param, &TypedDefaultValue]() -> Field {

					WString type = fields_param.second.type;

					ValuePtr defaultValue;
					ValuePtr finalValue;
					
					if (fields_param.second.defaultValue)
						defaultValue = fields_param.second.defaultValue->clone();

					bool isConst = fields_param.second.isConst;

					if (defaultValue) {
						if (type == defaultValue->GetTypeInString())
							finalValue = MOVE(defaultValue);

						else throw Simple_Error("Invalid type");
					}

					else if (Structs::IsExist(type))
						finalValue = CALL(type, Args_t());

					else if (TypedDefaultValue.find(type) != TypedDefaultValue.end())
						finalValue = TypedDefaultValue[type]->clone();

					else throw Simple_Error(type + L" - undeclared type");

					return Field(MOVE(finalValue), isConst);
					}());
			}

			Variables::SetNew(L"this", Variable(STRUCT(name, fields), false));
			
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

			ValuePtr value_this = Variables::Get(L"this");

			disassemble_arguments(savedGlobals);
			Variables::PopState();

			return MOVE(value_this);
		}
		catch (ReturnStatement&) {
			throw Simple_Error("Constructor cannot return a value");
		}
		};
}

ConstructorDefineStatement::ConstructorDefineStatement(WString name,
	ArgsParams_t argsParam, StatementPtr statement, RawFields_decl_t RawFields_params, bool is_any_args)
	: name(name), argsParam(MOVE(argsParam)), statement(MOVE(statement)), RawFields_params(MOVE(RawFields_params)), is_any_args(is_any_args) {
}

void ConstructorDefineStatement::execute() {
	fields_params = [this]() {

		Fields_decl_t transform;

		for (auto& Rawfield_params : RawFields_params) {
			ValuePtr defaultValue;

			if (Rawfield_params.second.defaultValue)
				defaultValue = Rawfield_params.second.defaultValue->eval().clone();

			transform.emplace(Rawfield_params.first, FIELD(

				Rawfield_params.second.type,
				Rawfield_params.second.isConst,
				MOVE(defaultValue))

			);
		}

		return MOVE(transform);
		}();

	Structs::Add(name, copy_fields_params(fields_params));

	Functions::RegisterDynamicFunction(name, TurnFuncFromVoidToVALUE(statement), { is_any_args ? any_args : (int)argsParam.size() });
}