#include "Utils.h"
#include "Values.h"
#include "Simple_Error.h"
#include "Variable.h"
#include "Variables.h"
#include "Structs.h"
#include "ArgParams.h"
#include "Field_info.h"
#include "FuncParams.h"
#include "Functions.h"
#include "Method_info.h"

using namespace Simple;

Val_map Simple::CreateTypedDefaultValue() {
	Val_map TypedDefaultValue;

	TypedDefaultValue.emplace(L"num",	   CREATE_GET_VALUEPTR(NumberValue, 0));
	TypedDefaultValue.emplace(L"str",	   CREATE_GET_VALUEPTR(StringValue, L""));
	TypedDefaultValue.emplace(L"char",	   CREATE_GET_VALUEPTR(CharValue,   L""));
	TypedDefaultValue.emplace(L"digit",    CREATE_GET_VALUEPTR(DigitValue,  0));
	TypedDefaultValue.emplace(L"void",	   CREATE_GET_VALUEPTR_VOID);
	TypedDefaultValue.emplace(L"arr",	   CREATE_GET_VALUEPTR(ArrayValue,    ArrayValue()));
	TypedDefaultValue.emplace(L"function", CREATE_GET_VALUEPTR(FunctionValue, FuncParams()));
	
	return MOVE(TypedDefaultValue);
}

double Simple::strict_stod(const WString str) {
	double result;
	size_t pos;
	try {
		result = std::stod(str, &pos);
		if (pos != str.length())
			throw 0;
	}
	catch (...) {
		throw Simple_Error(L"\"" + str + L"\" not number");
	}
	return result;
}

String Simple::to_string(LogicOperators op)
{
	switch (op) {

	case LogicOperators::EQUALS:
		return "==";

	case LogicOperators::NOT_EQUALS:
		return "!=";

	case LogicOperators::LT:
		return "<";

	case LogicOperators::LTEQ:
		return "<=";

	case LogicOperators::GT:
		return ">";

	case LogicOperators::GTEQ:
		return ">=";

	case LogicOperators::AND:
		return "&&";

	case LogicOperators::OR:
		return "||";

	default:
		break;
	}
}

String Simple::to_string(BinaryOperators op)
{
	switch (op) {

	case BinaryOperators::PLUS:
		return "+";

	case BinaryOperators::MINUS:
		return "-";

	case BinaryOperators::MULTIPLY:
		return "*";

	case BinaryOperators::DIVIDE:
		return "/";

	case BinaryOperators::POWER:
		return "**";

	default:
		break;
	}
}

WString Simple::IdentifyCategory(ValueType type) {
	switch (type) {

	case Simple::ValueType::_DIGIT_:
		return L"primitive";

	case Simple::ValueType::_NUMBER:
		return L"primitive";

	case Simple::ValueType::_CHAR:
		return L"primitive";

	case Simple::ValueType::_STRING:
		return L"primitive";

	case Simple::ValueType::_STRUCT:
		return L"struct";

	case Simple::ValueType::_VOID:
		return L"primitive";

	default:
		throw Simple_Error("Unknown type");
	}
}

ValueType Simple::IdentifyValueType(const WString& key) {

	if (key == L"num")
		return ValueType::_NUMBER;

	else if (key == L"str")
		return ValueType::_STRING;

	else if (key == L"void")
		return ValueType::_VOID;

	else if (key == L"digit")
		return ValueType::_DIGIT_;

	else if (key == L"char")
		return ValueType::_CHAR;

	else if (key == L"arr")
		return ValueType::_ARRAY;

	else if (Structs::IsExist(key))
		return ValueType::_STRUCT;

	else throw Simple_Error(L"\"" + key + L"\" is unknown type");
}

bool Simple::equals_type(const WString& key1, const WString& key2) {

	ValueType type1 = IdentifyValueType(key1),
	type2 = IdentifyValueType(key2);

	if (type1 == ValueType::_STRUCT && type2 == ValueType::_STRUCT)
		return Structs::_equals(key1, key2);

	return type1 == type2;
}

void Simple::copy_variables(const Vars_t& from, Vars_t& whom) {
	for (const auto& var : from) {
		whom[var.first].value = var.second.value->clone();
	}
}

