#include "Values.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "Variables.h"

#include <algorithm>

using namespace Simple;

StructValue::StructValue(const WString& name, Vars_t fields)
	: name(name), fields(MOVE(fields)) {}

double StructValue::AsDouble() const {
	throw Simple_Error("You can't convert a structure to a number");
}

WString StructValue::AsString() const {
	throw Simple_Error("You can't convert a structure to a string");
	/*return name + L" {\n" + [this]() {
		WString result;
		for (auto& field : fields) {
			result += L"    " + field.first + L": " + field.second->AsString() + L"\n";
		}
		return result;
		}() + L"}";*/
}

ValuePtr StructValue::clone() const {
	return STRUCT(name, [this]() -> Vars_t {
		Vars_t clone_fields;

		for (auto& field : fields) {
			clone_fields.emplace(field.first, Variable(MOVE(field.second.value->clone()), field.second.is_const));
		}
		return clone_fields;
		}());
}

Value& StructValue::get_ref() {
	return *this;
}

void StructValue::set_ref(ValuePtr& ref) {
	if (auto structRef = dynamic_cast<StructValue*>(ref.get())) {
		name = structRef->name;

		fields = MOVE(structRef->fields);
	}
	else {
		throw Simple_Error("Invalid type");
	}
}

ValueType StructValue::GetType() const {
	return ValueType::_STRUCT;
}

WString StructValue::GetTypeInString() const {
	return name;
}

Simple_Iterator StructValue::begin() {
	throw Simple_Error("begin There is no operator corresponding");
}

Simple_Iterator StructValue::end() {
	throw Simple_Error("end There is no operator corresponding");
}

ValuePtr StructValue::operator+(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be added");
}

ValuePtr StructValue::operator-(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be subtructed");
}

ValuePtr StructValue::operator*(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be multiplicated");
}

ValuePtr StructValue::operator/(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be divided");
}

ValuePtr StructValue::operator++() {
	throw Simple_Error("You can't increment a structure");
}

ValuePtr StructValue::operator++(int) {
	throw Simple_Error("You can't increment a structure");
}

ValuePtr StructValue::operator--() {
	throw Simple_Error("You can't decrement a structure");
}

ValuePtr StructValue::operator--(int) {
	throw Simple_Error("You can't decrement a structure");
}

bool StructValue::operator<(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator>(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator<=(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator>=(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator==(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

bool StructValue::operator!=(const ValuePtr& other) const {
	throw Simple_Error("Structures cannot be compared");
}

Value& StructValue::operator[](int pos) {
	throw Simple_Error("In a structure you cannot access it by index");
}

ValuePtr StructValue::operator()(Args_t args) const {
	throw Simple_Error("() There is no operator corresponding");
}

ValuePtr StructValue::power(const ValuePtr& other) const {
	throw Simple_Error("Structure cannot be raised to a power");
}

Value& StructValue::dot(const WString& key) const {

	auto find_result = fields.find(key);
	if (find_result != fields.end()) {

		if (find_result->second.is_const) {
			cloneValue = find_result->second.value->clone();
			return cloneValue->get_ref();
		}

		else return find_result->second.value->get_ref();
	}
	throw Simple_Error(L"Struct \"" + name + L"\" does not have a member named \"" + key + L"\"");
}

int StructValue::fields_count() {
	return static_cast<int>(fields.size());
}

WStr_vec StructValue::fields_names() {
	WStr_vec fields_names;

	for (auto& field : fields) {
		fields_names.push_back(field.first);
	}
	return fields_names;
}