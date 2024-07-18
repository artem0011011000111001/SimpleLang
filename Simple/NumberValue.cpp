#include "Values.h"
#include "Utils.h"
#include "Simple_Error.h"

using namespace Simple;

NumberValue::NumberValue(const double value) : value(value) {}

double NumberValue::AsDouble() {
	return value;
}

std::string NumberValue::AsString() {
	int int_value = static_cast<int>(value);
	if (value == int_value)
		return std::to_string(int_value);
	return std::to_string(value);
}

ValuePtr NumberValue::clone() const {
	return std::make_unique<NumberValue>(value);
}

ValueType NumberValue::GetType() const {
	return ValueType::NUMBER;
}

bool NumberValue::operator==(const ValuePtr& other) const {
	if (IdentifyValueType(other) != ValueType::NUMBER)
		throw Simple_Error("Can't compare a number to another type");

	return value == other->AsDouble();
}