void Simple::create_arguments(ArgsParams_t& argsParam, Args_t& args, bool is_any_args) {

	Vars_t matches_names;

	auto save_variable = [&matches_names](const WString& key) {
		if (Variables::IsExist(key)) {
			matches_names[key] = Variable(Variables::Get(key), Variables::IsConstant(key));
		}
		};

	if (is_any_args) {

		save_variable(argsParam.front().name);
		ArrayValue arr;
		for (auto& arg : args) {
			arr.AddElement(MOVE(arg));
		}
		Variables::SetNew(argsParam.front().name, Variable(CREATE_PTR<ArrayValue>(MOVE(arr)), argsParam.front().isConst));
	}
	else {
		//auto argParamIt = argsParam.begin();

		for (size_t i = 0; i < args.size(); ++i) {
			auto& arg = args[i];
			auto& argParam = argsParam[i];

			Variable var;
			var.is_const = argParam.isConst;

			if (arg)
				var.value = MOVE(arg);

			else if (argParam.defaultValue)
				var.value = argParam.defaultValue->eval().clone();

			else throw Simple_Error("There is no default value for the function argument");

			save_variable(argParam.name);

			Variables::SetNew(argParam.name, MOVE(var));
		}

		/*for (auto& arg : args) {
			Variable var;
			var.is_const = argParamIt->isConst;

			if (arg)
				var.value = MOVE(arg);

			else if (argParamIt->defaultValue)
				var.value = argParamIt->defaultValue->eval().clone();

			else throw Simple_Error("There is no default value for the function argument");

			save_variable(argParamIt->name);

			Variables::SetNew(argParamIt->name, MOVE(var));
			++argParamIt;
		}*/
	}
	Variables::PushMatches(MOVE(matches_names));	
}

void Simple::disassemble_arguments() {
	Variables::PopMatches();
}

void Simple::check_pos(int pos, int max_pos, const String& designator) {
	if (pos > max_pos)
		throw Simple_Error("Pos greater than " + designator + " size");
	else if (pos < 0)
		throw Simple_Error("Pos cannot be negative");
}

String Simple::uni_to_ascii(const WString& str) {
	String ascii_str;
	for (wchar_t wc : str) {
		if (wc <= 127) {
			ascii_str += static_cast<char>(wc);
		}
	}
	return ascii_str;
}

Fields_decl_t Simple::copy_fields_params(const Fields_decl_t& from) {
	Fields_decl_t copy_fields_params;

	for (auto& field_params : from) {

		ValuePtr copy_value;
		copy_value = field_params.second.value->clone();

		copy_fields_params.emplace(field_params.first,
			FIELD_INFO(field_params.second.type,
				field_params.second.isConst,
				   MOVE(copy_value)));

	}
	return MOVE(copy_fields_params);
}

FunctionPtr Simple::CheckAndGetFunc(const FuncParams& func, int argsCount) {

	auto func_without_any_args = func.func_bodies.find(argsCount);
	auto end = func.func_bodies.end();

	if (func_without_any_args != end)
		return func_without_any_args->second->clone();

	auto func_with_any_args = func.func_bodies.find(any_args);

	if (func_with_any_args != end)
		return func_with_any_args->second->clone();

	return nullptr;
}

Vars_t Simple::to_vars_t(Fields_decl_t& other) {
	Vars_t vars;

	for (auto& field : other) {
		vars.emplace(field.first, field.second.value->clone()); ////
	}
	return MOVE(vars);
}

Args_t Simple::copy_args(Args_t from) {
	Args_t newArgs;

	for (auto& arg : from) {
		newArgs.push_back(MOVE(arg->clone()));
	} return MOVE(newArgs);
}

bool Simple::is_number_value(const ValuePtr& val) {
	return val->GetType() == ValueType::_NUMBER || val->GetType() == ValueType::_DIGIT_ || val->GetType() == ValueType::_PERCENT;
}

bool Simple::is_char_value(const ValuePtr& val) {
	return val->GetType() == ValueType::_STRING || val->GetType() == ValueType::_CHAR;
}

WString Simple::multiply_str(const WString& str, const int count) {
	WString result;
	for (size_t i = 0; i < count; i++) {
		result += str;
	}
	return result;
}

