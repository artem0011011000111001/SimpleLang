#include "Values.h"
#include "Simple_Error.h"

using namespace Simple;

double VoidValue::AsDouble() const {
	return 0;
}

std::string VoidValue::AsString() const {
	return "Void";
}

ValuePtr VoidValue::clone() const {
	return VOID;
}

Value& VoidValue::get_ref() {
	return *this;
}

void VoidValue::set_ref(ValuePtr& ref) {
	if (auto structRef = dynamic_cast<VoidValue*>(ref.get())) {
		throw Simple_Error("Cannot be assigned to type void");
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType VoidValue::GetType() const {
	return ValueType::_VOID;
}

std::string VoidValue::GetTypeInString() const {
	return "void";
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

ValuePtr VoidValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

Value& VoidValue::dot(const std::string& key) const {
	throw Simple_Error("Void does not have a member named \"" + key + "\"");
}