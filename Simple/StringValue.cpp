#include "Values.h"
#include "Simple_Error.h"
#include "Simple_defines.h"
#include "Utils.h"

using namespace Simple;

StringValue::StringValue(const WString& value)
	: value([this, value]() {
			Vec<CharValue> result;
			for (auto& Char : value) {
				result.push_back(WString(1, Char));
			}
			return result;
		}()) {}

double StringValue::AsDouble() const {
	return strict_stod(AsString());
}

WString StringValue::AsString() const {
	WString result;
	for (auto& Char : value) {
		result += Char.AsString();
	}
	return result;
}

ValuePtr StringValue::clone() const {
	return STRING(AsString());
}

Value& StringValue::get_ref() {
	return *this;
}

void StringValue::set_ref(ValuePtr& ref) {
	if (auto stringRef = dynamic_cast<StringValue*>(ref.get())) {
		value = stringRef->value;
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType StringValue::GetType() const {
	return ValueType::_STRING;
}

WString StringValue::GetTypeInString() const {
	return L"str";
}

Simple_Iterator StringValue::begin() {
	static ValuePtr begin_ptr = CHAR(*(value.data()));
	//ptr_to_char = CHAR(*(value.data()));
	return Simple_Iterator(&begin_ptr);
}

Simple_Iterator StringValue::end() {
	static ValuePtr end_ptr = CHAR(*(value.data() + value.size()));
	return Simple_Iterator(&end_ptr);
}

ValuePtr StringValue::operator+(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING || other->GetType() == ValueType::_CHAR)
		return STRING(AsString() + other->AsString());

	throw Simple_Error(L"+ There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr StringValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("- There is no operator corresponding");
}

ValuePtr StringValue::operator*(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_NUMBER || other->GetType() == ValueType::_DIGIT_) {
		auto result = [this, &other]() {
			WString result;
			for (size_t i = 0, size = (size_t)other->AsDouble(); i < size; i++) {
				result += AsString();
			}
			return result;
			};
		return STRING(result());
	}
	throw Simple_Error(L"* There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

ValuePtr StringValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("/ There is no operator corresponding");
}

ValuePtr StringValue::operator++() {
	throw Simple_Error("++i There is no operator corresponding");
}

ValuePtr StringValue::operator++(int) {
	throw Simple_Error("i++ There is no operator corresponding");
}

ValuePtr StringValue::operator--() {
	throw Simple_Error("--i There is no operator corresponding");
}

ValuePtr StringValue::operator--(int) {
	throw Simple_Error("i-- There is no operator corresponding");
}

bool StringValue::operator<(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() < other->AsString();

	throw Simple_Error(L"< There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool StringValue::operator>(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() > other->AsString();

	throw Simple_Error(L"> There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool StringValue::operator<=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() <= other->AsString();

	throw Simple_Error(L"<= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool StringValue::operator>=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() >= other->AsString();

	throw Simple_Error(L">= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool StringValue::operator==(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() == other->AsString();

	throw Simple_Error(L"== There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

bool StringValue::operator!=(const ValuePtr& other) const {
	if (other->GetType() == ValueType::_STRING)
		return AsString() != other->AsString();

	throw Simple_Error(L"!= There is no operator corresponding to these operands: "
		+ GetTypeInString() + L" " + other->GetTypeInString());
}

Value& StringValue::operator[](int pos) {
	check_pos(pos, (int)AsString().length(), "str");
	return value[pos].get_ref();
}

ValuePtr StringValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr StringValue::power(const ValuePtr& other) const {
	throw Simple_Error("** There is no operator corresponding");
}

Value& StringValue::dot(const WString& key) const {
	throw Simple_Error(L"String does not have a member named \"" + key + L"\"");
}