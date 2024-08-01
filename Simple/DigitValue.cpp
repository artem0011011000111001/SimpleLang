#include "Values.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

using namespace Simple;

DigitValue::DigitValue(const double value)
	: value(value) {}

double DigitValue::AsDouble() const {
	return value;
}

String DigitValue::AsString() const {
	return std::to_string(static_cast<int>(value));
}

ValuePtr DigitValue::clone() const {
	return DIGIT(value);
}

Value& DigitValue::get_ref() {
	return *this;
}

void DigitValue::set_ref(ValuePtr& ref) {
	if (auto digitRef = dynamic_cast<DigitValue*>(ref.get())) {
		value = digitRef->value;
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType DigitValue::GetType() const {
	return ValueType::_DIGIT_;
}

String DigitValue::GetTypeInString() const {
	return "digit";
}

ValuePtr DigitValue::operator+(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return NUMBER(value + other->AsDouble());
	throw Simple_Error("+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr DigitValue::operator-(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return NUMBER(value - other->AsDouble());
	throw Simple_Error("+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr DigitValue::operator*(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return NUMBER(value * other->AsDouble());

	auto multiply_str = [this, &other]() {
		String result, str = other->AsString();
		for (size_t i = 0; i < value; i++) {
			result += str;
		}
		return result;
		};

	if (other->GetType() == ValueType::_STRING || other->GetType() == ValueType::_CHAR)
		return STRING(multiply_str());

	throw Simple_Error("* There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr DigitValue::operator/(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return NUMBER(value / other->AsDouble());
	throw Simple_Error("+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

ValuePtr DigitValue::operator++() {
	++value;
	if (value > 9)
		value = 0;
	return DIGIT(value);
}

ValuePtr DigitValue::operator++(int) {
	ValuePtr temp = DIGIT(value);
	++value;
	if (value > 9)
		value = 0;
	return std::move(temp);
}

ValuePtr DigitValue::operator--() {
	--value;
	if (value < 0)
		value = 9;
	return DIGIT(value);
}

ValuePtr DigitValue::operator--(int) {
	ValuePtr temp = DIGIT(value);
	--value;
	if (value < 0)
		value = 9;
	return std::move(temp);
}

bool DigitValue::operator<(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value < other->AsDouble();

	throw Simple_Error("< There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool DigitValue::operator>(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value > other->AsDouble();

	throw Simple_Error("> There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool DigitValue::operator<=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value <= other->AsDouble();

	throw Simple_Error("<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool DigitValue::operator>=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value >= other->AsDouble();

	throw Simple_Error(">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool DigitValue::operator==(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value == other->AsDouble();

	throw Simple_Error("== There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

bool DigitValue::operator!=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return value != other->AsDouble();

	throw Simple_Error("!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

Value& DigitValue::operator[](int pos) {
	throw Simple_Error("[] There is no operator corresponding");
}

ValuePtr DigitValue::power(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return NUMBER(std::pow(value, other->AsDouble()));

	throw Simple_Error("!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + " " + other->GetTypeInString());
}

Value& DigitValue::dot(const String& key) const {
	throw Simple_Error("Digit does not have a member named \"" + key + "\"");
}