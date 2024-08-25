#include "Values.h"
#include "Simple_Error.h"
#include "Function.h"
#include "FuncParams.h"
#include "Functions.h"

using namespace Simple;

FunctionValue::FunctionValue(WString& key)
	: func(MOVE(Functions::Get(key))) {}

FunctionValue::FunctionValue(FuncParams func)
	: func(MOVE(func)) {}

double FunctionValue::AsDouble() const {
	throw Simple_Error("to_num There is no operator corresponding");
}

WString FunctionValue::AsString() const {
	throw Simple_Error("to_str There is no operator corresponding");
}

ValuePtr FunctionValue::clone() const {
	return FUNCTION(MOVE(func.clone()));
}

Value& FunctionValue::get_ref() {
	return *this;
}

void FunctionValue::set_ref(ValuePtr& ref) {
	if (auto funcRef = dynamic_cast<FunctionValue*>(ref.get())) {
		func = funcRef->func.clone();
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType FunctionValue::GetType() const {
	return ValueType::_FUNCTION;
}

WString FunctionValue::GetTypeInString() const {
	return L"function";
}

Simple_Iterator FunctionValue::begin() {
	throw Simple_Error("begin There is no operator corresponding");
}

Simple_Iterator FunctionValue::end() {
	throw Simple_Error("end There is no operator corresponding");
}

ValuePtr FunctionValue::operator+(const ValuePtr& other) const {
	throw Simple_Error("+ There is no operator corresponding");
}

ValuePtr FunctionValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("- There is no operator corresponding");
}

ValuePtr FunctionValue::operator*(const ValuePtr& other) const {
	throw Simple_Error("* There is no operator corresponding");
}

ValuePtr FunctionValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("/ There is no operator corresponding");
}

void FunctionValue::operator+=(const ValuePtr& other) {
	throw Simple_Error("+= There is no operator corresponding");
}

void FunctionValue::operator-=(const ValuePtr& other) {
	throw Simple_Error("-= There is no operator corresponding");
}

void FunctionValue::operator*=(const ValuePtr& other) {
	throw Simple_Error("*= There is no operator corresponding");
}

void FunctionValue::operator/=(const ValuePtr& other) {
	throw Simple_Error("/= There is no operator corresponding");
}

void FunctionValue::powereq(const ValuePtr& other) {
	throw Simple_Error("**= There is no operator corresponding");
}

ValuePtr FunctionValue::operator++() {
	throw Simple_Error("++i There is no operator corresponding");
}

ValuePtr FunctionValue::operator++(int) {
	throw Simple_Error("i++ There is no operator corresponding");
}

ValuePtr FunctionValue::operator--() {
	throw Simple_Error("--i There is no operator corresponding");
}

ValuePtr FunctionValue::operator--(int) {
	throw Simple_Error("i-- There is no operator corresponding");
}

bool FunctionValue::operator<(const ValuePtr& other) const {
	throw Simple_Error("< There is no operator corresponding");
}

bool FunctionValue::operator>(const ValuePtr& other) const {
	throw Simple_Error("> There is no operator corresponding");
}

bool FunctionValue::operator<=(const ValuePtr& other) const {
	throw Simple_Error("<= There is no operator corresponding");
}

bool FunctionValue::operator>=(const ValuePtr& other) const {
	throw Simple_Error(">= There is no operator corresponding");
}

bool FunctionValue::operator==(const ValuePtr& other) const {
	throw Simple_Error("== There is no operator corresponding");
}

bool FunctionValue::operator!=(const ValuePtr& other) const {
	throw Simple_Error("!= There is no operator corresponding");
}

Value& FunctionValue::operator[](int pos) {
	throw Simple_Error("[] There is no operator corresponding");
}

ValuePtr FunctionValue::operator()(Args_t args) const {
	auto func = CheckAndGetFunc(this->func, (int)args.size());

	if (func)
		return func->execute(MOVE(args));

	else throw Simple_Error("No overload found with " + std::to_string(args.size()) + " args count");
}

ValuePtr FunctionValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

Value& FunctionValue::dot(const WString& key) const {
	throw Simple_Error(L"Function does not have a member named \"" + key + L"\"");
}

ValuePtr FunctionValue::call_method(const WString& key, int args_count, Args_t args) const {
	throw Simple_Error(L"Function does not have a member named \"" + key + L"\"");
}