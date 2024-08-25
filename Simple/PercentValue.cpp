#include "Values.h"

using namespace Simple;

PercentValue::PercentValue(const double value)
	: value(value) {}

double PercentValue::AsDouble() const {
	return value / 100;
}

WString PercentValue::AsString() const {
	int int_value = static_cast<int>(value);
	if (value == int_value)
		return std::to_wstring(int_value) + L"%";
	return std::to_wstring(value) + L"%";
}

ValuePtr PercentValue::clone() const {
	return PERCENT(value);
}

Value& PercentValue::get_ref() {
	return *this;
}

void PercentValue::set_ref(ValuePtr& ref) {
	if (auto percentRef = dynamic_cast<PercentValue*>(ref.get())) {
		value = percentRef->value;
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType PercentValue::GetType() const {
	return ValueType::_PERCENT;
}

WString PercentValue::GetTypeInString() const {
	return L"percent";
}

Simple_Iterator PercentValue::begin() {
	throw Simple_Error("begin There is no operator corresponding");
}

Simple_Iterator PercentValue::end() {
	throw Simple_Error("end There is no operator corresponding");
}

ValuePtr PercentValue::operator+(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value + other->AsDouble());

	throw Simple_Error(L"+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr PercentValue::operator-(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value - other->AsDouble());

	throw Simple_Error(L"- There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr PercentValue::operator*(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value * other->AsDouble());

	if (is_char_value(other))
		return STRING(multiply_str(other->AsString(), (int)AsDouble()));

	throw Simple_Error(L"* There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr PercentValue::operator/(const ValuePtr& other) const {
	if (is_number_value(other))
		return NUMBER(value / other->AsDouble());

	throw Simple_Error(L"/ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

void PercentValue::operator+=(const ValuePtr& other) {
	value = this->operator+(other)->AsDouble();
}

void PercentValue::operator-=(const ValuePtr& other) {
	value = this->operator-(other)->AsDouble();
}

void PercentValue::operator*=(const ValuePtr& other) {
	value = this->operator*(other)->AsDouble();
}

void PercentValue::operator/=(const ValuePtr& other) {
	value = this->operator/(other)->AsDouble();
}

void PercentValue::powereq(const ValuePtr& other) {
	value = this->power(other)->AsDouble();
}

ValuePtr PercentValue::operator++() {
	++value;
	return PERCENT(value);
}

ValuePtr PercentValue::operator++(int) {
	ValuePtr temp = PERCENT(value);
	++value;
	return std::move(temp);
}

ValuePtr PercentValue::operator--() {
	--value;
	return PERCENT(value);
}

ValuePtr PercentValue::operator--(int) {
	ValuePtr temp = PERCENT(value);
	--value;
	return MOVE(temp);
}

bool PercentValue::operator<(const ValuePtr& other) const {
	if (is_number_value(other))
		return value < other->AsDouble();

	throw Simple_Error(L"< There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool PercentValue::operator>(const ValuePtr& other) const {
	if (is_number_value(other))
		return value > other->AsDouble();

	throw Simple_Error(L"> There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool PercentValue::operator<=(const ValuePtr& other) const {
	if (is_number_value(other))
		return value <= other->AsDouble();

	throw Simple_Error(L"<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool PercentValue::operator>=(const ValuePtr& other) const {
	if (is_number_value(other))
		return value >= other->AsDouble();

	throw Simple_Error(L">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool PercentValue::operator==(const ValuePtr& other) const {
	if (is_number_value(other))
		return value == other->AsDouble();

	throw Simple_Error(L"== There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool PercentValue::operator!=(const ValuePtr& other) const {
	if (is_number_value(other))
		return value != other->AsDouble();

	throw Simple_Error(L"!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

Value& PercentValue::operator[](int pos) {
	throw Simple_Error("[] There is no operator corresponding");
}

ValuePtr PercentValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr PercentValue::power(const ValuePtr& other) const {
	return NUMBER(std::pow(AsDouble(), other->AsDouble()));
}

Value& PercentValue::dot(const WString& key) const {
	throw Simple_Error(L"Number does not have a member named \"" + key + L"\"");
}

ValuePtr PercentValue::call_method(const WString& key, int args_count, Args_t args) const {
	throw Simple_Error(L"Percent does not have a member named \"" + key + L"\"");
}
