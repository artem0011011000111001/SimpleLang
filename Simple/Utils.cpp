#include "Utils.h"
#include "Values.h"
#include "Simple_Error.h"

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

ValueType Simple::IdentifyValueType(const ValuePtr& valuePtr) {

	if (dynamic_cast<NumberValue*>(valuePtr.get()))
		return ValueType::NUMBER;

	else if (dynamic_cast<StringValue*>(valuePtr.get()))
		return ValueType::STRING;
}

std::string Simple::to_string(LogicOperators op)
{
	switch (op)
	{
	/*case LogicOperators::PLUS:
		return "+";
	case LogicOperators::MINUS:
		return "-";
	case LogicOperators::MULTIPLY:
		return "*";
	case LogicOperators::DIVIDE:
		return "/";*/
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

std::string Simple::to_string(ValueType val) {
	switch (val)
	{
	case ValueType::NUMBER:
		return "number";
	case ValueType::STRING:
		return "string";
	default:
		break;
	}
}

void Simple::copy_variables(const std::unordered_map<std::string, ValuePtr>&from, std::unordered_map<std::string, ValuePtr>&whom) {
	for (const auto& var : from) {
		whom[var.first] = var.second->clone();
	}

}