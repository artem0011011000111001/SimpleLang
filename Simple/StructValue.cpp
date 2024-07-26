#include "Values.h"
#include "Simple_defines.h"
#include "Simple_Error.h"
#include "Variables.h"

#include <algorithm>

using namespace Simple;

StructValue::StructValue(const std::string& name, std::unordered_map<std::string, ValuePtr> fields)
	: name(name), fields(std::move(fields)) {}

double StructValue::AsDouble() {
	throw Simple_Error("You can't convert a structure to a number");
}

std::string StructValue::AsString() {
	throw Simple_Error("You can't convert a structure to a string");
}

ValuePtr StructValue::clone() const {
	return CREATE_PTR<StructValue>(name, [this]() -> std::unordered_map<std::string, ValuePtr> {
		std::unordered_map<std::string, ValuePtr> clone_fields;

		for (auto& field : fields) {
			clone_fields.emplace(field.first, field.second->clone());
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
		fields = std::move(structRef->fields);
	}
	else {
		throw Simple_Error("Invalid reference type");
	}
}

ValueType StructValue::GetType() const {
	return ValueType::STRUCT;
}

std::string StructValue::GetTypeInString() const {
	return "\"" + name + "\"";
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

ValuePtr StructValue::operator[](int pos) const {
	throw Simple_Error("In a structure you cannot access it by index");
}

ValuePtr StructValue::power(const ValuePtr& other) const {
	throw Simple_Error("Structure cannot be raised to a power");
}

ValuePtr StructValue::dot(const std::string& key) const {
	auto find_result = fields.find(key);
	if (find_result != fields.end())
		return fields.find(key)->second->clone();
	throw Simple_Error("Struct \"" + name + "\" does not have a member named \"" + key + "\"");
}
