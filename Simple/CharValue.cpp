#include "Values.h"
#include "Simple_Error.h"

using namespace Simple;

CharValue::CharValue(const WString& value)
	: value(value) {}

double CharValue::AsDouble() const {
	if (isdigit(value[0]))
		return stoi(value);
	throw Simple_Error("\'" + value[0] + String("\' not digit"));
}

WString CharValue::AsString() const {
	return value;
}

ValuePtr CharValue::clone() const {
	return CHAR(value);
}

Value& CharValue::get_ref() {
	return *this;
}

void CharValue::set_ref(ValuePtr& ref) {
	if (auto charRef = dynamic_cast<CharValue*>(ref.get())) {
		value = charRef->value;
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType CharValue::GetType() const {
	return ValueType::_CHAR;
}

WString CharValue::GetTypeInString() const {
	return L"char";
}

Simple_Iterator CharValue::begin() {
	throw Simple_Error("begin There is no operator corresponding");
}

Simple_Iterator CharValue::end() {
	throw Simple_Error("end There is no operator corresponding");
}

ValuePtr CharValue::operator+(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_CHAR || other->GetType() == ValueType::_STRING)
		return STRING(value + other->AsString());

	throw Simple_Error(L"+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr CharValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("- There is no operator corresponding");
}

ValuePtr CharValue::operator*(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_)
		return STRING([this, &other]() {
		WString result;
			for (size_t i = 0, count = static_cast<size_t>(other->AsDouble()); i < count; i++) {
				result += value;
			}
			return result;
			}());
	throw Simple_Error(L"* There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr CharValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("/ There is no operator corresponding");
}	

ValuePtr CharValue::operator++() {
	throw Simple_Error("++i There is no operator corresponding");
}

ValuePtr CharValue::operator++(int) {
	throw Simple_Error("i++ There is no operator corresponding");
}

ValuePtr CharValue::operator--() {
	throw Simple_Error("--i There is no operator corresponding");
}

ValuePtr CharValue::operator--(int) {
	throw Simple_Error("i-- There is no operator corresponding");
}

bool CharValue::operator<(const ValuePtr& other) const {
	throw Simple_Error("< There is no operator corresponding");
}

bool CharValue::operator>(const ValuePtr& other) const {
	throw Simple_Error("> There is no operator corresponding");
}

bool CharValue::operator<=(const ValuePtr& other) const {
	throw Simple_Error("<= There is no operator corresponding");
}

bool CharValue::operator>=(const ValuePtr& other) const {
	throw Simple_Error(">= There is no operator corresponding");
}

bool CharValue::operator==(const ValuePtr& other) const {
	throw Simple_Error("== There is no operator corresponding");
}

bool CharValue::operator!=(const ValuePtr& other) const {
	throw Simple_Error("!= There is no operator corresponding");
}

Value& CharValue::operator[](int pos) {
	throw Simple_Error("[] There is no operator corresponding");
}

ValuePtr CharValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr CharValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

Value& CharValue::dot(const WString& key) const {
	throw Simple_Error(L"Void does not have a member named \"" + key + L"\"");
}