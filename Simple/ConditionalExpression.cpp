#include "Expressions.h"
#include "Simple_typedefs.h"
#include "Utils.h"
#include "Simple_Error.h"
#include "Values.h"

using namespace Simple;

ConditionalExpression::ConditionalExpression(ExpressionPtr expr1, const LogicOperators operation, ExpressionPtr expr2)
	: expr1(std::move(expr1)), operation(operation), expr2(std::move(expr2)) {}

ValuePtr ConditionalExpression::eval() const {
	const ValuePtr value1 = (*expr1).eval();
	const ValuePtr value2 = (*expr2).eval();

	auto value1_type = value1->GetType();
	auto value2_type = value2->GetType();
 
	double result1, result2;

	if (value1_type == ValueType::STRING) {
		if (value2_type == ValueType::NUMBER) throw Simple_Error("Can't compare string and number");
		const std::string str1 = value1.get()->AsString();
		const std::string str2 = value2.get()->AsString();
		switch (operation)
		{
		case LogicOperators::EQUALS:	 return std::make_unique<NumberValue>(str1 == str2);
		case LogicOperators::NOT_EQUALS: return std::make_unique<NumberValue>(str1 != str2);
		case LogicOperators::LT:		 return std::make_unique<NumberValue>(str1 < str2);
		case LogicOperators::LTEQ:	   	 return std::make_unique<NumberValue>(str1 <= str2);
		case LogicOperators::GT:		 return std::make_unique<NumberValue>(str1 > str2);
		case LogicOperators::GTEQ:		 return std::make_unique<NumberValue>(str1 >= str2);
		default: throw Simple_Error("Unknown logic operation");
		}
	}
	else {
		result1 = value1->AsDouble();
		result2 = value2->AsDouble();
	}

	if (value2_type == ValueType::STRING) throw Simple_Error("Can't compare string and number");
	//double double_value1 = value1.get()->AsDouble();
	//double double_value2 = value2.get()->AsDouble();

	switch (operation)
	{
	case LogicOperators::EQUALS:	 return std::make_unique<NumberValue>(result1 == result2);
	case LogicOperators::NOT_EQUALS: return std::make_unique<NumberValue>(result1 != result2);
	case LogicOperators::LT:		 return std::make_unique<NumberValue>(result1 <  result2);
	case LogicOperators::LTEQ:	   	 return std::make_unique<NumberValue>(result1 <= result2);
	case LogicOperators::GT:		 return std::make_unique<NumberValue>(result1 >  result2);
	case LogicOperators::GTEQ:		 return std::make_unique<NumberValue>(result1 >= result2);

	case LogicOperators::AND:		 return std::make_unique<NumberValue>(result1 != 0 && result2 != 0);
	case LogicOperators::OR:		 return std::make_unique<NumberValue>(result1 != 0 || result2 != 0);

	default: throw Simple_Error("Unknown logic operation");
	}
}

std::string ConditionalExpression::to_string() const {
	return expr1->eval()->AsString() + " " + Simple::to_string(operation) + " " + expr2->eval()->AsString();
}