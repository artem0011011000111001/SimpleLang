#include "Values.h"
#include "Simple_Error.h"

using namespace Simple;

double VoidValue::AsDouble() const {
	return 0;
}

WString VoidValue::AsString() const {
	return L"void";
}

ValuePtr VoidValue::clone() const {
	return VOID;
}

Value& VoidValue::get_ref() {
	return *this;
}

void VoidValue::set_ref(ValuePtr& ref) {
	if (auto voidRef = dynamic_cast<VoidValue*>(ref.get())) {
		throw Simple_Error("Cannot be assigned to type void");
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType VoidValue::GetType() const {
	return ValueType::_VOID;
}

WString VoidValue::GetTypeInString() const {
	return L"void";
}

Simple_Iterator VoidValue::begin() {
	throw Simple_Error("begin There is no operator corresponding");
}

Simple_Iterator VoidValue::end() {
	throw Simple_Error("end There is no operator corresponding");
}

ValuePtr VoidValue::operator+(const ValuePtr& other) const {
	throw Simple_Error("+ There is no operator corresponding");
}

ValuePtr VoidValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("- There is no operator corresponding");
}

ValuePtr VoidValue::operator*(const ValuePtr& other) const {
	throw Simple_Error("* There is no operator corresponding");
}

ValuePtr VoidValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("/ There is no operator corresponding");
}

ValuePtr VoidValue::operator++() {
	throw Simple_Error("++i There is no operator corresponding");
}

ValuePtr VoidValue::operator++(int) {
	throw Simple_Error("i++ There is no operator corresponding");
}

ValuePtr VoidValue::operator--() {
	throw Simple_Error("--i There is no operator corresponding");
}

ValuePtr VoidValue::operator--(int) {
	throw Simple_Error("i-- There is no operator corresponding");
}

bool VoidValue::operator<(const ValuePtr& other) const {
	throw Simple_Error("< There is no operator corresponding");
}

bool VoidValue::operator>(const ValuePtr& other) const {
	throw Simple_Error("> There is no operator corresponding");
}

bool VoidValue::operator<=(const ValuePtr& other) const {
	throw Simple_Error("<= There is no operator corresponding");
}

bool VoidValue::operator>=(const ValuePtr& other) const {
	throw Simple_Error(">= There is no operator corresponding");
}

bool VoidValue::operator==(const ValuePtr& other) const {
	throw Simple_Error("== There is no operator corresponding");
}

bool VoidValue::operator!=(const ValuePtr& other) const {
	throw Simple_Error("!= There is no operator corresponding");
}

Value& VoidValue::operator[](int pos) {
	throw Simple_Error("[] There is no operator corresponding");
}

ValuePtr VoidValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr VoidValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

Value& VoidValue::dot(const WString& key) const {
	throw Simple_Error(L"Void does not have a member named \"" + key + L"\"");
}