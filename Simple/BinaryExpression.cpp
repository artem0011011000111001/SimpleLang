#include "Expressions.h"
#include "Simple_typedefs.h"
#include "Values.h"
#include "Simple_Error.h"

#include <type_traits>
#include <cmath>

using namespace Simple;

BinaryExpression::BinaryExpression(ExpressionPtr expr1, const BinaryOperators operation, ExpressionPtr expr2)
	: expr1(std::move(expr1)), operation(operation), expr2(std::move(expr2)) {}

ValuePtr BinaryExpression::eval() const {
	const ValuePtr value1 = (*expr1).eval();
	const ValuePtr value2 = (*expr2).eval();

	auto value1_type = IdentifyValueType(value1);
	auto value2_type = IdentifyValueType(value2);

	if (value1_type == ValueType::STRING) {
		const std::string str = value1.get()->AsString();
		switch (operation)
		{
		case BinaryOperators::MULTIPLY:
			if (value2_type == ValueType::NUMBER) {
				std::string buffer;
				double double_value = value2.get()->AsDouble();

				if (double_value < 0) throw Simple_Error("Multiplying a string by a negative number");
				else if (double_value == 0) return std::make_unique<StringValue>("");

				const size_t iterations = static_cast<size_t>(double_value);
				for (size_t i = 0; i < iterations; i++) {
					buffer.append(str);
				}
				return std::make_unique<StringValue>(buffer);
			}
			else throw Simple_Error("Multiplication by a number was expected");
		case BinaryOperators::PLUS:
			if (value2_type == ValueType::STRING)
				return std::make_unique<StringValue>(str + value2.get()->AsString());
			else throw Simple_Error("String concatenation expected");
		}
	}

	if (value2_type == ValueType::STRING) {
		if (operation == BinaryOperators::MULTIPLY) {
			std::string str = value2.get()->AsString();
			double double_value = value1.get()->AsDouble();

			if (double_value < 0) throw Simple_Error("Multiplying a string by a negative number");
			else if (double_value == 0) return std::make_unique<StringValue>("");

			const size_t iterations = static_cast<size_t>(double_value);
			std::string buffer;

			for (size_t i = 0; i < iterations; i++) {
				buffer.append(str);
			}
			return std::make_unique<StringValue>(buffer);
		}
		else throw Simple_Error("Multiplication by a number was expected");
	}
	
	double double_value1 = value1.get()->AsDouble();
	double double_value2 = value2.get()->AsDouble();

	switch (operation)
	{
	case BinaryOperators::MINUS:  return std::make_unique<NumberValue>(double_value1 - double_value2);
	case BinaryOperators::MULTIPLY:  return std::make_unique<NumberValue>(double_value1 * double_value2);
	case BinaryOperators::DIVIDE:  return std::make_unique<NumberValue>(double_value1 / double_value2);
	case BinaryOperators::PLUS:  return std::make_unique<NumberValue>(double_value1 + double_value2);
	case BinaryOperators::POWER: return std::make_unique<NumberValue>(std::pow(double_value1, double_value2));
	default: throw Simple_Error("\"" + Simple::to_string(operation) + std::string("\" is unknown operation"));
	}
}

std::string BinaryExpression::to_string() const {
	return expr1.get()->eval().get()->AsString() + " " + Simple::to_string(operation) + " " + expr2.get()->eval().get()->AsString();
}