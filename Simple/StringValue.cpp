#include "Values.h"
#include "Simple_Error.h"
#include "Utils.h"

using namespace Simple;

StringValue::StringValue(const std::string value) : value(value) {}

double StringValue::AsDouble() {
	return strict_stod(value);
}

std::string StringValue::AsString() {
	return value;
}

ValuePtr StringValue::clone() const {
	return std::make_unique<StringValue>(value);
}

ValueType StringValue::GetType() const
{
	return ValueType::STRING;
}

bool StringValue::operator==(const ValuePtr& other) const {
	if (IdentifyValueType(other) != ValueType::STRING)
		throw Simple_Error("Can't compare a number to another type");

	return value == other->AsString();
}
