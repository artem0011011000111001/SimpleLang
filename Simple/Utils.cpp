#include "Utils.h"
#include "Values.h"
#include "Simple_Error.h"
#include "Variable.h"
#include "Variables.h"
#include "Structs.h"
#include "ArgParams.h"
#include "Field_decl.h"
#include "FuncParams.h"

using namespace Simple;

Val_map Simple::CreateTypedDefaultValue() {
	Val_map TypedDefaultValue;

	TypedDefaultValue.emplace(L"num",	   CREATE_GET_VALUEPTR(NumberValue, 0));
	TypedDefaultValue.emplace(L"str",	   CREATE_GET_VALUEPTR(StringValue, L""));
	TypedDefaultValue.emplace(L"char",	   CREATE_GET_VALUEPTR(CharValue,   L""));
	TypedDefaultValue.emplace(L"digit",    CREATE_GET_VALUEPTR(DigitValue,  0));
	TypedDefaultValue.emplace(L"void",	   CREATE_GET_VALUEPTR_VOID);
	TypedDefaultValue.emplace(L"arr",	   CREATE_GET_VALUEPTR(ArrayValue,    HAND_OVER_ARGS({})));
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
	switch (op)
	{
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

void Simple::create_arguments(ArgsParams_t& argsParam, Args_t& args, Vars_t& whom, bool is_any_args) {

	auto save_variable = [&whom](const WString& key) {
			if (Variables::IsExist(key)) {
				whom[key] = Variable(Variables::Get(key), Variables::IsConstant(key));
			}
		};

	if (is_any_args) {

		save_variable(argsParam.front().name);
		ArrayValue arr;
		for (auto& arg : args) {
			arr.AddElement(MOVE(arg));
		}
		Variables::SetNew(argsParam.front().name, Variable(CREATE_PTR<ArrayValue>(MOVE(arr)), argsParam.front().isConst));
		return;
	}

	auto argParamIt = argsParam.begin();

	for (auto& arg : args) {
		Variable var;
		var.is_const = argParamIt->isConst;

		if (arg)
			var.value = MOVE(arg);

		else if (argParamIt->defaultValue)
			var.value = argParamIt->defaultValue->eval().clone();

		else throw Simple_Error("There is no default value for the function argument");

		save_variable(argParamIt->name);
		/*if (Variables::IsExist(argParamIt->name)) {
			whom[argParamIt->name] = Variable(Variables::Get(argParamIt->name), Variables::IsConstant(argParamIt->name));
		}*/
		Variables::SetNew(argParamIt->name, MOVE(var));
		++argParamIt;
	}
}

void Simple::disassemble_arguments(Vars_t& from) {
	for (const auto& var : from) {
		Variables::SetNew(var.first, Variable(var.second.value->clone(), var.second.is_const));
	}
}

void Simple::check_pos(int pos, int max_pos, const String& designator) {
	if (pos > max_pos)
		throw Simple_Error("Pos greater than " + designator + " size");
	else if (pos < 0)
		throw Simple_Error("Pos cannot be negative");
}

Fields_decl_t Simple::copy_fields_params(const Fields_decl_t& from) {
	Fields_decl_t copy_fields_params;

	for (auto& field_params : from) {

		ValuePtr copy_value;
		if (field_params.second.defaultValue)
			copy_value = field_params.second.defaultValue->clone();

		copy_fields_params.emplace(field_params.first,
			FIELD(field_params.second.type,
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