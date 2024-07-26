#include "Values.h"
#include "Simple_Error.h"
#include "Simple_defines.h"
#include "Utils.h"

using namespace Simple;

StringValue::StringValue(const std::string value) 
	: value(value) {}

double StringValue::AsDouble() {
	return strict_stod(value);
}

std::string StringValue::AsString() {
	return value;
}

ValuePtr StringValue::clone() const {
	return STRING(value);
}

Value& StringValue::get_ref() {
	return *this;
}

void StringValue::set_ref(ValuePtr& ref) {
	if (auto stringRef = dynamic_cast<StringValue*>(ref.get())) {
		value = stringRef->value;
	}
	else {
		throw Simple_Error("Invalid reference type");
	}
}

ValueType StringValue::GetType() const {
	return ValueType::STRING;
}

std::string StringValue::GetTypeInString() const {
	return "\"String\"";
}

ValuePtr StringValue::operator+(const ValuePtr& other) const {
	if (other->GetType() == ValueType::STRING)
		return STRING(value + other->AsString());
	throw Simple_Error("+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr StringValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("- There is no operator corresponding");
}

ValuePtr StringValue::operator*(const ValuePtr& other) const {
	if (other->GetType() == ValueType::NUMBER) {
		auto result = [this, &other]() {
			std::string result;
			for (size_t i = 0, size = (size_t)other->AsDouble(); i < size; i++) {
				result += value;
			}
			return result;
			};
		return STRING(result());
	}
	throw Simple_Error("* There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr StringValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("/ There is no operator corresponding");
}

ValuePtr StringValue::operator++() {
	throw Simple_Error("++str There is no operator corresponding");
}

ValuePtr StringValue::operator++(int) {
	throw Simple_Error("str++ There is no operator corresponding");
}

ValuePtr StringValue::operator--() {
	throw Simple_Error("--str There is no operator corresponding");
}

ValuePtr StringValue::operator--(int) {
	throw Simple_Error("str-- There is no operator corresponding");
}

bool StringValue::operator<(const ValuePtr& other) const {
	if (other->GetType() == ValueType::STRING)
		return value < other->AsString();

	throw Simple_Error("< There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator>(const ValuePtr& other) const {
	if (other->GetType() == ValueType::STRING)
		return value > other->AsString();

	throw Simple_Error("> There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator<=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::STRING)
		return value <= other->AsString();

	throw Simple_Error("<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator>=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::STRING)
		return value >= other->AsString();

	throw Simple_Error(">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator==(const ValuePtr& other) const {
	if (other->GetType() == ValueType::STRING)
		return value == other->AsString();

	throw Simple_Error("== There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator!=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::STRING)
		return value != other->AsString();

	throw Simple_Error("!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr StringValue::operator[](int pos) const {
	if (pos >= value.length())
		throw Simple_Error("Pos greater than string length");
	else if (pos < 0)
		throw Simple_Error("Pos cannot be negative");
	return STRING(std::string(1, value[pos]));
}

ValuePtr StringValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

ValuePtr StringValue::dot(const std::string& key) const {
	throw Simple_Error("String does not have a member named \"" + key + "\"");
}