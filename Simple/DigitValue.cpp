#include "Values.h"
#include "Simple_defines.h"
#include "Simple_Error.h"

#include <cmath>

using namespace Simple;

DigitValue::DigitValue(const double value)
	: value(value) {}

double DigitValue::AsDouble() const {
	return value;
}

WString DigitValue::AsString() const {
	return std::to_wstring(static_cast<int>(value));
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

WString DigitValue::GetTypeInString() const {
	return L"digit";
}

Simple_Iterator DigitValue::begin() {
	throw Simple_Error("begin There is no operator corresponding");
}

Simple_Iterator DigitValue::end() {
	throw Simple_Error("end There is no operator corresponding");
}

ValuePtr DigitValue::operator+(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value + other->AsDouble());

	throw Simple_Error(L"+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr DigitValue::operator-(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value - other->AsDouble());

	throw Simple_Error(L"+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr DigitValue::operator*(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value * other->AsDouble());

	if (is_char_value(other))
		return STRING(multiply_str(other->AsString(), (int)AsDouble()));

	throw Simple_Error(L"* There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr DigitValue::operator/(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value / other->AsDouble());
	throw Simple_Error(L"/ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

void DigitValue::operator+=(const ValuePtr& other) {
	value = this->operator+(other)->AsDouble();
}

void DigitValue::operator-=(const ValuePtr& other) {
	value = this->operator-(other)->AsDouble();
}

void DigitValue::operator*=(const ValuePtr& other) {
	value = this->operator*(other)->AsDouble();
}

void DigitValue::operator/=(const ValuePtr& other) {
	value = this->operator/(other)->AsDouble();
}

void DigitValue::powereq(const ValuePtr& other) {
	value = this->power(other)->AsDouble();
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
	if (is_number_value(other))
		return value < other->AsDouble();

	throw Simple_Error(L"< There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool DigitValue::operator>(const ValuePtr& other) const {
	if (is_number_value(other))
		return value > other->AsDouble();

	throw Simple_Error(L"> There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool DigitValue::operator<=(const ValuePtr& other) const {
	if (is_number_value(other))
		return value <= other->AsDouble();

	throw Simple_Error(L"<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool DigitValue::operator>=(const ValuePtr& other) const {
	if (is_number_value(other))
		return value >= other->AsDouble();

	throw Simple_Error(L">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool DigitValue::operator==(const ValuePtr& other) const {
	if (is_number_value(other))
		return value == other->AsDouble();

	throw Simple_Error(L"== There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool DigitValue::operator!=(const ValuePtr& other) const {
	if (is_number_value(other))
		return value != other->AsDouble();

	throw Simple_Error(L"!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

Value& DigitValue::operator[](int pos) {
	throw Simple_Error("[] There is no operator corresponding");
}

ValuePtr DigitValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr DigitValue::power(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(std::pow(value, other->AsDouble()));

	throw Simple_Error(L"!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

Value& DigitValue::dot(const WString& key) const {
	throw Simple_Error(L"Digit does not have a member named \"" + key + L"\"");
}

ValuePtr DigitValue::call_method(const WString& key, int args_count, Args_t args) const {
	throw Simple_Error(L"Digit does not have a member named \"" + key + L"\"");
}
