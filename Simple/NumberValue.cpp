#include "Values.h"
#include "Utils.h"
#include "Simple_Error.h"

using namespace Simple;

NumberValue::NumberValue(const double value) 
	: value(value) {}

double NumberValue::AsDouble() const {
	return value;
}

std::string NumberValue::AsString() const {
	int int_value = static_cast<int>(value);
	if (value == int_value)
		return std::to_string(int_value);
	return std::to_string(value);
}

ValuePtr NumberValue::clone() const {
	return NUMBER(value);
}

Value& NumberValue::get_ref() {
	return *this;
}

void NumberValue::set_ref(ValuePtr& ref) {
	if (auto numberRef = dynamic_cast<NumberValue*>(ref.get())) {
		value = numberRef->value;
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType NumberValue::GetType() const {
	return ValueType::_NUMBER;
}

std::string NumberValue::GetTypeInString() const {
	return "num";
}

ValuePtr NumberValue::operator+(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return NUMBER(value + other->AsDouble());
	throw Simple_Error("+ There is no operator corresponding to these operands: " 
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr NumberValue::operator-(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return NUMBER(value - other->AsDouble());
	throw Simple_Error("- There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr NumberValue::operator*(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return NUMBER(value * other->AsDouble());

	auto multiply_str = [this, &other]() {
		std::string result, str = other->AsString();
		for (size_t i = 0; i < AsDouble(); i++) {
			result += str;
		}
		return result;
		};

	if (other->GetType() == ValueType::_STRING || other->GetType() == ValueType::_CHAR)
		return STRING(multiply_str());

	throw Simple_Error("* There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr NumberValue::operator/(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return NUMBER(value / other->AsDouble());
	throw Simple_Error("+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr NumberValue::operator++() {
	++value;
	return NUMBER(value);
}

ValuePtr NumberValue::operator++(int) {
	ValuePtr temp = NUMBER(value);
	++value;
	return std::move(temp);
}

ValuePtr NumberValue::operator--() {
	--value;
	return NUMBER(value);
}

ValuePtr NumberValue::operator--(int) {
	ValuePtr temp = NUMBER(value);
	--value;
	return std::move(temp);
}

bool NumberValue::operator<(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value < other->AsDouble();

	throw Simple_Error("< There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator>(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value > other->AsDouble();

	throw Simple_Error("> There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator<=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value <= other->AsDouble();

	throw Simple_Error("<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator>=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value >= other->AsDouble();

	throw Simple_Error(">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator==(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value == other->AsDouble();

	throw Simple_Error("== There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool NumberValue::operator!=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value != other->AsDouble();

	throw Simple_Error("!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

Value& NumberValue::operator[](int pos) {
	throw Simple_Error("[] There is no operator corresponding");
}

ValuePtr NumberValue::power(const ValuePtr& other) const {
	return NUMBER(std::pow(AsDouble(), other->AsDouble()));
}

Value& NumberValue::dot(const std::string& key) const {
	throw Simple_Error("Number does not have a member named \"" + key + "\"");
}