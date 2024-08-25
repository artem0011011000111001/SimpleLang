#include "AST.h"
#include "Simple_typedefs.h"
#include "Simple_Error.h"
#include "Functions.h"
#include "Variables.h"
#include "Structs.h"
#include "ArgParams.h"
#include "Field_info.h"
#include "Function.h"
#include "Utils.h"

#include <algorithm>
#include <iterator>

using namespace Simple;

std::function<VALUE(Args_t)> StructDefineStatement::TurnFuncFromVoidToVALUE(StatementPtr& statement, ArgsParams_t& argsParam, bool is_any_args_) {
	return [&statement, &argsParam, &is_any_args_, this](Args_t args) -> VALUE {
		try {
			Variables::PushState();

			create_arguments(argsParam, args, is_any_args_);

			Vars_t fields;

			Val_map TypedDefaultValue = CreateTypedDefaultValue();

			for (auto& fields_param : fields_params) {
				fields.emplace(fields_param.first, [&fields_param, &TypedDefaultValue]() -> Field {

					WString type = fields_param.second.type;

					ValuePtr defaultValue;
					ValuePtr finalValue;
					
					if (!dynamic_cast<nullptrValue*>(fields_param.second.value.get())) {
						defaultValue = fields_param.second.value->clone();
					}

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

			disassemble_arguments();
			Variables::PopState();

			return MOVE(value_this);
		}
		catch (ReturnStatement&) {
			throw Simple_Error("Constructor cannot return a value");
		}
		};
}

StructDefineStatement::StructDefineStatement(WString name, Vec<ArgsParams_t> argsParam,
	Vec<StatementPtr> statements, RawFields_decl_t RawFields_params, Vec<bool> is_any_args)
	: name(name), argsParam(MOVE(argsParam)), statements(MOVE(statements)), RawFields_params(MOVE(RawFields_params)), is_any_args(is_any_args) {
}

void StructDefineStatement::execute() {
	fields_params = [this]() {

		Fields_decl_t transform;

		for (auto& Rawfield_params : RawFields_params) {
			ValuePtr defaultValue = NOT_VALUE;

			if (Rawfield_params.second.defaultValue)
				defaultValue = Rawfield_params.second.defaultValue->eval().clone();

			transform.emplace(Rawfield_params.first, FIELD_INFO(

				Rawfield_params.second.type,
				Rawfield_params.second.isConst,
				MOVE(defaultValue))

			);
		}

		return MOVE(transform);
		}();

	Structs::Add(name, copy_fields_params(fields_params));

	auto is_any_args_it = is_any_args.begin();
	auto args_param_it  = argsParam.begin();

	for (auto& statement : statements) {
		bool _is_any_args_ = *is_any_args_it;
		Functions::RegisterDynamicFunction(name, Statement_to_struct_constructor(statement, *args_param_it, _is_any_args_, fields_params, name),
			{ _is_any_args_ ? any_args : (int)args_param_it->size() });
		++is_any_args_it;
		++args_param_it;
	}
}