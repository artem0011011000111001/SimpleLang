#include "Expressions.h"
#include "Values.h"
#include "Variables.h"
#include "Simple_Error.h"

using namespace Simple;

UnaryExpression::UnaryExpression(const UnaryOperators operation, ExpressionPtr expr) : operation(operation), expr(std::move(expr)) {}

//ValuePtr UnaryExpression::eval() {
//	return get_ref().clone();
//}

Value& UnaryExpression::eval() {

	auto IncrementDecrement = [this](bool IsInc, bool IsPr) {

		ValuePtr key = expr->eval().clone();
		ValuePtr newValue = nullptr;
		ValuePtr setValue = nullptr;

		if (IsInc) {
			ValuePtr key_copy = key->clone();
			setValue = key_copy->operator++();
			newValue = IsPr ? setValue->clone() : key->operator++(0);
		}
		else {
			ValuePtr key_copy = key->clone();
			setValue = key_copy->operator--();
			newValue = IsPr ? setValue->clone() : key->operator--(0);
		}

		expr->eval().set_ref(setValue);

		return std::move(newValue);
		};

	/*if (operation == "+")
		ref = NUMBER(expr->eval().AsDouble());*/

	if (operation == UnaryOperators::MINUS)
		ref = NUMBER(-expr->eval().AsDouble());

	else if (operation == UnaryOperators::NOT)
		ref = NUMBER(!(expr->eval().AsDouble()));

	else if (operation == UnaryOperators::PRE_INC) {
		ref = IncrementDecrement(true, true);
	}

	else if (operation == UnaryOperators::POST_INC) {
		ref = IncrementDecrement(true, false);
	}

	else if (operation == UnaryOperators::PRE_DEC) {
		ref = IncrementDecrement(false, true);
	}

	else if (operation == UnaryOperators::POST_DEC) {
		ref = IncrementDecrement(false, false);
	}

	else throw Simple_Error("Unknown unary operation");

	return *ref;
}