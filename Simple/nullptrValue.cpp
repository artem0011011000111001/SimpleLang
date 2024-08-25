#include "Values.h"

using namespace Simple;

double nullptrValue::AsDouble() const {
	return 0;
}

nullptrValue::operator bool() {
	return false;
}

WString nullptrValue::AsString() const {
	return L"nullptr";
}

ValuePtr nullptrValue::clone() const {
	return CREATE_PTR<nullptrValue>();
}

Value& nullptrValue::get_ref() {
	return *this;
}

void nullptrValue::set_ref(ValuePtr& ref) {
}

ValueType nullptrValue::GetType() const {
	throw Simple_Error("nullptrValue does not have type");
}

WString nullptrValue::GetTypeInString() const {
	return L"nullptr";
}

Simple_Iterator nullptrValue::begin() {
	throw Simple_Error("begin There is no operator corresponding");
}

Simple_Iterator nullptrValue::end() {
	throw Simple_Error("end There is no operator corresponding");
}

ValuePtr nullptrValue::operator+(const ValuePtr& other) const {
	throw Simple_Error("+ There is no operator corresponding");
}

ValuePtr nullptrValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("- There is no operator corresponding");
}

ValuePtr nullptrValue::operator*(const ValuePtr& other) const {
	throw Simple_Error("* There is no operator corresponding");
}

ValuePtr nullptrValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("/ There is no operator corresponding");
}

void nullptrValue::operator+=(const ValuePtr& other) {
	throw Simple_Error("+= There is no operator corresponding");
}

void nullptrValue::operator-=(const ValuePtr& other) {
	throw Simple_Error("-= There is no operator corresponding");
}

void nullptrValue::operator*=(const ValuePtr& other) {
	throw Simple_Error("*= There is no operator corresponding");
}

void nullptrValue::operator/=(const ValuePtr& other) {
	throw Simple_Error("/= There is no operator corresponding");
}

void nullptrValue::powereq(const ValuePtr& other) {
	throw Simple_Error("**= There is no operator corresponding");
}

ValuePtr nullptrValue::operator++() {
	throw Simple_Error("++i There is no operator corresponding");
}

ValuePtr nullptrValue::operator++(int) {
	throw Simple_Error("i++ There is no operator corresponding");
}

ValuePtr nullptrValue::operator--() {
	throw Simple_Error("--i There is no operator corresponding");
}

ValuePtr nullptrValue::operator--(int) {
	throw Simple_Error("i-- There is no operator corresponding");
}

bool nullptrValue::operator<(const ValuePtr& other) const {
	throw Simple_Error("< There is no operator corresponding");
}

bool nullptrValue::operator>(const ValuePtr& other) const {
	throw Simple_Error("> There is no operator corresponding");
}

bool nullptrValue::operator<=(const ValuePtr& other) const {
	throw Simple_Error("<= There is no operator corresponding");
}

bool nullptrValue::operator>=(const ValuePtr& other) const {
	throw Simple_Error(">= There is no operator corresponding");
}

bool nullptrValue::operator==(const ValuePtr& other) const {
	throw Simple_Error("== There is no operator corresponding");
}

bool nullptrValue::operator!=(const ValuePtr& other) const {
	throw Simple_Error("!= There is no operator corresponding");
}

Value& nullptrValue::operator[](int pos) {
	throw Simple_Error("[] There is no operator corresponding");
}

ValuePtr nullptrValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr nullptrValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

Value& nullptrValue::dot(const WString& key) const {
	throw Simple_Error(L"nullptr does not have a member named \"" + key + L"\"");
}

ValuePtr nullptrValue::call_method(const WString& key, int args_count, Args_t args) const {
	throw Simple_Error(L"nullptr does not have a member named \"" + key + L"\"");
}
