#include "Utils.h"
#include "Values.h"
#include "Simple_Error.h"
#include "Variable.h"
#include "Variables.h"
#include "Structs.h"

using namespace Simple;

double Simple::strict_stod(const std::string str) {
	double result;
	size_t pos;
	try {
		result = std::stod(str, &pos);
		if (pos != str.length())
			throw 0;
	}
	catch (...) {
		throw Simple_Error("\"" + str + "\" not number");
	}
	return result;
}

std::string Simple::to_string(LogicOperators op)
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

std::string Simple::to_string(BinaryOperators op)
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

std::string Simple::IdentifyCategory(ValueType type) {
	switch (type) {

	case Simple::ValueType::_DIGIT_:
		return "Primitive";

	case Simple::ValueType::_NUMBER:
		return "Primitive";

	case Simple::ValueType::_CHAR:
		return "Primitive";

	case Simple::ValueType::_STRING:
		return "Primitive";

	case Simple::ValueType::_STRUCT:
		return "Struct";

	case Simple::ValueType::_VOID:
		return "Primitive";

	default:
		throw Simple_Error("Unknown type");
	}
}

ValueType Simple::IdentifyValueType(const String& key) {
	if (key == "num")
		return ValueType::_NUMBER;
	else if (key == "str")
		return ValueType::_STRING;
	else if (key == "void")
		return ValueType::_VOID;
	else if (key == "digit")
		return ValueType::_DIGIT_;
	else if (key == "char")
		return ValueType::_CHAR;
	else if (Structs::IsExist(key))
		return ValueType::_USER_STRUCT;
	else throw Simple_Error("\"" + key + "\" is invalid type");
}

bool Simple::equals_type(const String& key1, const String& key2) {
	ValueType type1 = IdentifyValueType(key1),
	type2 = IdentifyValueType(key2);
	if (type1 == ValueType::_USER_STRUCT && type2 == ValueType::_USER_STRUCT)
		return Structs::_equals(key1, key2);
	return type1 == type2;
}

void Simple::copy_variables(const std::unordered_map<std::string, Variable>&from, std::unordered_map<std::string, Variable>&whom) {
	for (const auto& var : from) {
		whom[var.first].value = var.second.value->clone();
	}
}

void Simple::create_arguments(ArgsParam_t& argsParam, Args_t& args, std::unordered_map<std::string, Variable>& whom) {
	auto argNameIt = argsParam.first.begin();
	auto argIsConstIt = argsParam.second.begin();
	for (auto& arg : args) {
		if (Variables::IsExist(*argNameIt)) {
			whom[*argNameIt] = Variable(Variables::Get(*argNameIt), Variables::IsConstant(*argNameIt));
		}
		Variables::SetNew(*argNameIt, Variable(std::move(arg), *argIsConstIt));
		++argNameIt;
	}
}

void Simple::disassemble_arguments(std::unordered_map<std::string, Variable>& from) {
	for (const auto& var : from) {
		Variables::SetNew(var.first, Variable(var.second.value->clone(), var.second.is_const));
	}
}