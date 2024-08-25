#include "Values.h"
#include "Utils.h"
#include "Simple_Error.h"

#include <cmath>

using namespace Simple;

NumberValue::NumberValue(const double value) 
	: value(value) {}

double NumberValue::AsDouble() const {
	return value;
}

WString NumberValue::AsString() const {
	int int_value = static_cast<int>(value);
	if (value == int_value)
		return std::to_wstring(int_value);
	return std::to_wstring(value);
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

WString NumberValue::GetTypeInString() const {
	return L"num";
}

Simple_Iterator NumberValue::begin() {
	throw Simple_Error("begin There is no operator corresponding");
}

Simple_Iterator NumberValue::end() {
	throw Simple_Error("end There is no operator corresponding");
}

ValuePtr NumberValue::operator+(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value + other->AsDouble());
	throw Simple_Error(L"+ There is no operator corresponding to these operands: " 
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr NumberValue::operator-(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value - other->AsDouble());
	throw Simple_Error(L"- There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr NumberValue::operator*(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value * other->AsDouble()); 

	if (is_char_value(other))
		return STRING(multiply_str(other->AsString(), (int)value));

	throw Simple_Error(L"* There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr NumberValue::operator/(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value / other->AsDouble());
	throw Simple_Error(L"/ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

void NumberValue::operator+=(const ValuePtr& other) {
	value = this->operator+(other)->AsDouble();
}

void NumberValue::operator-=(const ValuePtr& other) {
	value = this->operator-(other)->AsDouble();
}

void NumberValue::operator*=(const ValuePtr& other) {
	value = this->operator*(other)->AsDouble();
}

void NumberValue::operator/=(const ValuePtr& other) {
	value = this->operator/(other)->AsDouble();
}

void NumberValue::powereq(const ValuePtr& other) {
	value = this->power(other)->AsDouble();
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
	if (is_number_value(other))
		return value < other->AsDouble();

	throw Simple_Error(L"< There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool NumberValue::operator>(const ValuePtr& other) const {
	if (is_number_value(other))
		return value > other->AsDouble();

	throw Simple_Error(L"> There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool NumberValue::operator<=(const ValuePtr& other) const {
	if (is_number_value(other))
		return value <= other->AsDouble();

	throw Simple_Error(L"<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool NumberValue::operator>=(const ValuePtr& other) const {
	if (is_number_value(other))
		return value >= other->AsDouble();

	throw Simple_Error(L">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool NumberValue::operator==(const ValuePtr& other) const {
	if (is_number_value(other))
		return value == other->AsDouble();

	throw Simple_Error(L"== There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool NumberValue::operator!=(const ValuePtr& other) const {
	if (is_number_value(other))
		return value != other->AsDouble();

	throw Simple_Error(L"!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

Value& NumberValue::operator[](int pos) {
	throw Simple_Error("[] There is no operator corresponding");
}

ValuePtr NumberValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr NumberValue::power(const ValuePtr& other) const {
	return NUMBER(std::pow(AsDouble(), other->AsDouble()));
}

Value& NumberValue::dot(const WString& key) const {
	throw Simple_Error(L"Number does not have a member named \"" + key + L"\"");
}

ValuePtr NumberValue::call_method(const WString& key, int args_count, Args_t args) const {
	throw Simple_Error(L"Number does not have a member named \"" + key + L"\"");
}