Vars_t Simple::copy_vars(const Vars_t& vars) {
	Vars_t copy;

	for (auto& var : vars) {
		copy.emplace(var.first, Variable(var.second.clone_value(), var.second.is_const));
	}
	return MOVE(copy);
}

Methods_t Simple::copy_methods(const Methods_t& methods) {
	Methods_t copy;

	for (auto& method : methods) {
		copy.emplace(method.first, method.second.clone());
	}
	return MOVE(copy);
}

Args_t Simple::exprs_to_args(Vec<ExpressionPtr> exprs) {
	Args_t args;
	args.reserve(exprs.size());

	for (const auto& arg : exprs) {
		ValuePtr argValue;
		if (arg)
			argValue = arg->eval().clone();
		else argValue = DEFAULT;

		args.push_back(MOVE(argValue));
	}
	return MOVE(args);
}

void Simple::CreateDefaultFieldsValues(Fields_t& fields, Fields_decl_t& fields_params) {

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
}

Fields_decl_t Simple::RawToMade(RawFields_decl_t& raw) {
	Fields_decl_t transform;

	for (auto& Rawfield_params : raw) {
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
}

ClassFields_decl_t Simple::RawToMade(RawClassFields_decl_t& raw) {
	ClassFields_decl_t transform;

	for (auto& Rawfield_params : raw) {
		ValuePtr defaultValue = NOT_VALUE;

		if (Rawfield_params.second.first.defaultValue)
			defaultValue = Rawfield_params.second.first.defaultValue->eval().clone();
		
		transform.emplace(Rawfield_params.first, MK_PAIR(FIELD_INFO(

			Rawfield_params.second.first.type,
			Rawfield_params.second.first.isConst,
			MOVE(defaultValue)
		
		), Rawfield_params.second.second));
	}

	return MOVE(transform);
}

//Methods_t Simple::RawToMade(RawMethod_decl_t raw, StatementPtr add_statement) {
//	Methods_t transform;
//
//	for (auto& RawMethod_params : raw) {
//
//		auto& raw_method = RawMethod_params.second.first;
//
//		transform.emplace(RawMethod_params.first, Statement_to_func(
//
//			raw_method.body,
//			raw_method.args_params,
//			raw_method.is_any_args));
//
//	}
//
//	return MOVE(transform);
//}

std::function<VALUE(Args_t)> Simple::Statement_to_func(StatementPtr& statement, ArgsParams_t& argsParam, bool is_any_args) {
	return [&statement, &argsParam, is_any_args](Args_t args) -> VALUE {
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

std::function<VALUE(Args_t)> Simple::Statement_to_struct_constructor(StatementPtr& statement, ArgsParams_t& argsParam, bool is_any_args, Fields_decl_t& fields_params, const WString& name) {
	return [&statement, &argsParam, is_any_args, &fields_params, &name](Args_t args) -> VALUE {
		try {
			Variables::PushState();

			create_arguments(argsParam, args, is_any_args);

			Fields_t fields;

			CreateDefaultFieldsValues(fields, fields_params);

			/*Val_map TypedDefaultValue = CreateTypedDefaultValue();

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
			}*/

			Variables::SetNew(L"this", Variable(STRUCT(name, fields), false));

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

std::function<VALUE(Args_t)> Simple::Statement_to_class_constructor(StatementPtr& statement, ArgsParams_t& argsParam, bool is_any_args, Fields_decl_t& fields_params, RawMethod_decl_t& methods_params, const WString& name) {
	return [&statement, &argsParam, is_any_args, &fields_params, &name, &methods_params](Args_t args) -> VALUE {
		try {
			Variables::PushState();

			create_arguments(argsParam, args, is_any_args);

			Fields_t fields;

			CreateDefaultFieldsValues(fields, fields_params);

			Variables::SetNew(L"this", Variable(CLASS(name, fields, methods_params), false));

			if (statement)
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

Fields_decl_t Simple::_DECL_FIELDS(std::initializer_list<PAIR<WString, Field_info>> fields_args) {
	Fields_decl_t fields;

	for (auto& field_arg : fields_args) {
		fields.emplace(field_arg.first, field_arg.second.clone());
	}

	return MOVE(fields);
}