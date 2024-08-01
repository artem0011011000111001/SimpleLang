#include "Values.h"
#include "Simple_Error.h"
#include "Simple_defines.h"
#include "Utils.h"

using namespace Simple;

StringValue::StringValue(const std::string& value) 
	: value([this, value]() {
			std::vector<CharValue> result;
			for (auto& Char : value) {
				result.push_back(std::string(1, Char));
			}
			return result;
		}()) {}

double StringValue::AsDouble() const {
	return strict_stod(AsString());
}

std::string StringValue::AsString() const {
	std::string result;
	for (auto& Char : value) {
		result.push_back(Char.AsString()[0]);
	}
	return result;
}

ValuePtr StringValue::clone() const {
	return STRING(AsString());
}

Value& StringValue::get_ref() {
	return *this;
}

void StringValue::set_ref(ValuePtr& ref) {
	if (auto stringRef = dynamic_cast<StringValue*>(ref.get())) {
		value = stringRef->value;
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType StringValue::GetType() const {
	return ValueType::_STRING;
}

std::string StringValue::GetTypeInString() const {
	return "str";
}

ValuePtr StringValue::operator+(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING || other->GetType() == ValueType::_CHAR)
		return STRING(AsString() + other->AsString());

	throw Simple_Error("+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr StringValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("- There is no operator corresponding");
}

ValuePtr StringValue::operator*(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_) {
		auto result = [this, &other]() {
			std::string result;
			for (size_t i = 0, size = (size_t)other->AsDouble(); i < size; i++) {
				result += AsString();
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
	throw Simple_Error("++i There is no operator corresponding");
}

ValuePtr StringValue::operator++(int) {
	throw Simple_Error("i++ There is no operator corresponding");
}

ValuePtr StringValue::operator--() {
	throw Simple_Error("--i There is no operator corresponding");
}

ValuePtr StringValue::operator--(int) {
	throw Simple_Error("i-- There is no operator corresponding");
}

bool StringValue::operator<(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() < other->AsString();

	throw Simple_Error("< There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator>(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() > other->AsString();

	throw Simple_Error("> There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator<=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() <= other->AsString();

	throw Simple_Error("<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator>=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() >= other->AsString();

	throw Simple_Error(">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator==(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() == other->AsString();

	throw Simple_Error("== There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool StringValue::operator!=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() != other->AsString();

	throw Simple_Error("!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

Value& StringValue::operator[](int pos) {
	if (pos >= AsString().length())
		throw Simple_Error("Pos greater than string length");
	else if (pos < 0)
		throw Simple_Error("Pos cannot be negative");

	return value[pos].get_ref();
}

ValuePtr StringValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

Value& StringValue::dot(const std::string& key) const {
	throw Simple_Error("String does not have a member named \"" + key + "\"");
}